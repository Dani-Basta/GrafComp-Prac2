#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

//constexpr double PI = 3.14159265;

using namespace glm;

//-------------------------------------------------------------------------

/*
De forma predeterminada se aplicar� sobre modelMat y modelViewMat. Por lo tanto, si modificamos modelMat, 
cuando llamemos a modelMat, se cargar� otra cosa distinta.
*/

void Entity::uploadMvM(dmat4 const& modelViewMat) const
{ 
	dmat4 aMat = modelViewMat * modelMat;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(aMat));
}

//-------------------------------------------------------------------------


void Entity::update() {}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//------------------------ENTIDADES CU�DRICAS------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Sphere::Sphere(GLdouble r) {
	this->r = r;
}


void Sphere::render(glm::dmat4 const& modelViewMat) {
	uploadMvM(modelViewMat * this->modelMat);

	// Fijar el color con glColor3f(...);
	//glColor3f(0.0, 0.0, 0.0);

	// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
	//gluQuadricDrawStyle(q, GLU_LINE);

	gluQuadricDrawStyle(q, GLU_FILL);

	/*
	glDisable(GL_COLOR_MATERIAL);

	Material mat =
		//Material(Material::Copper);
		Material(Material::Gold);
	//Material(Material::Silver);
	mat.upload();


	gluSphere(q, r, 50, 50);


	gluQuadricDrawStyle(q, GLU_FILL);
	glEnable(GL_COLOR_MATERIAL);
	*/
	//glColor3f(1.0, 1.0, 1.0);
}

void Sphere::update() {}

Cylinder::Cylinder(GLdouble r1, GLdouble r2, GLdouble h) {
	this->r1 = r1;
	this->r2 = r2;
	this->h = h;
}

void Cylinder::render(glm::dmat4 const& modelViewMat) {
	uploadMvM(modelViewMat * this->modelMat);
	//uploadMvM(modelViewMat);

	// Fijar el color con glColor3f(...);
	//glColor3f(0.0, 0.0, 0.0);

	// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
	//gluQuadricDrawStyle(q, GLU_LINE);
	

	//gluQuadricDrawStyle(q, GLU_FILL);

	gluCylinder(q, r1, r2, h, 50, 50);

	//gluQuadricDrawStyle(q, GLU_FILL);
	//glColor3f(1.0, 1.0, 1.0);
}

void Cylinder::update() { }


Disk::Disk(GLdouble r1, GLdouble r2) {
	this->r1 = r1;
	this->r2 = r2;
}

void Disk::render(glm::dmat4 const& modelViewMat) {
	uploadMvM(modelViewMat * this->modelMat);

	// Fijar el color con glColor3f(...);
	//glColor3f(0.0, 0.0, 0.0);

	// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
	//gluQuadricDrawStyle(q, GLU_LINE);

	gluDisk(q, r1, r2, 50, 50);

	//gluQuadricDrawStyle(q, GLU_FILL);
	//glColor3f(1.0, 1.0, 1.0);
}

void Disk::update() {}

PartialDisk::PartialDisk(GLdouble r1, GLdouble r2, GLdouble ini, GLdouble fin) {
	this->r1 = r1;
	this->r2 = r2;
	this->ini = ini;
	this->fin = fin;
}

void PartialDisk::render(glm::dmat4 const & modelViewMat) {
	uploadMvM(modelViewMat * this->modelMat);

	// Fijar el color con glColor3f(...);
	//glColor3f(0.0, 0.0, 0.0);

	// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
	//gluQuadricDrawStyle(q, GLU_LINE);

	gluPartialDisk(q, r1, r2, 50, 50, ini, fin);

	//gluQuadricDrawStyle(q, GLU_FILL);
	//glColor3f(1.0, 1.0, 1.0);
}

void PartialDisk::update() {}

//-------------------------------------------------------------------------

/*
	Debemos implementar estos tres m�todos para cada clase que queramos mostrar.

	En el primer m�todo, a�adimos la malla correspondiente a la entidad. No siempre es necesario 
	crear una nueva (se pueden reutilizar otras).

	La implementaci�n del segundo m�todo ser� pr�cticamente la misma en todos los objetos.

	El tercer m�todo ser� el que dibujar� el objeto. Entonces, en este m�todo debemos indicar c�mo 
	queremos que se dibuje el objeto.

	IMPORTANTE !!

	Siempre ubicaremos el objeto en el punto (0,0,0). Si queremos que se vea en otra posici�n, utilizar los 
	m�todos translate, rotate, etc. 

	Todos estos m�todos se utilizan dentro de la implementaci�n correspondiente de render.
*/

//-------------------------------------------------------------------------

// COMPOUND ENTITY

void CompoundEntity::render(dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	for (Entity* it : grObjects) 
		it->render(aMat);
}

void CompoundEntity::update() {
	for (Entity* it : grObjects) 
		it->update();
}

//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::createRGBAxes(l);
}

EjesRGB::~EjesRGB() 
{ 
	delete mesh; mesh = nullptr; 
};

void EjesRGB::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 modelMatAux = modelViewMat * this->modelMat;
		uploadMvM(modelMatAux);
		glLineWidth(2); 
		mesh->render();
		glLineWidth(1);
	}
}

void EjesRGB::update() {

}


//-------------------------------------------------------------------------

//POLIESPIRAL


Poliespiral::Poliespiral(dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert): Entity()
{
	mesh = Mesh::generaPoliespiral(verIni, angIni,incrAng, ladoIni, incrLado, numVert);
}

Poliespiral::~Poliespiral()
{
	delete mesh; mesh = nullptr;
};

void Poliespiral::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {
		

		//El traslado necesario para realizar la escena. Comentar si se desea que est� en (0,0).
		dmat4 modelMatAux = modelViewMat * this->modelMat;
		modelMatAux = translate(modelMatAux, dvec3(-100, 100, 0.0));

		uploadMvM(modelMatAux);
		
		glLineWidth(2);
		glColor3d(0.0,1.0,0.0);

		mesh->render();  //Se dibuja en este momento.
		
		//Reestrablecer todo a su valor predeterminado.
		glLineWidth(1);	
	}
}

void Poliespiral::update() {

}

//-------------------------------------------------------------------------

//DRAGON

Dragon::Dragon(GLuint numVert) : Entity()
{
	mesh = Mesh::generaDragon(numVert);
}

Dragon::~Dragon()
{
	delete mesh; mesh = nullptr;
};

void Dragon::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {

		
		//dmat4 modelMatAux = modelMat; //De esta otra forma no funciona.
		dmat4 modelMatAux = modelViewMat * this->modelMat;

		//Traslaci�n inicial para la escena 2D.
		modelMatAux = translate(modelMatAux, dvec3(100,100,0));

		modelMatAux = scale(translate(modelMatAux, dvec3(-40.0, -170.0, 0.0)), dvec3(40.0, 40.0, 40.0));

		uploadMvM(modelMatAux); //Cargamos la matriz de modelado modificada.

		glPointSize(2);			  //Establecemos el tama�o de los puntos.
		glColor3d(0.0, 1.0, 0.0); //Establecemos los colores.
			   
		mesh->render();  //Se dibuja en este momento.

		//Reestrablecer todo a su valor predeterminado.
		glPointSize(1);
	}
}


void Dragon::update() {

}


//-------------------------------------------------------------------------


//TRIANGULO RGB

TrianguloRGB::TrianguloRGB(GLdouble r) : Entity()
{
	mesh = Mesh::generaTrianguloRGB(r);
}

TrianguloRGB::~TrianguloRGB()
{
	delete mesh; mesh = nullptr;
};

void TrianguloRGB::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {


		dmat4 modelMatAux = modelViewMat * this->modelMat;

		//Traslaci�n inicial para la escena 2D.
		modelMatAux = translate(modelMatAux, dvec3(-100,-100,0));

		//glPolygonMode(GL_BACK,GL_POINT);
		glPolygonMode(GL_BACK,GL_LINE);

		uploadMvM(modelMatAux);
		mesh->render();  //Se dibuja en este momento.

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reestablecemos la opci�n por defecto.

	}
}

void TrianguloRGB::update() {

}

//------------------------------------

//Rectangulo RGB

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) : Entity() {
	this->modelMat = dmat4(1.0);
	mesh = Mesh::generaRectanguloRGB(w, h);
	this->color = fvec3(1.0);
}

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h, fvec3 color) : Entity() {
	this->modelMat = dmat4(1.0);
	mesh = Mesh::generaRectanguloRGB(w, h);
	this->color = color;
}

RectanguloRGB::~RectanguloRGB() {
	delete mesh; mesh = nullptr;
};

void RectanguloRGB::render(dmat4 const &modelViewMat) {
	if (mesh != nullptr) {

		dmat4 modelMatAux = modelViewMat * this->modelMat;

		glColor3f(color.r, color.g, color.b);

		//Rotaci�n necesaria para la escena 3D.

		//modelMatAux = rotate(modelMatAux, radians(90.0),dvec3(1,0,0));

		//modelMatAux = rotate(modelMatAux, radians(25.0), dvec3(0.0,0.0,1.0));

		uploadMvM(modelMatAux);
		mesh->render();  //Se dibuja en este momento.
	}
}

void RectanguloRGB::update() {

}

//------------------------------------

//TRIANGULO ANIMADO

TrianguloAnimado:: TrianguloAnimado(GLdouble r,GLdouble x, GLdouble y, GLdouble gradeIncr) : Entity()
{
	mesh = Mesh::generaTrianguloRGB(r);

	this->x = x;
	this->y = y;
	this->incrGr = gradeIncr;
}

TrianguloAnimado::~TrianguloAnimado()
{
	delete mesh; mesh = nullptr;
};

void TrianguloAnimado::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {

		dmat4 auxModelMat = modelViewMat * this->modelMat;

		//Traslaci�n inicial para la escena 2D.
		//No la realizamos, lo ubicamos en el centro (0,0,0).
		//auxModelMat = translate(auxModelMat, dvec3(-100, -200, 0));

		//Utilizamos, como radio de giro que dibuja la circumferencia, 100 unidades.

		auxModelMat = translate(auxModelMat, dvec3(this->x + 100 * cos(radians(this->grades)), this->y + 100 * sin(radians(this->grades)) ,0.0));
		auxModelMat = rotate(auxModelMat, radians(this->grades), dvec3(0,0,1));
			

		uploadMvM(auxModelMat);
		mesh->render();  //Se dibuja en este momento.

	}
}

void TrianguloAnimado::update() {
	this->grades = this->grades + this->incrGr;
}

//------------------------------------------------------------------------

//ESTRELLA 3D

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h, GLdouble ri) : Entity()
{
	mesh = Mesh::generaEstrella3D(re,np,h,ri);

	this->angle = 20;
	this->incrAngle = 3; 
}

Estrella3D::~Estrella3D()
{
	delete mesh; mesh = nullptr;
};

void Estrella3D::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {

		dmat4 auxModelMat = modelViewMat * this->modelMat;

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3d(1.0, 0.0, 0.0); //Establecemos los colores.

		//Traslaci�n para la animaci�n 3D
		auxModelMat = translate(auxModelMat, dvec3(100,100,100));


		//Realizamos la rotaci�n asociada a la animaci�n.		
		auxModelMat = rotate(auxModelMat, radians(this->angle + 20), dvec3(0, 1, 0)); //Rotamos en el eje Y.
		auxModelMat = rotate(auxModelMat, radians(this->angle), dvec3(0,0,1)); //Rotamos en el eje Z.


		uploadMvM(auxModelMat);
		mesh->render();  //Se dibuja en este momento.

		//Para el duplicado asociado.
		auxModelMat = rotate(auxModelMat, radians(180.0), dvec3(0,1,0));
		
		glColor3d(0.0, 0.0, 1.0); //Establecemos los colores.
		
		uploadMvM(auxModelMat);
		mesh->render();  //Se dibuja en este momento.
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reestablecemos la opci�n por defecto.


	}
}

void Estrella3D::update() {
	this->angle += this->incrAngle;
}

//------------------------------------------------------------------------

//CUBO 3D

Cubo3D::Cubo3D(GLdouble h, GLdouble w) : Entity()
{
	mesh = Mesh::generaCubo(h, w);
	auxiliarMesh = Mesh::generaSueloCubo(h, w);
}

Cubo3D::~Cubo3D()
{
	delete mesh; mesh = nullptr;
};

void Cubo3D::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {

		glColor3d(0.0, 0.0, 1.0); //Establecemos los colores.
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		dmat4 modelMatAux = modelViewMat * this->modelMat;

		uploadMvM(modelMatAux);


		mesh->render();  //Dibujamos el cubo.

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		auxiliarMesh->render();	//Dibujamos el suelo del cubo.
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}
}

void Cubo3D::update() {
}

//------------------------------------------------------------------------

//CUBO TAPADO

CuboTapado::CuboTapado(GLdouble h, GLdouble w) : Entity()
{
	mesh = Mesh::generaCubo(h, w);
	auxiliarMesh = Mesh::generaSueloCubo(h, w);
	auxiliarMesh2 = Mesh::generaTapaCubo(h, w);
}

CuboTapado::~CuboTapado()
{
	delete mesh; mesh = nullptr;
};

void CuboTapado::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {

		glColor3d(0.0, 0.0, 1.0); //Establecemos los colores.
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		dmat4 modelMatAux = modelViewMat * this->modelMat;

		uploadMvM(modelMatAux);


		mesh->render();  //Dibujamos el cubo.

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		auxiliarMesh2->render();
		auxiliarMesh->render();	//Dibujamos el suelo del cubo.

	}
}

void CuboTapado::update() {
}

//------------------------------------------------------------------------


//RECTANGULO TEXCOR

RectanguloTexCor::RectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) : Entity()
{
	mesh = Mesh::generaRectanguloTexCor(w, h,rw, rh);
	texture.load("baldosaC.bmp");
}

RectanguloTexCor::~RectanguloTexCor()
{
	delete mesh; mesh = nullptr;
};

void RectanguloTexCor::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {
		texture.bind( GL_REPLACE );				//Importante para a�adir la textura.


		dmat4 modelMatAux = modelViewMat * this->modelMat;

		//Rotaci�n necesaria para la escena 3D.
		modelMatAux = rotate(modelMatAux, radians(90.0), dvec3(1, 0, 0));
		modelMatAux = rotate(modelMatAux, radians(25.0), dvec3(0.0, 0.0, 1.0));

		uploadMvM(modelMatAux);
		
		mesh->render();  //Dibujamos el cubo.		
		texture.unbind();

	}
}

void RectanguloTexCor::update() {
}

//------------------------------------------------------------------------


//ESTRELLA TEXCOR

EstrellaTexCor::EstrellaTexCor(GLdouble r, GLdouble nL, GLdouble h, GLdouble ri) : Entity()
{
	mesh = Mesh::generaEstrellaTexCor(r, nL, h, ri);
	texture.load("baldosaP.bmp");

	this->angle = 0;
	this->incrAngle = 3;

}

EstrellaTexCor::~EstrellaTexCor()
{
	delete mesh; mesh = nullptr;
};

void EstrellaTexCor::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {
		
		dmat4 auxModelMat = modelViewMat * this->modelMat;

		//Traslaci�n para la animaci�n 3D
		auxModelMat = translate(auxModelMat, dvec3(100, 100, 100));

		//Realizamos la rotaci�n asociada a la animaci�n.		
		auxModelMat = rotate(auxModelMat, radians(this->angle + 20), dvec3(0, 1, 0)); //Rotamos en el eje Y.
		auxModelMat = rotate(auxModelMat, radians(this->angle), dvec3(0, 0, 1)); //Rotamos en el eje Z.

		texture.bind(GL_REPLACE);				//Importante para a�adir la textura.

		uploadMvM(auxModelMat);

		mesh->render();  //Se dibuja en este momento.

		//Para el duplicado asociado.
		auxModelMat = rotate(auxModelMat, radians(180.0), dvec3(0, 1, 0));

		uploadMvM(auxModelMat);
		mesh->render();  //Se dibuja en este momento.
		texture.unbind();

	}
}

void EstrellaTexCor::update() {
	this->angle += this->incrAngle;
}


//------------------------------------------------------------------------

//CAJATEXCOR

CajaTexCor::CajaTexCor(GLdouble h, GLdouble w) : Entity()
{
	mesh = Mesh::generaCajaTexCor(h, w);
	auxiliarMesh = Mesh::generaSueloTexCor(h, w);
	texture.load("papelE.bmp");
	textureAux.load("container.bmp");
}

CajaTexCor::~CajaTexCor()
{
	delete mesh; mesh = nullptr;
};

void CajaTexCor::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxModelMat = modelViewMat * this->modelMat;
		//Renderizamos solo el exterior.
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		texture.bind(GL_REPLACE);				//Importante para a�adir la textura.
		uploadMvM(auxModelMat);
		mesh->render();  //Dibujamos el cubo.
		auxiliarMesh->render();
		texture.unbind();

		//Renderizamos el interior.
		glCullFace(GL_BACK);
		textureAux.bind(GL_REPLACE);				//Importante para a�adir la textura.
		uploadMvM(auxModelMat);
		mesh->render();  //Dibujamos el cubo.
		auxiliarMesh->render();
		textureAux.unbind();

		glDisable(GL_CULL_FACE);
	}
}

void CajaTexCor::update() {
}

//------------------------------------------------------------------------


//FOTO

Foto::Foto() : Entity()
{
	mesh = Mesh::generaFotoTex(200, 100);
}

Foto::~Foto()
{
	delete mesh; mesh = nullptr;
};

void Foto::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {

		dmat4 auxModelMat = modelViewMat * this->modelMat;

		//Traslaci�n para la animaci�n 3D
		auxModelMat = translate(auxModelMat, dvec3(150, 150, 0));

		texture.bind(GL_REPLACE);				//Importante para a�adir la textura.
		uploadMvM(auxModelMat);
		mesh->render();  //Dibujamos el cubo.
		texture.unbind();
	}
}

void Foto::update() {
	texture.loadColorBuffer();
}



//-------------------------------------------------------------------------
/*


	PARTE 2 DE LA ASIGNATURA.


*/
//-------------------------------------------------------------------------


//CANGILON	

Cangilon::Cangilon(GLdouble h, GLdouble w, GLdouble pos, GLdouble grade) : CajaTexCor(h, w)
{
	this->angle = grade;
	this->incrAngle = 2;
	this->pos = pos;
	this->h = h;
	this->w = w;
	mesh = Mesh::generaCajaTexCor(h, w);
	auxiliarMesh = Mesh::generaSueloTexCor(h, w);
	texture.load("papelE.bmp");
	textureAux.load("container.bmp");
}

Cangilon::~Cangilon()
{
	delete mesh; mesh = nullptr;
}

void Cangilon::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {

		dmat4 auxModelMat = modelViewMat * this->modelMat;

		//Traslaci�n para centrar el cangilon.
		auxModelMat = translate(auxModelMat, dvec3(-w / 2, -h / 2, -w / 2));

		//Traslaci�n para que realice la animaci�n.
		//GLdouble R = pos;
		auxModelMat = translate(auxModelMat, dvec3(this->pos*cos(radians(this->angle)), this->pos*sin(radians(this->angle)), 0));

		//Renderizamos solo el interior.
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		textureAux.bind(GL_REPLACE);				//Importante para a�adir la textura.
		uploadMvM(auxModelMat);
		mesh->render();  //Dibujamos el cubo.
		textureAux.unbind();
		texture.bind(GL_REPLACE);
		auxiliarMesh->render();
		texture.unbind();

		//Renderizamos el exterior.
		glCullFace(GL_BACK);
		textureAux.bind(GL_REPLACE);
		uploadMvM(auxModelMat);
		mesh->render();  //Dibujamos el cubo.
		auxiliarMesh->render();
		textureAux.unbind();

		glDisable(GL_CULL_FACE);
	}
}

void Cangilon::update() {
	this->angle += this->incrAngle;
}


//------------------------------------------------------------------------


//ASPA DE LA NORIA.

AspaNoria::AspaNoria(GLdouble h, GLdouble w, GLdouble hc, GLdouble wc, GLdouble esc, GLdouble grade) : Cubo3D(h, w)
{
	this->hc = hc;
	this->wc = wc;
	this->esc = esc;
	this->angle = grade;
	this->incrAngle = 2;
	mesh = Mesh::generaCajaTexCor(h, w);
	auxiliarMesh = Mesh::generaSueloTexCor(h, w);
}

AspaNoria::~AspaNoria()
{
	delete mesh; mesh = nullptr;
}

void AspaNoria::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {

		dmat4 auxModelMat = modelViewMat * this->modelMat;
		glColor3d(0, 0, 0);

		//Realizamos la rotaci�n para que en lugar de estar alineado con el eje z, lo est� con el eje x.
		auxModelMat = rotate(auxModelMat, radians(90.0), dvec3(0, 1, 0));

		//Rotaci�n asociada al giro de las aspas.
		auxModelMat = rotate(auxModelMat, radians(-this->angle), dvec3(1, 0, 0));

		auxModelMat = scale(auxModelMat, dvec3(1, 1, esc));

		//Trasladamos para renderizar la primera aspa.
		auxModelMat = translate(auxModelMat, dvec3(this->wc / 2, 0, 0));
		uploadMvM(auxModelMat);
		mesh->render();
		auxiliarMesh->render();


		//Trasladamos para renderizar la segunda aspa.
		auxModelMat = translate(auxModelMat, dvec3(-this->wc, 0, 0));
		uploadMvM(auxModelMat);
		mesh->render();
		auxiliarMesh->render();

	}
}

void AspaNoria::update() {
	this->angle += this->incrAngle;
}


//------------------------------------------------------------------------


//ROTOR

Rotor::Rotor(GLdouble r, GLdouble w, bool clockwise, dvec3 color) {	
	this->modelMat = dmat4(1.0);
	this->rect = new RectanguloRGB(2 * r, w, color);
	this->cil = new Cylinder(r, r, w);

	this->r = r;
	this->w = w;
	this->angle = 0;

	this->incrAngle = clockwise ? -37 : 37;

	//dmat4 cylMM = rotate(modelMat, radians(-90.0), dvec3(1, 0, 0));

	//dmat4 rectMM = translate(modelMat, dvec3(0, this->w / 4, 0 ));

	//this->rect->setModelMat(rectMM);
	//this->cil->setModelMat(cylMM);
	this->rect->setModelMat(translate(this->rect->getModelMat(),dvec3(0, this->w / 4, 0)));
	this->cil->setModelMat(rotate(this->cil->getModelMat(), radians(-45.0), dvec3(1, 0, 0)));


	this->grObjects.push_back(this->rect);
	this->grObjects.push_back(this->cil);	
	
	//this->mesh = Mesh::generaRectangulo(2 * r, w);
}

Rotor::~Rotor() {
	CompoundEntity::~CompoundEntity();
	
	return;

	delete mesh; mesh = nullptr;
	delete cil; cil = nullptr;
}

/*
void Rotor::render(dmat4 const &modelViewMat) {
	CompoundEntity::render(modelViewMat*this->modelMat);
	//return ;
	/*
	if (mesh != nullptr) {

		dmat4 auxModelMat = modelViewMat;

		//auxModelMat = rotate(auxModelMat, radians(-90.0), dvec3(1, 0, 0));

		// Pintamos el cilindro que hace de contorno del aspa
		glColor3f(1.0, 0.0, 0.0);
		//gluQuadricDrawStyle(q, GLU_LINE);
		//gluCylinder(this->q, this->r, this->r, this->w, 50, 50);
		this->cil->render(auxModelMat);
		//gluQuadricDrawStyle(q, GLU_FILL);
		// Devolvemos el color al por defecto 
		glColor3f(1.0, 1.0, 1.0);

		uploadMvM(auxModelMat);
		
		auxModelMat = rotate(auxModelMat, radians(-90.0), dvec3(1, 0, 0));

		auxModelMat = translate(auxModelMat, dvec3(0, 0, this->w / 2));

		auxModelMat = rotate(auxModelMat, radians(90.0), dvec3(1, 0, 0));

		//Rotacion del aspa 
		auxModelMat = rotate(auxModelMat, radians(this->angle), dvec3(0, 1, 0));

		uploadMvM(auxModelMat);

		glColor3d(0.0, 0.0, 0.0);
		mesh->render();
		glColor3d(1.0, 1.0, 1.0);

	}
	///
}
//*/

void Rotor::update() {
	this->rect->setModelMat( rotate(rect->getModelMat(), radians(this->incrAngle), dvec3(0, 1, 0)));
	/*
	dmat4 rectMM = rotate(dmat4(1.0), radians(-90.0), dvec3(1, 0, 0));
	rectMM = translate(rectMM, dvec3(0, 0, this->w / 2));
	rectMM = rotate(rectMM, radians(90.0), dvec3(1, 0, 0));
	rectMM = rotate(rectMM, radians(this->angle), dvec3(0, 1, 0));
	this->rect->setModelMat(rectMM);
	//*/
}

//------------------------------------------------------------------------

//CHASIS 

Chasis::Chasis(GLdouble escH, GLdouble escW) : CuboTapado(1, 1)
{
	this->escH = escH;
	this->escW = escW;

	mesh = Mesh::generaCubo(1, 1);				//Lo hacemos de 1x1. Luego, escalaremos lo que corresponda.
	auxiliarMesh = Mesh::generaSueloCubo(1, 1);
	auxiliarMesh2 = Mesh::generaTapaCubo(1, 1);
}

Chasis::~Chasis()
{
	delete mesh; mesh = nullptr;
	delete auxiliarMesh; auxiliarMesh = nullptr;
	delete auxiliarMesh2; auxiliarMesh2 = nullptr;
}

void Chasis::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {

		dmat4 auxModelMat = modelViewMat * this->modelMat;
		glColor3d(0, 0, 1);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Reestablecemos la opci�n por defecto.

		//Traslaci�n para ubicar el objeto de modo que el centro est� en 0,0,0
		auxModelMat = translate(auxModelMat, dvec3(-this->escW / 2, -this->escH/2, -this->escW/2));

		//Escalamos tal y como corresponda.
		auxModelMat = scale(auxModelMat, dvec3(this->escW, this->escH, this->escW));

		uploadMvM(auxModelMat);
		mesh->render();
		auxiliarMesh->render();
		auxiliarMesh2->render();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reestablecemos la opci�n por defecto
	}
}

void Chasis::update() { }

//------------------------------------------------------------------------


//Dron

Dron::Dron(GLdouble r, GLdouble w, GLdouble escH, GLdouble escW) {
	Chasis* chasis = new Chasis(escH, escW);

	this->rot1 = new Rotor(r, w, true, dvec3(1.0, 0.0, 0.0));
	this->rot2 = new Rotor(r, w, false, dvec3(1.0, 0.0, 0.0));
	this->rot3 = new Rotor(r, w, false, dvec3(0.0, 1.0, 0.0));
	this->rot4 = new Rotor(r, w, true, dvec3(0.0, 1.0, 0.0));


	chasis->setModelMat( this->modelMat );

	this->rot1->setModelMat(translate(this->modelMat, dvec3(-escW / 2, escH / 2, -escW / 2)));
	this->rot2->setModelMat(translate(this->modelMat, dvec3(escW / 2, escH / 2, -escW / 2)));
	this->rot3->setModelMat(translate(this->modelMat, dvec3(-escW / 2, escH / 2, escW / 2)));
	this->rot4->setModelMat(translate(this->modelMat, dvec3(escW / 2, escH / 2, escW / 2)));
	

	this->grObjects.push_back(chasis);
	this->grObjects.push_back(rot1);
	this->grObjects.push_back(rot2);
	this->grObjects.push_back(rot3);
	this->grObjects.push_back(rot4);
}

Dron::Dron(GLdouble r, GLdouble w, GLdouble escH, GLdouble escW, SpotLight* li) : Dron(r,w,escH,escW) {
	this->cameraLight = li;
	li->setPosDir(fvec3(0, -escH/2, 0));
	cameraLight->enable();
}

Dron::~Dron() {
	//delete chasis; chasis = nullptr;
	delete rot1; rot1 = nullptr;
	delete rot2; rot2 = nullptr;
	delete rot3; rot3 = nullptr;
	delete rot4; rot4 = nullptr;
	if (this->cameraLight != nullptr) {
		cameraLight->disable();
		delete cameraLight;
		cameraLight = nullptr ;
	}
}

void Dron::render(dmat4 const &modelViewMat) {
	if (this->cameraLight != nullptr) {
		//cameraLight->enable();
		dmat4 auxModelMat = modelViewMat * this->modelMat;
		cameraLight->upload(dmat4(1.0)* auxModelMat);
	}
	__super::render(modelViewMat);

}

/*
void Dron::update() {
	this->rot1->update();
	this->rot2->update();
	this->rot3->update();
	this->rot4->update();
}
*/
//------------------------------------------------------------------------


//Cono

Cone::Cone(GLdouble h, GLdouble r) {
	this->r = r;    //radio de la base
	this->h = h;    //altura del cono
	int m = 3; // m=n�mero de puntos del perfil
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(0.0, 0.0, 0.0);
	perfil[1] = dvec3(r, 0.0, 0.0);
	perfil[2] = dvec3(0.0, h, 0.0);
	// this->mesh = new MBR(m, 50, perfil); // No funciona el polimorfismo Mesh-MBR
	this->mbr = new MBR(m, 100, perfil);
}

Cone::~Cone() {
	if (mesh != nullptr) {
		delete mesh; mesh = nullptr;
	}
	if (mbr != nullptr) {
		delete mbr; mbr = nullptr;
	}
}

void Cone::render(dmat4 const &modelViewMat) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	dmat4 auxModelMat = modelViewMat * this->modelMat;
	uploadMvM(auxModelMat);
	// mesh->render(); // No funciona el polimorfismo Mesh-MBR
	mbr->render();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Cone::update() { }


//------------------------------------------------------------------------


//Esfera

Esfera::Esfera(GLdouble r, GLdouble m, GLdouble n) {

	this->r = r;    // radio de la esfera
	this->m = m;    // numero de paralelos de la esfera
	this->n = n;    // numero de meridianos de la esfera

	dvec3* perfil = new dvec3[m];

	GLdouble angBase = -90.0;

	GLdouble incrAng = 180 / (m-1) ;

	for (size_t i = 0; i < m; i++)	
		perfil[i] = dvec3( r * cos( radians(angBase + i*incrAng)  ) , r * sin(radians(angBase + i * incrAng)), 0.0);

	// this->mesh = new MBR(m, n, perfil); // No funciona el polimorfismo Mesh-MBR
	this->mbr = new MBR(m, n, perfil);

	this->color = fvec3(0.8, 0.4, 0.2);
}

//Esfera

Esfera::Esfera(GLdouble r, GLdouble m, GLdouble n, Material::mater mater) : Esfera(r,n,m) {
	this->mat = new Material(mater);
}

Esfera::~Esfera(){
	if (mesh != nullptr) {
		delete mesh; mesh = nullptr;
	}
	if (mbr != nullptr) {
		delete mbr; mbr = nullptr;
	}
	if (mat != nullptr) {
		delete mat; mat = nullptr;
	}
}

void Esfera::render(dmat4 const &modelViewMat) {
	if (mbr != nullptr) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		dmat4 auxModelMat = modelViewMat * this->modelMat;
		uploadMvM(auxModelMat);

		if (this->mat != nullptr) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDisable(GL_COLOR_MATERIAL);
			mat->upload();

			mbr->render();
			
			glEnable(GL_COLOR_MATERIAL);
		}
		else {
			glEnable(GL_COLOR_MATERIAL);
			//this->color = fvec3(0.8, 0.4, 0.2);
			if ( color != fvec3(-1.0, -1.0, -1.0) )  // color.r != -1.0 || color.g != -1.0 || color.b != -1.0 )
				glColor3fv( value_ptr(color)  );
			else
				glColor3f(0.24725, 0.1995, 0.0745);
			mbr->render();
		}
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}



void Esfera::update() { }

//------------------------------------------------------------------------

// ESFERA con un DRON sobrevolando

EsferaDron::EsferaDron(GLdouble r, GLdouble m, GLdouble n) : Esfera(r, m, n) {

	this->angMer = 45.0;
	this->angPar = 0.0;
	
	this->dron = new Dron(5, 2, 5, 20);
}

// ESFERA con un DRON sobrevolando

EsferaDron::EsferaDron(GLdouble r, GLdouble m, GLdouble n, Material::mater mat, SpotLight* li) : Esfera(r, m, n, mat) {

	this->angMer = 45.0;
	this->angPar = 0.0;

	this->dron = new Dron(5, 2, 5, 20, li);
}

EsferaDron::~EsferaDron() {
	//this->esfera->~Esfera();
	//this->esfera = nullptr;
	Esfera::~Esfera();
	this->dron->~Dron();
	this->dron = nullptr;
}

void EsferaDron::render(dmat4 const &modelViewMat) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	dmat4 rot = modelViewMat;
	rot = rotate(rot, radians(angMer), dvec3(0, 1, 0));
	rot = rotate(rot, radians(angPar), dvec3(1, 0, 0));
	
	//rot = translate(rot, dvec3(0, (r + 5) * sin(radians(angPar) ), 0));
	//rot = translate(rot, dvec3(0, (r + 5) * sin(radians(angPar)), 0));
	
	rot = translate(rot, dvec3(0.0, this->r + 20, 0.0));
	this->dron->render(rot);
	//glColor3f(0.0, 0.0, 0.0);

	//this->esfera->render(modelViewMat);
	__super::render(modelViewMat);

	//glColor3f(1.0, 0.0, 0.0);

}

void EsferaDron::update() { 
	if( this->oscilacion )
		switch ( rand() % 8 ) {
		case 0:
			this->angPar -= 0.1;
			break;
		case 1:
			this->angMer -= 0.1;
			break;
		case 2:
			this->angPar += 0.1;
			break;
		case 3:
			this->angMer += 0.1;
			break;
		}

	this->dron->update();
}

void EsferaDron::move(int key) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		this->angMer += 3;
		break;
	case GLUT_KEY_LEFT:
		this->angMer -= 3;
		break;
	case GLUT_KEY_UP:
		this->angPar -= 3;
		break;
	case GLUT_KEY_DOWN:
		this->angPar += 3;
		break;
	}
}

//------------------------------------------------------------------------

// DRON con DRONES sobrevolando

DronDrones::DronDrones(GLdouble r, GLdouble w, GLdouble escH, GLdouble escW) : Dron(r, w, escH, escW) {

	GLdouble factEsc = 0.2;
	
	//this->dron = new Dron(factEsc*r, factEsc*w, factEsc*escH, factEsc*escW);

	GLdouble deltaX = (escW / 2 ) ;
	GLdouble deltaY = (escH / 2 + w + 5) ;
	GLdouble deltaZ = (escW / 2) ;

	dmat4 escala = scale(this->modelMat, dvec3(factEsc));

	Dron* dron1 = new Dron(r * factEsc, w * factEsc, escH * factEsc, escW * factEsc);
	Dron* dron2 = new Dron(r * factEsc, w * factEsc, escH * factEsc, escW * factEsc);
	Dron* dron3 = new Dron(r * factEsc, w * factEsc, escH * factEsc, escW * factEsc);
	Dron* dron4 = new Dron(r * factEsc, w * factEsc, escH * factEsc, escW * factEsc);

	dron1->setModelMat(translate(modelMat, dvec3(-deltaX, deltaY, -deltaZ)));
	dron2->setModelMat(translate(modelMat, dvec3( deltaX, deltaY, -deltaZ)));
	dron3->setModelMat(translate(modelMat, dvec3(-deltaX, deltaY,  deltaZ)));
	dron4->setModelMat(translate(modelMat, dvec3( deltaX, deltaY,  deltaZ)));

	this->grObjects.push_back(dron1);
	this->grObjects.push_back(dron2);
	this->grObjects.push_back(dron3);
	this->grObjects.push_back(dron4);
}

DronDrones::~DronDrones() {
	Dron::~Dron();
	CompoundEntity::~CompoundEntity();
}
/*
void DronDrones::render(dmat4 const &modelViewMat) {
	CompoundEntity::render(modelViewMat);
	return;
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	dmat4 escala = scale(modelViewMat, dvec3(factEsc));
	__super::render(modelViewMat);
	
	__super::render(translate(escala, dvec3(-this->deltaX, this->deltaY, -this->deltaZ)));
	__super::render(translate(escala, dvec3( this->deltaX, this->deltaY, -this->deltaZ)));
	__super::render(translate(escala, dvec3(-this->deltaX, this->deltaY,  this->deltaZ)));
	__super::render(translate(escala, dvec3( this->deltaX, this->deltaY,  this->deltaZ)));

	//dmat4 escala = scale(translate(modelViewMat, dvec3(-this->deltaX, this->deltaY, -this->deltaZ)), dvec3(0.2));
	//this->dron->render(translate(modelViewMat, dvec3(-this->deltaX, this->deltaY, -this->deltaZ) ) );
	//this->dron->render(translate(modelViewMat, dvec3( this->deltaX, this->deltaY, -this->deltaZ) ) );
	//this->dron->render(translate(modelViewMat, dvec3(-this->deltaX, this->deltaY,  this->deltaZ) ) );
	//this->dron->render(translate(modelViewMat, dvec3( this->deltaX, this->deltaY,  this->deltaZ) ) );

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
} //*/
/*
void DronDrones::update() {
	__super::update();
	//this->dron->update();
}
*/


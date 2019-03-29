#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

/*
De forma predeterminada se aplicará sobre modelMat y modelViewMat. Por lo tanto, si modificamos modelMat, 
cuando llamemos a modelMat, se cargará otra cosa distinta.

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
//------------------------ENTIDADES CUÁDRICAS------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Sphere::Sphere(GLdouble r) {
	this->r = r;
}

void Sphere::render(glm::dmat4 const& modelViewMat) {
	
	uploadMvM(modelViewMat);
	
	// Fijar el color con glColor3f(...);
	//glColor3f(0.0, 0.0, 0.0);
	
	// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
	//gluQuadricDrawStyle(q, GLU_LINE);

	//gluSphere(q, r, 50, 50);

	//gluQuadricDrawStyle(q, GLU_FILL);

	//glColor3f(1.0, 1.0, 1.0);
}

void Sphere::update() {}

Cylinder::Cylinder(GLdouble r1, GLdouble r2, GLdouble h) {
	this->r1 = r1;
	this->r2 = r2;
	this->h = h;
}

void Cylinder::render(glm::dmat4 const& modelViewMat) {

	uploadMvM(modelViewMat);

	// Fijar el color con glColor3f(...);
	//glColor3f(0.0, 0.0, 0.0);

	// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
	//gluQuadricDrawStyle(q, GLU_LINE);

	//gluCylinder(q, r1, r2, h, 50, 50);

	//gluQuadricDrawStyle(q, GLU_FILL);
	//glColor3f(1.0, 1.0, 1.0);
}

void Cylinder::update() { }


Disk::Disk(GLdouble r1, GLdouble r2) {
	this->r1 = r1;
	this->r2 = r2;
}

void Disk::render(glm::dmat4 const& modelViewMat) {

	uploadMvM(modelViewMat);

	// Fijar el color con glColor3f(...);
	//glColor3f(0.0, 0.0, 0.0);

	// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
	//gluQuadricDrawStyle(q, GLU_LINE);

	//(q, r1, r2, 50, 50);

	//gluQuadricDrawStyle(q, GLU_FILL);
	//glColor3f(1.0, 1.0, 1.0);
}

void Disk::update() {}

PartialDisk::PartialDisk(GLdouble r1, GLdouble r2, GLdouble ini, GLdouble fin)
{
	this->r1 = r1;
	this->r2 = r2;
	this->ini = ini;
	this->fin = fin;
}

void PartialDisk::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat);

	// Fijar el color con glColor3f(...);
	//glColor3f(0.0, 0.0, 0.0);

	// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
	//gluQuadricDrawStyle(q, GLU_LINE);

	//gluPartialDisk(q, r1, r2, 50, 50, ini, fin);

	//gluQuadricDrawStyle(q, GLU_FILL);
	//glColor3f(1.0, 1.0, 1.0);
}

void PartialDisk::update() {}


/*
	Debemos implementar estos tres métodos para cada clase que queramos mostrar.

	En el primer método, añadimos la malla correspondiente a la entidad. No siempre es necesario 
	crear una nueva (se pueden reutilizar otras).

	La implementación del segundo método será prácticamente la misma en todos los objetos.

	El tercer método será el que dibujará el objeto. Entonces, en este método debemos indicar cómo 
	queremos que se dibuje el objeto.

	IMPORTANTE !!

	Siempre ubicaremos el objeto en el punto (0,0,0). Si queremos que se vea en otra posición, utilizar los 
	métodos translate, rotate, etc. 

	Todos estos métodos se utilizan dentro de la implementación correspondiente de render.
*/

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
		uploadMvM(modelViewMat); 
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
		

		//El traslado necesario para realizar la escena. Comentar si se desea que esté en (0,0).
		dmat4 modelMatAux = modelViewMat;
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
		dmat4 modelMatAux= modelViewMat;

		//Traslación inicial para la escena 2D.
		modelMatAux = translate(modelMatAux, dvec3(100,100,0));

		modelMatAux = scale(translate(modelMatAux, dvec3(-40.0, -170.0, 0.0)), dvec3(40.0, 40.0, 40.0));

		uploadMvM(modelMatAux); //Cargamos la matriz de modelado modificada.

		glPointSize(2);			  //Establecemos el tamaño de los puntos.
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


		dmat4 modelMatAux = modelViewMat;

		//Traslación inicial para la escena 2D.
		modelMatAux = translate(modelMatAux, dvec3(-100,-100,0));

		//glPolygonMode(GL_BACK,GL_POINT);
		glPolygonMode(GL_BACK,GL_LINE);

		uploadMvM(modelMatAux);
		mesh->render();  //Se dibuja en este momento.

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reestablecemos la opción por defecto.

	}
}

void TrianguloRGB::update() {

}

//------------------------------------

//Rectangulo RGB

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generaRectanguloRGB(w,h);
}

RectanguloRGB::~RectanguloRGB()
{
	delete mesh; mesh = nullptr;
};

void RectanguloRGB::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {

		dmat4 modelMatAux = modelViewMat;


		//Rotación necesaria para la escena 3D.

		modelMatAux = rotate(modelMatAux, radians(90.0),dvec3(1,0,0));

		modelMatAux = rotate(modelMatAux, radians(25.0), dvec3(0.0,0.0,1.0));

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

		dmat4 auxModelMat = modelViewMat;

		//Traslación inicial para la escena 2D.
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

		dmat4 auxModelMat = modelViewMat;

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3d(1.0, 0.0, 0.0); //Establecemos los colores.

		//Traslación para la animación 3D
		auxModelMat = translate(auxModelMat, dvec3(100,100,100));


		//Realizamos la rotación asociada a la animación.		
		auxModelMat = rotate(auxModelMat, radians(this->angle + 20), dvec3(0, 1, 0)); //Rotamos en el eje Y.
		auxModelMat = rotate(auxModelMat, radians(this->angle), dvec3(0,0,1)); //Rotamos en el eje Z.


		uploadMvM(auxModelMat);
		mesh->render();  //Se dibuja en este momento.

		//Para el duplicado asociado.
		auxModelMat = rotate(auxModelMat, radians(180.0), dvec3(0,1,0));
		
		glColor3d(0.0, 0.0, 1.0); //Establecemos los colores.
		
		uploadMvM(auxModelMat);
		mesh->render();  //Se dibuja en este momento.
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reestablecemos la opción por defecto.


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


		uploadMvM(modelViewMat);


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


		uploadMvM(modelViewMat);


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
		texture.bind( GL_REPLACE );				//Importante para añadir la textura.


		dmat4 modelMatAux = modelViewMat;

		//Rotación necesaria para la escena 3D.
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
		
		dmat4 auxModelMat = modelViewMat;

		//Traslación para la animación 3D
		auxModelMat = translate(auxModelMat, dvec3(100, 100, 100));

		//Realizamos la rotación asociada a la animación.		
		auxModelMat = rotate(auxModelMat, radians(this->angle + 20), dvec3(0, 1, 0)); //Rotamos en el eje Y.
		auxModelMat = rotate(auxModelMat, radians(this->angle), dvec3(0, 0, 1)); //Rotamos en el eje Z.

		texture.bind(GL_REPLACE);				//Importante para añadir la textura.

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

		//Renderizamos solo el exterior.
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		texture.bind(GL_REPLACE);				//Importante para añadir la textura.
		uploadMvM(modelViewMat);
		mesh->render();  //Dibujamos el cubo.
		auxiliarMesh->render();
		texture.unbind();

		//Renderizamos el interior.
		glCullFace(GL_BACK);
		textureAux.bind(GL_REPLACE);				//Importante para añadir la textura.
		uploadMvM(modelViewMat);
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

		dmat4 auxModelMat = modelViewMat;

		//Traslación para la animación 3D
		auxModelMat = translate(auxModelMat, dvec3(150, 150, 0));

		texture.bind(GL_REPLACE);				//Importante para añadir la textura.
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

		dmat4 auxModelMat = modelViewMat;

		//Traslación para centrar el cangilon.
		auxModelMat = translate(auxModelMat, dvec3(-w / 2, -h / 2, -w / 2));

		//Traslación para que realice la animación.
		//GLdouble R = pos;
		auxModelMat = translate(auxModelMat, dvec3(this->pos*cos(radians(this->angle)), this->pos*sin(radians(this->angle)), 0));

		//Renderizamos solo el interior.
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		textureAux.bind(GL_REPLACE);				//Importante para añadir la textura.
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

		dmat4 auxModelMat = modelViewMat;
		glColor3d(0, 0, 0);

		//Realizamos la rotación para que en lugar de estar alineado con el eje z, lo esté con el eje x.
		auxModelMat = rotate(auxModelMat, radians(90.0), dvec3(0, 1, 0));

		//Rotación asociada al giro de las aspas.
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

Rotor::Rotor(GLdouble r, GLdouble w, bool clockwise)
{	
	this->r = r;
	this->w = w;
	this->angle = 0;
	this->incrAngle = clockwise ? -3 : 3;
}

Rotor::~Rotor()
{
	delete mesh; mesh = nullptr;
}

void Rotor::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {

		uploadMvM(modelViewMat);

		// Pintamos el cilindro que hace de contorno del aspa
		glColor3f(1.0, 0.0, 0.0);
		//gluQuadricDrawStyle(q, GLU_LINE);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluCylinder(q, r, r, w, 50, 50);

		// Devolvemos el color al por defecto 
		//glColor3f(1.0, 1.0, 1.0);

		//Rotacion del aspa 
		//
		//

		//uploadMvM(auxModelMat);

		//glColor3d(0.0, 0.0, 0.0);
		//mesh->render();
		//glColor3d(1.0, 1.0, 1.0);

	}
}

void Rotor::update() {
	//this->angle += this->incrAngle;
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
}

void Chasis::render(dmat4 const &modelViewMat)
{
	if (mesh != nullptr) {

		dmat4 auxModelMat = modelViewMat;
		glColor3d(0, 0, 1);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Reestablecemos la opción por defecto.

		//Traslación para ubicar el objeto de modo que el centro esté en 0,0,0
		auxModelMat = translate(auxModelMat, dvec3(-this->escW / 2, -this->escH/2, -this->escW/2));

		//Escalamos tal y como corresponda.
		auxModelMat = scale(auxModelMat, dvec3(this->escW, this->escH, this->escW));

		uploadMvM(auxModelMat);
		mesh->render();
		auxiliarMesh->render();
		auxiliarMesh2->render();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reestablecemos la opción por defecto
	}
}

void Chasis::update() {
	//this->angle += this->incrAngle;
}

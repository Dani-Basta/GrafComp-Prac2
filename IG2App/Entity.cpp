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

		dmat4 auxModelMat = dmat4 const &modelViewMat;

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

Cubo3D::Cubo3D(GLdouble l) : Entity()
{
	mesh = Mesh::generaContCubo(l);
	auxiliarMesh = Mesh::generaSueloCubo(l);
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

CajaTexCor::CajaTexCor(GLdouble l) : Entity()
{
	mesh = Mesh::generaCajaTexCor(l);
	auxiliarMesh = Mesh::generaSueloTexCor(l);
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

void Foto::render(Camera const& cam)
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
//------------------------------------------------------------------------

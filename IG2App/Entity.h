//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Pixmap32RGBA.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
	Entity() : modelMat(1.0) { }; 
	virtual ~Entity() { };

	virtual void render(glm::dmat4 const &modelViewMat) = 0;	  
	virtual void update();


	// modeling matrix
	glm::dmat4 const& getModelMat() const { return modelMat; };

	void setModelMat(glm::dmat4 const& aMat) { modelMat = aMat; }
  
protected:

	//Objeto que se usará para dibujar las texturas.
	Texture texture;
	Texture textureAux; //Cargará una segunda textura.

	Mesh* mesh = nullptr;   // surface mesh
	Mesh* auxiliarMesh = nullptr; // mesh auxiliar para dibujar el rectángulo que será el suelo de la caja.
	Mesh* auxiliarMesh2 = nullptr; 

	glm::dmat4 modelMat;    // modeling matrix

	// transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//------------------------ENTIDADES CUÁDRICAS------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


class QuadricEntity : public Entity 
{
public:
	QuadricEntity()  { q = gluNewQuadric(); };
	~QuadricEntity() { gluDeleteQuadric(q); };
protected:
	GLUquadricObj* q;
};

//-------------------------------------------------------------------------

class Sphere : public QuadricEntity 
{
public:
	Sphere(GLdouble r); // r is the radius of the sphere
	void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble r;
};

//-------------------------------------------------------------------------

class Cylinder : public QuadricEntity 
{
public:
	Cylinder(GLdouble r1, GLdouble r2, GLdouble h); // r is the radius of the sphere
	void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble r1, r2, h;
};

//-------------------------------------------------------------------------

class Disk : public QuadricEntity 
{
public:
	Disk(GLdouble r1, GLdouble r2); // r is the radius of the sphere
	void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble r1, r2;
};

//-------------------------------------------------------------------------

class PartialDisk : public QuadricEntity 
{
public:
	PartialDisk(GLdouble r1, GLdouble r2, GLdouble ini, GLdouble fin); // r is the radius of the sphere
	void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble r1, r2, ini, fin;
};


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


/*
Para cada objeto que vaya a ser una entidad, hay que implementar una clase con la siguiente forma.
De forma general, vamos a ubicarlo en el centro (0,0,0). En el caso de que queramos ubicarlo en otra
posición, lo ubicamos en el centro y lo desplazamos en el render.
*/

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
	EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------

//POLIESPIRAL

class Poliespiral : public Entity
{
public:
	Poliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------

//DRAGON

class Dragon : public Entity
{
public:
	Dragon(GLuint numVert);
	~Dragon();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------

//TRIANGULO RGB

class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLdouble r);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------

//RECTANGULO RGB

class RectanguloRGB : public Entity
{
public:
	RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------

//TRIANGULO ANIMADO

class TrianguloAnimado : public Entity
{
protected:
	GLdouble grades = 0;
	GLdouble incrGr = 3;
	GLdouble x;
	GLdouble y;

public:
	TrianguloAnimado(GLdouble r, GLdouble x, GLdouble y, GLdouble gradeIncr);
	~TrianguloAnimado();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------

//ESTRELLA 3D

class Estrella3D: public Entity
{
protected:
	GLdouble angle;
	GLdouble incrAngle;

public:
	Estrella3D(GLdouble re, GLdouble np, GLdouble h, GLdouble ri);
	~Estrella3D();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();
};

//-------------------------------------------------------------------------

//CUBO 3D

class Cubo3D : public Entity
{
public:
	Cubo3D(GLdouble h, GLdouble w);
	~Cubo3D();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();
};

//-------------------------------------------------------------------------

//CUBO 3D

class CuboTapado : public Entity
{
public:
	CuboTapado(GLdouble h, GLdouble w);
	~CuboTapado();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();
};

//-------------------------------------------------------------------------


//RECTANGULO TEXCOR

class RectanguloTexCor : public Entity
{
public:
	RectanguloTexCor(GLdouble w, GLdouble h, GLuint	rw, GLuint rh);
	~RectanguloTexCor();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();
};

//-------------------------------------------------------------------------


//ESTRELLA TEXCOR

class EstrellaTexCor : public Entity
{
protected:
	GLdouble angle;
	GLdouble incrAngle;

public:
	EstrellaTexCor(GLdouble r, GLdouble nL, GLdouble h, GLdouble ri);
	~EstrellaTexCor();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();
};

//-------------------------------------------------------------------------

//CAJA TEXCOR
class CajaTexCor : public Entity
{

public:
	CajaTexCor(GLdouble h, GLdouble w);
	~CajaTexCor();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();
};

//-------------------------------------------------------------------------


//FOTO

class Foto : public Entity
{

public:
	Foto();
	~Foto();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();
};



//-------------------------------------------------------------------------
/*


	PARTE 2 DE LA ASIGNATURA.


*/
//-------------------------------------------------------------------------


//CANGILON	

class Cangilon : public CajaTexCor
{
protected:
	GLdouble w, h;
	GLdouble pos; //Posición en el eje X que estará la caja.
	GLdouble angle, incrAngle;

public:
	Cangilon(GLdouble h, GLdouble w, GLdouble pos, GLdouble grade);
	~Cangilon();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();
};

//-------------------------------------------------------------------------

//Aspa Noria

class AspaNoria : public Cubo3D
{
protected:
	GLdouble hc;		//Altura del cangilon asociado a las aspas.
	GLdouble wc;		//Anchura del cangilon asociado a las aspas.
	GLdouble esc;		//Factor de escalado.
	GLdouble angle, incrAngle;
public:
	AspaNoria(GLdouble h, GLdouble w, GLdouble hc, GLdouble wc, GLdouble esc, GLdouble grade);
	~AspaNoria();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();
};

//-------------------------------------------------------------------------

//ROTOR

class Rotor : public QuadricEntity 
{
protected:
	GLdouble r, w;
	GLdouble angle;
	GLdouble incrAngle;
	bool forceColor;
	Cylinder *cil;
public:
	Rotor(GLdouble r, GLdouble w, bool clockwise, bool forceColor); // r is the radius of the sphere
	~Rotor();
	void render(glm::dmat4 const& modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------


//CHASIS

class Chasis : public CuboTapado
{
protected:
	GLdouble escH;		//Factor de escalado en altura.
	GLdouble escW;		//Factor de escalado en anchura.

public:
	Chasis(GLdouble escH, GLdouble escW);
	~Chasis();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();

};

//DRON

class Dron : public Entity
{
protected:
	GLdouble escH;		//Factor de escalado en altura.
	GLdouble escW;		//Factor de escalado en anchura.
	GLdouble r, w;
	Chasis* chasis = nullptr;
	Rotor *rot1 = nullptr, *rot2 = nullptr, *rot3 = nullptr, *rot4 = nullptr;
public:
	Dron(GLdouble r, GLdouble w, GLdouble escH, GLdouble escW);
	~Dron();
	virtual void render(glm::dmat4 const &modelViewMat);
	virtual void update();

};

#endif //_H_Entities_H_
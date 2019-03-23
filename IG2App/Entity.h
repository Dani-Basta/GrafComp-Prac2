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

	//Objeto que se usar� para dibujar las texturas.
	Texture texture;
	Texture textureAux; //Cargar� una segunda textura.

	Mesh* mesh = nullptr;   // surface mesh
	Mesh* auxiliarMesh = nullptr; // mesh auxiliar para dibujar el rect�ngulo que ser� el suelo de la caja.

	glm::dmat4 modelMat;    // modeling matrix

	// transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//------------------------ENTIDADES CU�DRICAS------------------------------
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
posici�n, lo ubicamos en el centro y lo desplazamos en el render.
*/

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
	EjesRGB(glm::GLdouble l);
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
	Cubo3D(GLdouble l);
	~Cubo3D();
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
	CajaTexCor(GLdouble l);
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

//CANGILON	

class Cangilon : public CajaTexCor
{
protected:
	GLdouble angle;
	GLdouble incrAngle;
public:
	Cangilon(GLdouble l);
	~Cangilon();
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

public:
	Rotor(GLdouble r, GLdouble w); // r is the radius of the sphere
	void render(glm::dmat4 const& modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------


#endif //_H_Entities_H_
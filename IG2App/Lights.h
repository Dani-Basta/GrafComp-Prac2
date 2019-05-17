//#pragma once
#ifndef _H_Lights_H_
#define _H_Lights_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Pixmap32RGBA.h"
#include <vector>

static GLuint cont = 0; // Para generar un nuevo id cada vez

class Light { // Abstract class
protected:
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // id no válido
	// Atributos lumínicos y geométrico de la fuente de luz
	glm::fvec4 ambient = { 0.1, 0.1, 0.1, 1 };
	glm::fvec4 diffuse = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };

	glm::fvec4 posDir = { 0, 0, 1, 0 };

public:
	Light(void);
	virtual ~Light(void) { disable(); }

	GLuint getId(void);

	void uploadL(void);
	void disable(void);
	void enable(void);

	virtual void upload(glm::dmat4 const& modelViewMat) = 0;

	// Añade setter’s para cambiar el valor de los atributos lumínicos

	void setAmbient (glm::fvec4 nuevo) { this->ambient  = nuevo; uploadL(); };
	void setDiffuse (glm::fvec4 nuevo) { this->diffuse  = nuevo; uploadL(); };
	void setSpecular(glm::fvec4 nuevo) { this->specular = nuevo; uploadL(); };

};

//-------------------------------------------------------------------------

class DirLight : public Light {
public:
	void upload(glm::dmat4 const& modelViewMat);
	void setPosDir(glm::fvec3 dir);
};

//-------------------------------------------------------------------------

class PosLight : public Light {
protected:
	// Factores de atenuación
	GLfloat kc = 1, kl = 0, kq = 0;
public:
	void upload(glm::dmat4 const& modelViewMat);
	void setPosDir(glm::fvec3 dir);
	void setAttr(GLfloat kc, GLfloat kl, GLfloat kq) {
		this->kc = kc;
		this->kl = kl;
		this->kq = kq;
	}
};

//-------------------------------------------------------------------------

class SpotLight : public PosLight  {
protected:
	// Atributos del foco
	//Hacia dónde mira el foco, un vector
	glm::fvec4 direction = { 0, 0, -1, 0 };
	//Apertura del ángulo del foco
	GLfloat cutoff = 45;
	// Grado de atenuación al alejarse del centro del foco
	GLfloat exp = 0;
	/* En este tipo de luz no tiene sentido 
	*/
public:
	SpotLight(glm::fvec3 pos = { 0, 0, 0 } ) : PosLight() {
		posDir = glm::fvec4(pos, 1.0);
	};
	void upload(glm::dmat4 const& modelViewMat);
	void setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e);
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Material {
protected:
	// Coeficientes de reflexión
	glm::fvec4 ambient = { 0.2, 0.2, 0.2, 1.0 };
	glm::fvec4 diffuse = { 0.8, 0.8, 0.8, 1.0 };
	glm::fvec4 specular = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat expF = 0; // Exponente para la reflexión especular
	GLuint face = GL_FRONT_AND_BACK;
	GLuint sh = GL_SMOOTH; // Tipo de matizado
public:
	const enum mater {
		Copper, BPlastic,Brass,Bronze,Chrome,Gold,Pewter,Silver,PolSilver 
	};
	Material(void) {};
	Material(mater tipo);
	virtual ~Material(void) {};
	void upload(void);
	void setCopper(void);
	void setBlackPlastic(void);
	void setBrass(void);
	void setBronze(void);
	void setChrome(void);
	void setGold(void);
	void setPewter(void);
	void setSilver(void);
	void setPolishedSilver(void);
};

//-------------------------------------------------------------------------

#endif //_H_Lights_H_


//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
//#include "Mesh.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
public:
    Scene() { };
	~Scene();
	void init2D(void);
	void init3D(void);
	void noria(int n);
	void esferaRev(void);
	void init(void);
	void dronDrones(void);

    void render(glm::dmat4 const &modelViewMat);
	void update(GLuint timeElapsed);
	void update(void);

	void move(int key);

protected:
	GLuint time = 0;

	GLuint umbral = 50;

	std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene
	EsferaDron* esfera;  // Entities (graphics objects) of the scene
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_


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
	void init2D();
	void init3D();
	void noria(int n);
	void prac2();

    void render(glm::dmat4 const &modelViewMat);
	void update(GLuint timeElapsed);
	void update();

protected:

	  std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_


//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

#include "Camera.h"
#include "Entity.h"
//#include "Mesh.h"
#include "Lights.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	: CompoundEntity {
protected:
	GLuint time = 0;

	GLuint umbral = 50;

	//std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene
	EsferaDron* esfera;  // Entities (graphics objects) of the scene

	std::vector<Light*> lights;

	//Light* ambGlo;

public:
    Scene() : esfera(nullptr){ 
		
	};
	~Scene();
	void init2D(void);
	void init3D(void);
	void noria(int n);
	void apagarLuces();
	void esferaRev(void);
	void esferaMateriales(int color);
	void init(void);
	void dronDrones(void);

    void render(glm::dmat4 const &modelViewMat);
	void update(GLuint timeElapsed);
	void update(void);

	void move(int key);

};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_


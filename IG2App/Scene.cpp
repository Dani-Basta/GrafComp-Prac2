#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

GLuint time = 0;

GLuint umbral = 50;


//-------------------------------------------------------------------------

//Escena 2D.
void Scene::init2D() {
	// OpenGL basic setting

	//Eliminamos los objetos que habia antes.
	grObjects.clear();


	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	//glEnable(GL_TEXTURE_2D);

	// lights
	// textures  
	// meshes

	// Graphics objects (entities) of the scene
	grObjects.push_back(new EjesRGB(200.0));

	//Escena 2D
	grObjects.push_back(new Poliespiral(dvec2(0, 0), 0, 160, 1, 1, 50));
	grObjects.push_back(new Dragon(3000));
	grObjects.push_back(new TrianguloRGB(50));
	grObjects.push_back(new RectanguloRGB(30, 20));
	grObjects.push_back(new TrianguloAnimado(40, 0, 0, 15));
}


//Escena 3D
void Scene::init3D() {
	// OpenGL basic setting

	grObjects.clear();


	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

	// lights
	// textures  
	// meshes
	
	// Graphics objects (entities) of the scene
	grObjects.push_back(new EjesRGB(200.0));

	//Escena 3D	
	
	//grObjects.push_back(new RectanguloTexCor(500, 200, 2, 3));
	grObjects.push_back(new EstrellaTexCor(60, 8, 30, 30));
	grObjects.push_back(new CajaTexCor(60));
	
	grObjects.push_back(new Foto());


}

//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources   
  
  for (Entity* el: grObjects)
  {
	  delete el;  el = nullptr;
  }
}
//-------------------------------------------------------------------------

void Scene::render(dmat4 const &modelViewMat)
{
	for (Entity* el: grObjects)
	{
		el->render(modelViewMat);
	}
}
//-------------------------------------------------------------------------

void Scene::update()
{
	for (Entity* el : grObjects)
	{
		el->update();
	}
}
//-------------------------------------------------------------------------

void Scene::update(GLuint timeElapsed)
{
	if (timeElapsed - time > umbral) {
		for (Entity* el : grObjects)
		{
			el->update();
		}
		time = timeElapsed;
	}

}
//-------------------------------------------------------------------------



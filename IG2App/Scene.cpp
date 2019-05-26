#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources   
	for (Light* li : lights) {
		li->disable();
		delete li;  li = nullptr;
	}
	for (Entity* el : grObjects) {
		delete el;  el = nullptr;
	}
	if (this->cameraLight != nullptr) {
		cameraLight->disable();
		delete cameraLight; cameraLight = nullptr;
	}
		
}

//-------------------------------------------------------------------------

void Scene::render(dmat4 const& modelViewMat) {
	encenderLuces();

	if (this->cameraLight != nullptr) {
		cameraLight->upload(dmat4(1.0));
	}

	for (Light* li : lights)
		li->upload(modelViewMat);

	__super::render(modelViewMat);

	/*
	for (Entity* el: grObjects)
	{
		el->render(modelViewMat);
	}*/
}

//-------------------------------------------------------------------------

void Scene::update() {
	__super::update();
	/*
	for (Entity* el : grObjects)
	{
		el->update();
	}
	*/
}

//-------------------------------------------------------------------------

void Scene::update(GLuint timeElapsed) {
	if (timeElapsed - time > umbral) {
		__super::update();
		time = timeElapsed;
	}

	if (this->cameraLight != nullptr) 
		cameraLight->enable();

}

//-------------------------------------------------------------------------

void Scene::apagarLuces() {
	for (Light* li : lights)
		li->disable();
	if (this->cameraLight != nullptr)
		cameraLight->disable();
}

//-------------------------------------------------------------------------

void Scene::encenderLuces() {
	for (Light* li : lights)
		li->enable();
	if (this->cameraLight != nullptr)
		cameraLight->enable();
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

void Scene::move(int key) {
	if (esfera != nullptr)
		this->esfera->move(key);
}

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


void Scene::myScene() {
	grObjects.clear();

	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_NORMALIZE);


	//Añadimos una luz que apunte a (1,1,0). DIRLIGHT APUNTA DEL INFINITO A (1,1,0).
	/*
	DirLight* light = new DirLight();
	light->setDiffuse(fvec4(1.0, 1.0, 1.0, 1.0));
	light->setAmbient(fvec4(0.2, 0.2, 0.2, 1.0));
	light->setSpecular(fvec4(0.5, 0.5, 0.5, 1.0));

	light->setPosDir(fvec3(1, 1, 0));

	lights.push_back(light);
	//*/
	//APARTADOS


	//Dron de drones
	//grObjects.push_back(new DronDrones(35, 15, 30, 200));

	//Esfera por revolución
	//grObjects.push_back(new Esfera(100, 100, 100));

	//Esfera de materiales
	/*
	Esfera* esf =
		//new Esfera(100, 100, 100, Material::Copper);
		//new Esfera(100, 100, 100, Material::Gold);
		new Esfera(100, 100, 100, Material::Silver);

	grObjects.push_back(esf);
	*/

	//Foco en la cámara
	/*
	this->cameraLight = new SpotLight();
	this->cameraLight->setDiffuse(fvec4(0.4, 0.8, 0.0, 1.0));
	this->cameraLight->setSpecular(fvec4(0.5, 0.5, 0.5, 1.0));

	this->cameraLight->setAmbient(fvec4(0.0, 0.0, 0.0, 1.0));

	this->cameraLight->setPosDir(fvec3(0, 0, -1));
	this->cameraLight->setSpot(fvec3(0, 0, -1), 8, 0);

	this->cameraLight->enable();

	Esfera* esf =
		//new Esfera(200, 100, 100, Material::Copper);
		new Esfera(200, 100, 100, Material::Gold);
	//new Esfera(200, 100, 100, Material::Silver);

	grObjects.push_back(esf);

	*/

	//Dron con foco
	//*	
	SpotLight* dronLight = new SpotLight();
	dronLight->setDiffuse(fvec4(1.0, 1.0, 1.0, 1.0));
	dronLight->setSpecular(fvec4(0.5, 0.5, 0.5, 1.0));
	dronLight->setAmbient(fvec4(0.0, 0.0, 0.0, 1.0));

	dronLight->setPosDir(fvec3(-1000, 1000, -1000));
	dronLight->setSpot(fvec3(0, -1, 0), 45, 0);

	dronLight->enable();
	
	esfera =
		//new EsferaDron(200, 100, 100, Material::Copper);
		new EsferaDron(200, 100, 100, Material::Gold, dronLight);
	//new EsferaDron(200, 100, 100, Material::Silver);

	grObjects.push_back(esfera);
	//*/


	grObjects.push_back(new EjesRGB(300.0));
}

/*
//Escena 2D.
void Scene::init2D() {
	// OpenGL basic setting
	lights.clear();
	//Eliminamos los objetos que habia antes.
	grObjects.clear();

	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	//glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);

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
*/
//-------------------------------------------------------------------------
/*
//Escena 3D
void Scene::init3D() {
	// OpenGL basic setting
	lights.clear();
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
	grObjects.push_back(new CajaTexCor(60,60));
	
	grObjects.push_back(new Foto());


}
*/
//-------------------------------------------------------------------------

void Scene::noria(int n) {
	lights.clear();
	grObjects.clear();


	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

	grObjects.push_back(new EjesRGB(200.0));

	//int n = 10;
	GLdouble gradesIncr = 360 / n;
	GLdouble grades = 0;

	for (int i = 0; i < n; i++) {
		grObjects.push_back(new Cangilon(80, 90, 250, grades));
		grObjects.push_back(new AspaNoria(10, 5, 80, 90, 50, grades));
		grades = grades + gradesIncr;
	}
}


//-------------------------------------------------------------------------
/*
void Scene::init() {
	lights.clear();
	grObjects.clear();


	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

	grObjects.push_back(new EjesRGB(300.0));

	this->esfera = new EsferaDron(200, 51, 51);
	grObjects.push_back(this->esfera);

}
*/
//-------------------------------------------------------------------------

void Scene::dronDrones() {
	lights.clear();
	grObjects.clear();


	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

	grObjects.push_back(new EjesRGB(300.0));

	//grObjects.push_back(new Rotor(100, 50, true));
	//grObjects.push_back(new Dron(40, 15, 30, 250));
	grObjects.push_back(new DronDrones(35, 15, 30, 200));

}

//-------------------------------------------------------------------------

void Scene::esferaRev() {
	lights.clear();
	grObjects.clear();

	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)

	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_NORMALIZE);


	//lights.push_back( ambGlo );
	DirLight* light = new DirLight();
	light->setDiffuse(fvec4(1.0, 1.0, 1.0, 1.0));
	light->setAmbient(fvec4(0.2, 0.2, 0.2, 1.0));
	light->setSpecular(fvec4(0.5, 0.5, 0.5, 1.0));

	light->setPosDir(fvec3(1, 1, 0));


	lights.push_back(light);

	grObjects.push_back(new EjesRGB(300.0));

	//grObjects.push_back(new CuboTapado(10, 100));
	//grObjects.push_back(new Rotor(100, 50, true));
	//grObjects.push_back(new Chasis(10,100));
	//grObjects.push_back(new Dron(40, 15, 30, 250));
	//grObjects.push_back( new Cone(250, 150) );

	grObjects.push_back(new Esfera(100, 100, 100));

	//encenderLuces();
}

//-------------------------------------------------------------------------

void Scene::esferaMateriales() {
	apagarLuces();
	lights.clear();
	grObjects.clear();

	glDisable(GL_COLOR_MATERIAL);

	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)

	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_NORMALIZE);

	DirLight* light = new DirLight();

	light->setDiffuse(fvec4(1.0, 1.0, 1.0, 1.0));
	light->setAmbient(fvec4(0.2, 0.2, 0.2, 1.0));
	light->setSpecular(fvec4(0.5, 0.5, 0.5, 1.0));

	light->setPosDir(fvec3(1, 1, 0));

	lights.push_back(light);

	grObjects.push_back(new EjesRGB(300.0));

	Esfera* esf = 
		//new Esfera(100, 100, 100, Material::Copper);
		//new Esfera(100, 100, 100, Material::Gold);
		new Esfera(100, 100, 100, Material::Silver);

	grObjects.push_back(esf);

	//encenderLuces();
}

//-------------------------------------------------------------------------

void Scene::esferaMinero() {
	apagarLuces();
	lights.clear();
	grObjects.clear();

	glDisable(GL_COLOR_MATERIAL);

	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)

	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_NORMALIZE);

	this->cameraLight = new SpotLight();
	this->cameraLight->setDiffuse(fvec4(0.4, 0.8, 0.0, 1.0));
	this->cameraLight->setSpecular(fvec4(0.5, 0.5, 0.5, 1.0));

	this->cameraLight->setAmbient(fvec4(0.0, 0.0, 0.0, 1.0));

	this->cameraLight->setPosDir(fvec3(0,0,-1));
	this->cameraLight->setSpot(fvec3(0, 0, -1), 8, 0);

	this->cameraLight->enable();

	/*
	DirLight* light = new DirLight();

	light->setDiffuse(fvec4(1.0, 1.0, 1.0, 1.0));
	light->setAmbient(fvec4(0.2, 0.2, 0.2, 1.0));
	light->setSpecular(fvec4(0.5, 0.5, 0.5, 1.0));

	light->setPosDir(fvec3(1, 1, 0));
	
	light->enable();

	lights.push_back(light);
	*/

	grObjects.push_back(new EjesRGB(300.0));

	Esfera* esf = 
		//new Esfera(100, 100, 100, Material::Copper);
		new Esfera(200, 100, 100, Material::Gold);
		//new Esfera(100, 100, 100, Material::Silver);

	grObjects.push_back(esf);

	//encenderLuces();
}

//-------------------------------------------------------------------------

void Scene::dronMinero() {
	apagarLuces();
	lights.clear();
	grObjects.clear();

	glDisable(GL_COLOR_MATERIAL);

	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)

	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_NORMALIZE);

	SpotLight* dronLight = new SpotLight();
	dronLight->setDiffuse(fvec4(1.0, 1.0, 1.0, 1.0));
	dronLight->setSpecular(fvec4(0.5, 0.5, 0.5, 1.0));
	dronLight->setAmbient(fvec4(0.0, 0.0, 0.0, 1.0));

	dronLight->setPosDir(fvec3(-1000, 1000, -1000));
	dronLight->setSpot(fvec3(0, -1, 0), 45, 0);

	dronLight->enable();

	/*
	DirLight* light = new DirLight();
	light->setDiffuse(fvec4(1.0, 1.0, 1.0, 1.0));
	light->setAmbient(fvec4(0.2, 0.2, 0.2, 1.0));
	light->setSpecular(fvec4(0.5, 0.5, 0.5, 1.0));

	light->setPosDir(fvec3(100, 100, 0));

	lights.push_back(light);
	//*/

	grObjects.push_back(new EjesRGB(300.0));

	esfera =
		//new EsferaDron(200, 100, 100, Material::Copper);
		new EsferaDron(200, 200, 200, Material::Gold, dronLight);
	//new EsferaDron(200, 100, 100, Material::Silver);

	grObjects.push_back(esfera);
	//grObjects.push_back(new Rotor(100, 50, true, dvec3(1.0, 0.0, 0.0)));

	encenderLuces();
}

//-------------------------------------------------------------------------
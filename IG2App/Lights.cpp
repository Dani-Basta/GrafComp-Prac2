#include "Lights.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

Light::Light() {
	if (cont < GL_MAX_LIGHTS) {
		this->id = GL_LIGHT0 + cont;
		cont++;
		glEnable(id);
	}
};

void Light::uploadL() {
	// Transfiere las características de la luz a la GPU
	glLightfv(id, GL_AMBIENT, value_ptr(ambient));
	glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(id, GL_SPECULAR, value_ptr(specular));
}

void Light::disable() { 
	if (id < GL_LIGHT0 + GL_MAX_LIGHTS) 
		glDisable(id); 
};

void Light::enable() { 
	if (id < GL_LIGHT0 + GL_MAX_LIGHTS) 
		glEnable(id); 
};


//-------------------------------------------------------------------------

void DirLight::upload(glm::dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, value_ptr(posDir));
	uploadL();
}

void DirLight::setPosDir(glm::fvec3 dir) {
	posDir = fvec4(dir, 0.0);
}

//-------------------------------------------------------------------------

void PosLight::upload(glm::dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, value_ptr(posDir));
	glLightf(id, GL_CONSTANT_ATTENUATION, kc);
	glLightf(id, GL_LINEAR_ATTENUATION, kl);
	glLightf(id, GL_QUADRATIC_ATTENUATION, kq);
	uploadL();
}

void PosLight::setPosDir(fvec3 dir) {
	posDir = fvec4(dir, 1.0);
}

//-------------------------------------------------------------------------

void SpotLight::upload(dmat4 const& modelViewMat) {
	PosLight::upload(modelViewMat);
	glLightfv(id, GL_SPOT_DIRECTION, value_ptr(direction));
	glLightf(id, GL_SPOT_CUTOFF, cutoff);
	glLightf(id, GL_SPOT_EXPONENT, exp);
}

void SpotLight::setSpot(fvec3 dir, GLfloat cf, GLfloat e) {
	direction = fvec4(dir, 0.0);
	cutoff = cf;
	exp = e;
}

//-------------------------------------------------------------------------

void Material::upload() {
	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
	glShadeModel(sh);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE); // Defecto
}

void Material::setBlackPlastic(void) {
	ambient = { 0.0, 0.0, 0.0, 1 };
	diffuse = { 0.01, 0.01, 0.01, 1 };
	specular = { 0.5, 0.5, 0.5, 1 };
	expF = 32.0;
}

void Material::setBrass(void) {
	ambient = { 0.329412, 0.223529, 0.027451, 1 };
	diffuse = { 0.780392, 0.568627, 0.113725, 1 };
	specular = { 0.992157, 0.941176, 0.807843, 1 };
	expF = 27.8974;
}

void Material::setBronze(void) {
	ambient = { 0.2125, 0.1275, 0.054, 1 };
	diffuse = { 0.714, 0.4284, 0.18144, 1 };
	specular = { 0.393548, 0.271906, 0.166721, 1 };
	expF = 25.6;
}

void Material::setChrome(void) {
	ambient = { 0.25, 0.25, 0.25, 1 };
	diffuse = { 0.4, 0.4, 0.4, 1 };
	specular = { 0.774597, 0.774597, 0.774597, 1 };
	expF = 76.8;
}

void Material::setCopper() {
	ambient = { 0.19125, 0.0735, 0.0225, 1 };
	diffuse = { 0.7038, 0.27048, 0.0828, 1 };
	specular = { 0.256777, 0.137622, 0.086014, 1 };
	expF = 12.8;
}

void Material::setGold(void) {
	ambient = { 0.24725, 0.1995, 0.0745, 1 };
	diffuse = { 0.75164, 0.60648, 0.22648, 1 };
	specular = { 0.628281, 0.555802, 0.366065, 1 };
	expF = 51.2;
}

void Material::setPewter(void) {
	ambient = { 0.10588, 0.058824, 0.113725, 1 };
	diffuse = { 0.427451, 0.470588, 0.541176, 1 };
	specular = { 0.3333, 0.3333, 0.521569, 1 };
	expF = 9.84615;
}

void Material::setSilver(void) {
	ambient = { 0.19225, 0.19225, 0.19225, 1 };
	diffuse = { 0.50754, 0.50754, 0.50754, 1 };
	specular = { 0.508273, 0.508273, 0.508273, 1 };
	expF = 51.2;
}

void Material::setPolishedSilver(void) {
	ambient = { 0.23125, 0.23125, 0.23125, 1 };
	diffuse = { 0.2775, 0.2775, 0.2775, 1 };
	specular = { 0.773911, 0.773911, 0.773911, 1 };
	expF = 89.6;
}

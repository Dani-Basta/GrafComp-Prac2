#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_access.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Camera::set2D() 
{
	this->eye = dvec3(0, 0, 500);
	this->look = dvec3(0, 0, 0);
	this->up = dvec3(0, 1, 0);
	//this->viewMat = lookAt(eye, look, up);

	setVM();
}

//-------------------------------------------------------------------------

void Camera::set3D() 
{
	this->ang = -45;
	GLdouble frente = this->radio*cos(radians(this->ang));
	this->eye = dvec3(frente, frente, frente);
	this->look= dvec3(0, 10, 0);
	this->up= dvec3(0, 1, 0);
	//this->viewMat = lookAt(eye, look, up);

	setVM();	
}

//-------------------------------------------------------------------------

void Camera::setCenital()
{
	this->ang = -90;
	this->eye = dvec3(0, this->radio, 0);
	this->look = dvec3(0, 0, 0);
	this->up = dvec3(0, 0, -1);

	//this->viewMat = lookAt(eye, look, up);

	setVM();
}

//-------------------------------------------------------------------------

void Camera::uploadVM() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(viewMat));
}

//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
	this->viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}

//-------------------------------------------------------------------------

void Camera::yaw(GLdouble a)
{
	this->viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}

//-------------------------------------------------------------------------

void Camera::roll(GLdouble a)
{
	this->viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}

//-------------------------------------------------------------------------

void Camera::uploadSize(GLdouble aw, GLdouble ah)
{
	this->xRight = aw / 2.0;
	this->xLeft = -xRight;
	this->yTop = ah / 2.0;
	this->yBot = -yTop;
	//projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);

	uploadPM();
}

//-------------------------------------------------------------------------

void Camera::uploadScale(GLdouble s)
{
	factScale -= s;
	if (factScale < 0) 
		factScale = 0.01;
	uploadPM();
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

void Camera::changeProj(void) {
	this->orto = !this->orto;
	uploadPM();
}

//-------------------------------------------------------------------------

void Camera::setAxes(void){
	u = row(viewMat,0);
	v = row(viewMat, 1);
	front = -row(viewMat, 2);
}

//-------------------------------------------------------------------------

void Camera::setVM(void) {
	this->viewMat = lookAt(eye, look, up);
	setAxes();
}

//-------------------------------------------------------------------------

void Camera::uploadPM() 
{
	if (this->orto) {
		this -> nearVal = 1.0;
		this -> projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	}
	else {
		this -> nearVal = 2 * yTop;
		this -> projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	}
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(projMat));
	glMatrixMode(GL_MODELVIEW);
}

//-------------------------------------------------------------------------

void Camera::moveLR(GLdouble cs) {
	this->eye += u * cs;
	this->look += u * cs;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::moveFB(GLdouble cs) {
	this->eye += this->front * cs;
	this->look += this->front * cs;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::moveUD(GLdouble cs) {
	this->eye += v * cs;
	this->look += v * cs;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::lookLR(GLdouble cs) {
	this->look += u * cs;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::lookUD(GLdouble cs) {
	this->look += v * cs;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::orbit(GLdouble ax) {
	this->ang += ax;
	this->eye.x = look.x + cos(radians(ang)) * radio;
	this->eye.z = look.z - sin(radians(ang)) * radio;
	
	setVM();
}

//-------------------------------------------------------------------------

void Camera::orbit(GLdouble ax, GLdouble ay) {
	this -> ang += ax;
	this -> eye.x = look.x + cos(radians(ang)) * radio;
	this->eye.y += ay;
	this -> eye.z = look.z - sin(radians(ang)) * radio;
	
	setVM();
}
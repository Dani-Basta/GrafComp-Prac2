//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------




class Mesh 
{
public:

	//Para cada objeto que creemos, creamos su malla correspondiente (si corresponde). Introducir el método aquí.
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D RGB axes mesh
	static Mesh* generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	static Mesh* generaDragon(GLuint numVert); //Genera el dragón descrito en el enunciado.
	static Mesh* generaTriangulo(GLdouble r); //Genera un triangulo equilatero de radio r.
	static Mesh* generaTrianguloRGB(GLdouble r); //Genera un triangulo RGB utilizando generaTriangulo.
	static Mesh* generaRectangulo(GLdouble w, GLdouble h); //Genera un rectangulo 2D de altura h y anchura w.
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h); //Genera el rectangulo RGB utilizando la función generaRectangulo.
	static Mesh* generaEstrella3D(GLdouble re, GLdouble np, GLdouble h,GLdouble ri);  //Genera la estrella 3D descrita en el enunciado.
	static Mesh* generaContCubo(GLdouble l); //Para generar el cubo descrito en el enunciado.
	static Mesh* generaSueloCubo(GLdouble l); //Para generar el suelo (rectangulo) del cubo anterior.
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh); 
	static Mesh* generaEstrellaTexCor(GLdouble r, GLdouble nL, GLdouble	h, GLdouble ri);
	static Mesh* generaCajaTexCor(GLdouble l);
	static Mesh* generaSueloTexCor(GLdouble l);
	static Mesh*  generaFotoTex(GLdouble w, GLdouble h);

	Mesh(void) { };
	~Mesh(void);
	virtual void render();

	glm::dvec3* getVertices() { return vertices; };  // vertex array
	glm::dvec4* getColors() { return colors; };      // color array
   
protected:

	GLuint numVertices = 0;   // arrays size (number of elements)
	GLuint primitive = GL_TRIANGLES;  // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...

	glm::dvec3* vertices = nullptr;  // vertex array
	glm::dvec4* colors = nullptr;    // color array
	glm::dvec2* texCoords = nullptr; // array de coordenadas de textura.

};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_
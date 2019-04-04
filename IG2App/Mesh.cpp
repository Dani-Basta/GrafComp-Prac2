#include "Mesh.h"

constexpr double PI = 3.14159265;

using namespace glm;

//-------------------------------------------------------------------------

Mesh::~Mesh(void) 
{
  delete[] vertices;  vertices = nullptr;
  delete[] colors;    colors = nullptr;
}
//-------------------------------------------------------------------------

void Mesh::render()
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate, stride, pointer 
    }
	
	if (texCoords != nullptr) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
	}



    glDrawArrays(primitive, 0, numVertices);   // primitive graphic, first index and number of elements to be rendered

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);



  }
}
//-------------------------------------------------------------------------

/*
	A partir de aquí se definen las funciones que crearán las mallas. 

	Estás funciones las llamarán en entity.cpp.
*/


//-------------------------------------------------------------------------


Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* m = new Mesh();
  m->primitive = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  // X axis vertices
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  // Y axis vertices
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  // Z axis vertices
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  // X axis color: red  ( Alpha = 1 : fully opaque)
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}
//-------------------------------------------------------------------------

//POLIESPIRAL

Mesh * Mesh::generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert)
{
	GLdouble x, y;

	Mesh* m = new Mesh();
	m->primitive = GL_LINE_STRIP;
	m->numVertices = numVert;

	m->vertices = new dvec3[m->numVertices];


	//Asignamos una las posiciones de los distintos vértices de la malla.
	
	x = verIni.x;
	y = verIni.y;

	m->vertices[0] = dvec3(x, y, 0); //Es 2D, de modo que z sería 0.

	for (unsigned i = 1; i < m->numVertices; i++) {

		angIni += incrAng;
		ladoIni += incrLado;

		x += ladoIni * cos(radians(angIni));
		y += ladoIni * sin(radians(angIni));
		
		m->vertices[i] = dvec3(x, y, 0);
	}

	return m;
}
//-------------------------------------------------------------------------

//DRAGÓN

Mesh * Mesh::generaDragon(GLuint numVert)
{
	Mesh* m = new Mesh();
	m->primitive = GL_POINTS;
	m->numVertices = numVert;

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0.0, 0.0, 0.0);

	for (unsigned i = 1; i < numVert; i++) {
		if ((rand() / double(RAND_MAX)) < 0.787473)  // T1
			m->vertices[i] = dvec3(0.824074 * m->vertices[i - 1].x + 0.281482 * m->vertices[i - 1].y - 0.882290,
				-0.212346 * m->vertices[i - 1].x + 0.864198 * m->vertices[i - 1].y - 0.110607,
				0.0);
		else
			m->vertices[i] = dvec3(0.088272 * m->vertices[i - 1].x + 0.520988 * m->vertices[i - 1].y + 0.785360,
				-0.463889 * m->vertices[i - 1].x - 0.377778 * m->vertices[i - 1].y + 8.095795,
				0.0);

	}

	return m;

}
//-------------------------------------------------------------------------



/*
	GENERA UN TRIÁNGULO EQUILÁTERO DE RADIO R
*/


Mesh * Mesh::generaTriangulo(GLdouble r)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];

	//Los valores que utilizaremos para crear la circumferencia son los siguientes:
	dvec3 centro = dvec3(0.0, 0.0, 0.0);
	GLdouble angIni = 90;
	GLdouble incrAng = 120; //EQUIVALENTE A 360 % NUM VERTICES.
	GLdouble x, y;

	for (unsigned i = 0; i < m->numVertices; i++) {
		x = centro.x + r * cos(radians(angIni));
		y = centro.y + r * sin(radians(angIni));
		
		m->vertices[i] = dvec3(x, y, 0.0);
		
		angIni += incrAng;
	}

	return m;
}


Mesh* Mesh::generaTrianguloRGB(GLdouble r) { 
	Mesh* m = generaTriangulo(r);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1, 0, 0, 0);
	m->colors[1] = dvec4(0, 1, 0, 0);
	m->colors[2] = dvec4(0, 0, 1, 0);

	return m;
}

//-------------------------------------------------------------------------

/*
	GENERA UN RECTANGULO
*/


Mesh * Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;		//Los rectangulos tienen siempre 4 vértices.

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(-w / 2, +h / 2, 0.0);
	m->vertices[1] = dvec3(+w / 2, +h / 2, 0.0);
	m->vertices[2] = dvec3(-w / 2, -h / 2, 0.0);
	m->vertices[3] = dvec3(+w / 2, -h / 2, 0.0);

	return m;
}


Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) { 
	Mesh* m = generaRectangulo(w, h);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1, 0, 0, 0);
	m->colors[1] = dvec4(0, 1, 0, 0);
	m->colors[2] = dvec4(0, 0, 1, 0);
	m->colors[3] = dvec4(0, 0, 0, 1);

	return m;
}


//-------------------------------------------------------------------------

/*
	GENERA UNA ESTRELLA 3D
*/

Mesh*  Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h, GLdouble ri) {

	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_FAN;
	m->numVertices = 2 * np + 2;	

	m->vertices = new dvec3[m->numVertices];

	//Se supone que el centro está en (0.0,0.0,0.0).
	//AngIni es 90 y incrAng = 120.
	GLdouble angIni = 90;
	GLdouble incrAng = 360 / (np*2);


	m->vertices[0] = dvec3(0, 0, 0);
	m->vertices[1] = dvec3(re*cos(radians(angIni)), re*sin(radians(angIni)), h);

	for (unsigned i = 2; i <= m->numVertices - 2; i += 2) {
		angIni += incrAng;
		m->vertices[i] = dvec3(ri*cos(radians(angIni)), ri*sin(radians(angIni)), h);
		angIni += incrAng;
		m->vertices[i + 1] = dvec3(re*cos(radians(angIni)), re*sin(radians(angIni)), h);
	}

	return m;
}


//-------------------------------------------------------------------------


/*
	GENERA EL CUBO DESCRITO EN EL ENUNCIADO
*/
/*
Mesh*  Mesh::generaContCubo(GLdouble l) {

	Mesh* m = new Mesh();

	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 10; // 8 + 2 para cerrar el cubo.	

	m->vertices = new dvec3[m->numVertices];


	m->vertices[0] = dvec3(0,l,l);
	m->vertices[1] = dvec3(0, 0, l);
	m->vertices[2] = dvec3(l, l, l);
	m->vertices[3] = dvec3(l, 0, l);
	m->vertices[4] = dvec3(l, l, 0);
	m->vertices[5] = dvec3(l, 0, 0);
	m->vertices[6] = dvec3(0, l, 0);
	m->vertices[7] = dvec3(0, 0, 0);
	m->vertices[8] = dvec3(0, l, l);
	m->vertices[9] = dvec3(0, 0, l);
	
	return m;
}

Mesh* Mesh::generaSueloCubo(GLdouble l) {
	Mesh* m = new Mesh();

	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;
	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0, 0, l);
	m->vertices[1] = dvec3(0, 0, 0);
	m->vertices[2] = dvec3(l, 0, l);
	m->vertices[3] = dvec3(l, 0, 0);

	
	return m;
}
*/

//-------------------------------------------------------------------------


/*
	RECTANGULO TEX COR
*/

Mesh*  Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint	rw, GLuint rh) {

	Mesh* m = generaRectangulo(w, h);

	m->texCoords = new dvec2[m->numVertices];

	m->texCoords[0] = dvec2(0, rh);
	m->texCoords[1] = dvec2(rw, rh);
	m->texCoords[2] = dvec2(0, 0);
	m->texCoords[3] = dvec2(rw, 0);

	return m;
}


//-------------------------------------------------------------------------

/*
	ESTRELLA TEX COR
*/

Mesh*  Mesh::generaEstrellaTexCor(GLdouble r, GLdouble nL, GLdouble	h, GLdouble ri){

	Mesh* m = generaEstrella3D(r, nL, h,ri);

	m->texCoords = new dvec2[m->numVertices];

	GLdouble angIni = 90;
	GLdouble incrAng = 360 / (nL*2);

	//Utilizaremos R = 0.5
	ri = (0.5*ri) / r; //Calculamos el radio interior respecto al nuevo radio exterior.

	m->texCoords[0] = dvec2(0, 0);
	m->texCoords[1] = dvec3(0.5*cos(radians(angIni)), 0.5*sin(radians(angIni)), h);

	for (unsigned i = 2; i <= m->numVertices - 2; i += 2) {
		angIni += incrAng;
		m->texCoords[i] = dvec3(ri*cos(radians(angIni)), ri*sin(radians(angIni)), h);
		angIni += incrAng;
		m->texCoords[i + 1] = dvec3(0.5*cos(radians(angIni)), 0.5*sin(radians(angIni)), h);
	}
	return m;
}


//-------------------------------------------------------------------------

/*
	GENERA EL CUBO TEXCOR
*/

Mesh*  Mesh::generaCajaTexCor(GLdouble h, GLdouble w) {

	Mesh* m = generaCubo(h, w);
	m->texCoords = new dvec2[m->numVertices];
	
	m->texCoords[0] = dvec2(1,0);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(1, 1);
	m->texCoords[3] = dvec2(0, 1);
	m->texCoords[4] = dvec2(1, 2);
	m->texCoords[5] = dvec2(0, 2);
	m->texCoords[6] = dvec2(1, 3);
	m->texCoords[7] = dvec2(0, 3);
	m->texCoords[8] = dvec2(1, 4);
	m->texCoords[9] = dvec2(0, 4);

	return m;
}

Mesh* Mesh::generaSueloTexCor(GLdouble h, GLdouble w) {
	Mesh* m = generaSueloCubo(h, w);
	m->texCoords = new dvec2[m->numVertices];

	m->texCoords[0] = dvec2(1, 0);
	m->texCoords[1] = dvec2(1, 1);
	m->texCoords[2] = dvec2(0, 0);
	m->texCoords[3] = dvec2(0, 1);

	return m;
}



//-------------------------------------------------------------------------

/*
	FOTO TEX
*/

Mesh*  Mesh:: generaFotoTex(GLdouble w, GLdouble h) {
		Mesh* m = generaRectangulo(w, h);
		
		m->texCoords = new dvec2[m->numVertices];

		m->texCoords[0] = dvec2(0, 1);
		m->texCoords[1] = dvec2(1, 1);
		m->texCoords[2] = dvec2(0, 0);
		m->texCoords[3] = dvec2(1, 0);

		return m;
}


//-------------------------------------------------------------------------

	//PARTE 2 DE LA ASIGNATURA.

//-------------------------------------------------------------------------


/*
	GENERA EL CUBO CON UNA CIERTA PROFUNDIDAD Y ALTURA.
*/

Mesh*  Mesh::generaCubo(GLdouble h, GLdouble w) {

	Mesh* m = new Mesh();

	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 10; // 8 + 2 para cerrar el cubo.	

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0, h, w);
	m->vertices[1] = dvec3(0, 0, w);
	m->vertices[2] = dvec3(w, h, w);
	m->vertices[3] = dvec3(w, 0, w);
	m->vertices[4] = dvec3(w, h, 0);
	m->vertices[5] = dvec3(w, 0, 0);
	m->vertices[6] = dvec3(0, h, 0);
	m->vertices[7] = dvec3(0, 0, 0);
	m->vertices[8] = dvec3(0, h, w);
	m->vertices[9] = dvec3(0, 0, w);;


	return m;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaSueloCubo(GLdouble h, GLdouble w) {
	Mesh* m = new Mesh();

	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;
	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0, 0, w);
	m->vertices[1] = dvec3(0, 0, 0);
	m->vertices[2] = dvec3(w, 0, w);
	m->vertices[3] = dvec3(w, 0, 0);
	return m;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaTapaCubo(GLdouble h, GLdouble w) {
	Mesh* m = new Mesh();

	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;
	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0, h, w);
	m->vertices[1] = dvec3(w, h, w);
	m->vertices[2] = dvec3(0, h, 0);
	m->vertices[3] =  dvec3(w, h, 0);
	return m;
}


//-------------------------------------------------------------------------

MBR::MBR(GLint m, GLint n, dvec3 * per) {
	this->m = m;
	this->n = n;
	this->perfil = per;
	this->vertexBuilding();
	this->normalize();
}

MBR::~MBR() {
	Mesh::~Mesh();
	if (this->perfil != nullptr) {
		delete[] this->perfil;	this->perfil = nullptr;
	}
	if (this->normals != nullptr) {
		delete[] this->normals;	this->normals = nullptr;
	}
}

void MBR::vertexBuilding() {
	// Definir el array vertices de tamaño numVertices(=n*m) 
	this->numVertices = this->n * this->m;
	this->vertices = new dvec3[this->numVertices];

	for (int i=0; i<n; i++) { 
		// Cada vuelta genera la muestra i-ésima de vértices
		double theta = i*2* PI / n; 
		double c = cos(theta);
		double s = sin(theta);
		// R_y de más abajo es la matriz de rotación sobre el eje Y
		for (int  j=0; j<m; j++) {
			int indice=  i*m  +j ;
			// Aplicar la matriz al punto j-ésimo del perfil
			double x = c*perfil[j][0] + s*perfil[j][2];        
			double z = -s*perfil[j][0] + c*perfil[j][2];        
			dvec3 p = dvec3(x, perfil[j][1], z);
			vertices[indice] = p;
		} 
	}
}

void MBR::normalize() {
	// Definir el array normals de tamaño numVertices
	// e inicializar sus componentes al vector cero(=dvec3(0,0,0))
	this->normals = new dvec3[this->numVertices];

	for (size_t i = 0; i < this->numVertices; i++)
		this->normals[i] = dvec3(0);

	for(int i = 0; i < n; i++)
		for(int j = 0; j < m-1; j++) {
			// Recorrido de todos los vértices
			// Ojo, i<n (obliga a usar %(n*m)) 
			// y j<m-1 (para excluir los vértices del borde superior)
			int  indice= i*m + j;

			// Por cada cara en la que el vértice ocupa la esquina 
			// inferior izquierda, se determinan 3 índices i0, i1, i2 
			// de 3 vértices consecutivos de esa cara  
			int i1 = (indice + m) ; i1 = i1 % numVertices;
			dvec3 aux0 = vertices[indice]; //i0
			dvec3 aux1 = vertices[i1]; 
			dvec3 aux2 = vertices[indice+1]; //i2

			dvec3 norm =  glm::cross ( aux2 - aux1 , aux0 - aux1 ) ;
			normals[indice] += norm;
			normals[i1] += norm; 
			normals[indice + 1] += norm;
			//normals[...] += norm; 
		}  
	// Fin del for
	// Se normalizan todos los vectores normales... 
	
	for (size_t i = 0; i < this->numVertices; i++)
		this->normals[i] = glm::normalize( (vec3) normals[i]);
}

void MBR::render() {
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);
		// Activación de vertex arrays de colores y 
		// coordenadas de textura, si hace el caso.
		// No olvidar desactivarlos
		if (normals != nullptr) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, normals);
			primitive = GL_POLYGON; // o GL_LINE_LOOP
			// Se dan índices de vértices de caras cuadrangulares 
			for (int i = 0; i < n; i++)
				// Unir muestra i-ésima con (i+1)%n-ésima
				for (int j = 0; j < m - 1; j++) {
					// Empezar en esquina inferior izquierda de la cara     
					unsigned int indice = i * m + j;
					unsigned int index[] = {indice, 
											(int)(indice + m)     % (int)(n*m), 
											(int)(indice + m + 1) % (int)(n*m),
											indice + 1 };
					glDrawElements(primitive, 4, GL_UNSIGNED_INT, index);
					}
			//...
		}

		glDisableClientState(GL_VERTEX_ARRAY);
	}
}


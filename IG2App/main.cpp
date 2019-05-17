//#include <Windows.h>
//#include <gl/GL.h>    // OpenGL
//#include <gl/GLU.h>   // OpenGL Utility Library
#include <GL/glut.h>  // OpenGL Utility Toolkit

#include <GL/freeglut.h>  // Free OpenGL Utility Toolkit for creating windows, initializing OpenGL contexts, and handling input events
#include <glm.hpp>  // OpenGL Mathematics. A C++ mathematics library for graphics programming 

#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"

#include <iostream>

using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
Viewport viewPort(800, 600);   
Viewport viewPortAux(800, 600);

// Camera position, view volume and projection
Camera camera(&viewPort);    
Camera cameraAux(&viewPortAux);

// Graphics objects of the scene
Scene scene;
Scene sceneAux;

//Para capturar el último instante en que se realiza la actualización.
GLuint last_update_tick;

bool activated = true;

glm::dvec2 mCoord;
int mBot = 0;

bool baldosas = false;
double ratioWH = 800 / 600;
int gridRows = 2, gridCols = 2;

bool twoPorts = false;

const GLfloat ambGrey[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat ambBlack[] = { 0.0, 0.0, 0.0, 1.0 };


//----------- Callbacks ----------------------------------------------------

void display(void);
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);

//Añadido por nosotros.
void Update();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void mouseWheel(int n, int d, int x, int y);

void vistaSimple(void);
void embaldosar(int nCol);
void embaldosar(int nCol, int nRow);
void doubleScene(void);

//-------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	cout << "Starting console..." << '\n';

	// Initialization
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);   // GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); 

	glutInitWindowSize(800, 600);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer 

	int win = glutCreateWindow("IG2App");  // window's identifier

	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutSpecialFunc(specialKey);
	glutDisplayFunc(display);
	glutIdleFunc(Update);
	glutMouseWheelFunc(mouseWheel);

	//callbacks añadidos por nosotros
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';

	// after creating the context
	camera.set3D();
	cameraAux.set3D();

	// El profesor ha dicho que todo será en 3D este cuatri
	// scene.init2D();		//CAMBIADO POR NOSOTROS
	// scene.init3D();

	sceneAux.dronDrones();

	// apartado 18-19
	scene.esferaRev();
	// apartado 20
	//scene.esferaMateriales();
	// apartado 21
	//scene.esferaMinero();
	// apartado 22
	//scene.dronMinero();

	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambGrey);

	glutMainLoop(); 

	// cin.ignore(INT_MAX, '\n');  cin.get();  
	glutDestroyWindow(win);  // Destroy the context 

	return 0;
}

//-------------------------------------------------------------------------

//AÑADIDA POR NOSOTROS PARA EL UPDATE AUTOMÁTICO

void Update() {
	if (activated) {
		last_update_tick = glutGet(GLUT_ELAPSED_TIME);
		scene.update(last_update_tick);
		sceneAux.update(last_update_tick);
		glutPostRedisplay();
	}
}


//-------------------------------------------------------------------------


void display() {   // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
  
	//scene.render(camera.getViewMat());   
    
	if (twoPorts) {
		doubleScene();
	}
	else if (baldosas) {
		gridRows = gridCols = 2;
		//embaldosar(gridRows, gridCols);
		embaldosar(gridCols);
		scene.render(camera.getViewMat());
	}
	else {
		//embaldosar(1);
		vistaSimple();
		scene.render(camera.getViewMat());
	}

	glutSwapBuffers();  
	glutPostRedisplay();
}

//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight) {
	// Resize Viewport 
	/*
	if (twoPorts) {
		camera.getVP()->uploadSize(newWidth/2, newHeight);
		cameraAux.getVP()->uploadSize(newWidth / 2, newHeight);
	}
	else if (baldosas) {
		camera.getVP()->uploadSize(newWidth / gridCols, newHeight / gridRows);
	}
	else {
		camera.getVP()->uploadSize(newWidth, newHeight);
	}

	// Resize Scene Visible Area 
	camera.uploadSize(camera.getVP()->getW(), camera.getVP()->getH());    // scale unchanged
	scene.render(camera.getViewMat());
	cameraAux.uploadSize(cameraAux.getVP()->getW(), cameraAux.getVP()->getH());
	sceneAux.render(cameraAux.getViewMat());
	//*/

	if (twoPorts) {
		//cameraAux.getVP()->uploadSize(newWidth, newHeight);
		viewPortAux.uploadSize(newWidth, newHeight);
		viewPort.uploadSize(newWidth, newHeight);

		camera.uploadSize(viewPort.getW(), viewPort.getH());
		cameraAux.uploadSize(viewPortAux.getW(), viewPortAux.getH());
	}
	else {
		viewPort.uploadSize(newWidth, newHeight);
		camera.uploadSize(viewPort.getW(), viewPort.getH());
	}
}

//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y) {
	bool need_redisplay = true;


	/*
	Este switch determinará qué acción se asocia a cada botón presionado.
	*/
  
	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
		break;

	case '+': 
		camera.uploadScale(+0.01);   // zoom in  (increases the scale)
		cameraAux.uploadScale(+0.01);
		break;

	case '-':
		camera.uploadScale(-0.01);   // zoom out (decreases the scale)
		cameraAux.uploadScale(-0.01);
		break;

	case 'l':
		camera.set3D(); 
		cameraAux.set3D();
		break;

	case 'o':
		camera.set2D();
		cameraAux.set2D();
		break;

	case 'c':
		camera.setCenital();
		cameraAux.setCenital();
		break;

	case 'u':
		scene.update();
		sceneAux.update();
		break;

	case 'U':
		activated = !activated;
		break;

	case 'h':
		baldosas = !baldosas;
		break;

	case 'j':
		twoPorts = !twoPorts;
		break;
	
	case 'k':
		cameraAux.yaw(1);
		break;

	case 'p': 
		camera.changeProj();
		cameraAux.changeProj();
		break;

	case 'n':
		//glDisable(GL_LIGHTING);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambBlack);
		break;
	case 'm':
		//glEnable(GL_LIGHTING);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambGrey);
		break;

	/*case '2':
	// Para el intercambio entre escenas 2D y 3D.
	// Se deja aquí para hacer pruebas, pero en principio sobra
		scene.init2D();
		break;
	case '3':
		scene.init3D();
		break;
	*/

	case '0':
		scene.noria(12);
		break;
	case '1':
		scene.esferaRev();
		break;
	case '2':
		scene.init();
		break;
	case '3':
		scene.dronDrones();
		break;
	case '4':
		scene.esferaMateriales();
		break;
	case '5':
		scene.esferaMinero();
		break;
	case '6':
		scene.dronMinero();
		break;

	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay();
}

//-------------------------------------------------------------------------

void specialKey(int key, int x, int y) {
	bool need_redisplay = true;

	switch (key) {
	/*
	case GLUT_KEY_RIGHT:
		camera.pitch(1);   // rotate 1 on the X axis
		break;
	case GLUT_KEY_LEFT:
		camera.yaw(1);     // rotate 1 on the Y axis 
		break;
	case GLUT_KEY_UP:
		camera.roll(1);    // rotate 1 on the Z axis
		break;
	case GLUT_KEY_DOWN:
		camera.roll(-1);   // rotate -1 on the Z axis
		break;
	*/
	case GLUT_KEY_RIGHT:
	case GLUT_KEY_LEFT:
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:
		scene.move(key);
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay();
}

//-------------------------------------------------------------------------

void mouse(int button, int state, int x, int y) {
	mBot = button;
	mCoord = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
}

//-------------------------------------------------------------------------

void motion(int x, int y) {
	// Guardar los valores de mCoord cuando se pulsó el botón
	glm::dvec2 mp = mCoord;
	mCoord = glm::dvec2(x, y);
	// Calcular el desplazamiento habido
	mp = (mCoord - mp);
	if (mBot == GLUT_LEFT_BUTTON)
		// Recuerda que mp.x son radianes. Redúcelos a tu gusto
		if( twoPorts && x > glutGet(GLUT_WINDOW_WIDTH) / 2 )
			cameraAux.orbit(mp.x*0.05, mp.y);
		else
			camera.orbit(mp.x*0.05, mp.y);
	else if (mBot == GLUT_RIGHT_BUTTON) 
		if (twoPorts && x > glutGet(GLUT_WINDOW_WIDTH) / 2) {
			cameraAux.moveUD(mp.y);
			cameraAux.moveLR(-mp.x);
		}
		else {
			camera.moveUD(mp.y);
			camera.moveLR(-mp.x);
		}
	
	glutPostRedisplay();
}

//-------------------------------------------------------------------------

void mouseWheel(int n, int d, int x, int y) {
	// Se identifica cuántas teclas de las siguientes están pulsadas
	// GLUT_ACTIVE_CTRL/_ALT/_SHIFT
	int m = glutGetModifiers();
	if (m == 0) {
		// Es decir, si ninguna tecla está pulsada,
		// se desplaza la cámara en la dirección de vista
		// d=+1/-1, rueda hacia delante/hacia atrás
		if (d == 1) {
			if (twoPorts && x > glutGet(GLUT_WINDOW_WIDTH) / 2)
				cameraAux.moveFB(10);
			else
				camera.moveFB(10);
		}
		else {
			if (twoPorts && x > glutGet(GLUT_WINDOW_WIDTH) / 2)
				cameraAux.moveFB(-10);
			else
				camera.moveFB(-10);
		}
	}
	else if (m == GLUT_ACTIVE_CTRL) {
		if (d == 1) {
			if (twoPorts && x > glutGet(GLUT_WINDOW_WIDTH) / 2)
				cameraAux.uploadScale(0.02);
			else
				camera.uploadScale(0.02);
		}
		else {
			if (twoPorts && x > glutGet(GLUT_WINDOW_WIDTH) / 2)
				cameraAux.uploadScale(-0.02);
			else
				camera.uploadScale(-0.02);
		}
	}
	glutPostRedisplay();
}

//-------------------------------------------------------------------------

void vistaSimple(void) {
	Viewport* vp = new Viewport(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	vp->uploadPos(0, 0);
	vp->upload();
	camera.setVP(vp);
	camera.uploadPM();
	scene.render(camera.getViewMat());
}

//-------------------------------------------------------------------------

void embaldosar(int nCol) {
	GLdouble SVAratio = (camera.xRight - camera.xLeft) / (camera.yTop - camera.yBot);
	GLdouble w = (GLdouble)glutGet(GLUT_WINDOW_WIDTH) / (GLdouble)nCol;
	GLdouble h = w / SVAratio;
	for (GLint c = 0; c < nCol; c++) {
		GLdouble currentH = 0;
		while ((currentH + h) <= glutGet(GLUT_WINDOW_HEIGHT)) {
			Viewport* vp = new Viewport((GLint)w, (GLint)h);
			vp->uploadPos((GLint)(c * w), (GLint)currentH);
			vp->upload();
			camera.setVP(vp);
			camera.uploadPM();
			scene.render(camera.getViewMat());
			currentH += h;
		}
	}
}

//-------------------------------------------------------------------------

void embaldosar(int nRow, int nCol) {
	GLdouble h, w;
	/*
	GLdouble SVAratio = (camera.xRight - camera.xLeft) / (camera.yTop - camera.yBot);
	if ( SVAratio * glutGet(GLUT_WINDOW_HEIGHT) < glutGet(GLUT_WINDOW_WIDTH) ) {
		h = (GLdouble)glutGet(GLUT_WINDOW_HEIGHT) / (GLdouble)nRow;
		w = (GLdouble)glutGet(GLUT_WINDOW_HEIGHT) / (SVAratio*(GLdouble)nCol);
	}
	else {
		w = (GLdouble)glutGet(GLUT_WINDOW_WIDTH) / (GLdouble)nCol;
		h = (GLdouble)glutGet(GLUT_WINDOW_WIDTH) / (SVAratio*(GLdouble)nRow);
	}
	//*/

	//h = (GLdouble)glutGet(GLUT_WINDOW_HEIGHT) / (GLdouble)nRow;
	//w = (GLdouble)glutGet(GLUT_WINDOW_WIDTH) / (GLdouble)nCol;

	GLdouble SVAratio = (camera.xRight - camera.xLeft) / (camera.yTop - camera.yBot);
	w = (GLdouble)glutGet(GLUT_WINDOW_WIDTH) / (GLdouble)nCol;
	h = w / (SVAratio * (GLdouble)nRow);

	for (GLint c = 0; c < nCol; c++) {
		GLdouble currentH = 0;
		while ((currentH + h) <= glutGet(GLUT_WINDOW_HEIGHT)) {
			Viewport* vp = new Viewport((GLint)w, (GLint)h);
			vp->uploadPos((GLint)(c*w), (GLint)currentH);
			vp->upload();
			//camera.getVP()->~Viewport();
			camera.setVP(vp);
			camera.uploadPM();
			scene.render(camera.getViewMat());
			currentH += h;
		}
	}
}

//-------------------------------------------------------------------------

void doubleScene() {
	GLdouble SVAratio = (camera.xRight - camera.xLeft) / (camera.yTop - camera.yBot);
	GLdouble w = (GLdouble)glutGet(GLUT_WINDOW_WIDTH) / 2.0;
	GLdouble h = w / SVAratio;

	Viewport* vp = new Viewport((GLint) w, h);
	vp->uploadPos(0, ((GLdouble)glutGet(GLUT_WINDOW_HEIGHT) - h ) /2.0);
	vp->upload();
	//camera.getVP()->~Viewport();
	camera.setVP(vp);
	camera.uploadPM();
	scene.render(camera.getViewMat());

	vp = new Viewport((GLint)w, h);
	vp->uploadPos(w, ((GLdouble)glutGet(GLUT_WINDOW_HEIGHT) - h) / 2.0);
	vp->upload();
	//cameraAux.getVP()->~Viewport();
	cameraAux.setVP(vp);
	cameraAux.uploadPM();
	sceneAux.render(cameraAux.getViewMat());

}

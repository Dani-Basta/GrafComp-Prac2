//#include <Windows.h>
//#include <gl/GL.h>    // OpenGL
//#include <gl/GLU.h>   // OpenGL Utility Library
//#include <GL/glut.h>  // OpenGL Utility Toolkit

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

// Camera position, view volume and projection
Camera camera(&viewPort);    

// Graphics objects of the scene
Scene scene;   

//Para capturar el último instante en que se realiza la actualización.
GLuint last_update_tick;

bool activated = true;


//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);

//Añadido por nosotros.
void Update();

//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
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
  
  int win = glutCreateWindow("IG1App");  // window's identifier
  
  // Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutSpecialFunc(specialKey);
  glutDisplayFunc(display);
  glutIdleFunc(Update);
  cout << glGetString(GL_VERSION) << '\n';
  cout << glGetString(GL_VENDOR) << '\n';

  // after creating the context
  camera.set2D();
  
  // El profesor ha dicho que todo será en 3D este cuatri
  // scene.init2D();		//CAMBIADO POR NOSOTROS
  scene.init3D();
	
  glutMainLoop(); 
    
  //cin.ignore(INT_MAX, '\n');  cin.get();  
  glutDestroyWindow(win);  // Destroy the context 
 
  return 0;
}
//-------------------------------------------------------------------------

//AÑADIDA POR NOSOTROS PARA EL UPDATE AUTOMÁTICO

void Update() {
	if (activated) {
		last_update_tick = glutGet(GLUT_ELAPSED_TIME);
		scene.update(last_update_tick);
		glutPostRedisplay();
	}
}


//-------------------------------------------------------------------------


void display()   // double buffering
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
  
  scene.render(camera.getViewMat());   
    
  glutSwapBuffers();  

}
//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight)
{
  // Resize Viewport 
  viewPort.uploadSize(newWidth, newHeight);  
  
  // Resize Scene Visible Area 
  camera.uploadSize(viewPort.getW(), viewPort.getH());    // scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
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
    break;

  case '-':
    camera.uploadScale(-0.01);   // zoom out (decreases the scale)
    break;

  case 'l':
	  camera.set3D(); 
	  break;

  case 'o':
	  camera.set2D();
	  break;

  case 'u':
	  scene.update();
	  break;

  case 'U':
	  activated = !activated;
	  break;

  case '2':
    // Para el intercambio entre escenas 2D y 3D.
    // Se deja aquí para hacer pruebas, pero en principio sobra
	  scene.init2D();
	  break;

  case '3':
	  scene.init3D();
	  break;

  default:
	  need_redisplay = false;
    break;
  } //switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
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
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------


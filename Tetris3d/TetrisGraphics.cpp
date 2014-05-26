#include <GL/glut.h>
#include <iostream>
#include "TetrisEngine.h"
#include <stdio.h>

#define BRICK_ALPHA 0.5f

using namespace std;

TetrisEngine* tet;
int size_x,size_y,size_z;
float camera_x = 0; float camera_z = -10;

bool move_forward;
bool move_backward;
bool move_left;
bool move_right;


void draw_cube(int color){
  switch(color){
  case -1:
    break;
  case 0:
    glColor4f(1.0f, 0.0f, 0.0f, BRICK_ALPHA);
    glutSolidCube(1);
    break;
  case 1:
    glColor4f(0.0f, 1.0f, 0.0f, BRICK_ALPHA);
    glutSolidCube(1);
    break;
  case 2:
    glColor4f(1.0f, 1.0f, 0.0f, BRICK_ALPHA);
    glutSolidCube(1);
    break;
  case 3:
    glColor4f(1.0f, 0.0f, 1.0f, BRICK_ALPHA);
    glutSolidCube(1);
    break;
  case 4:
    glColor4f(1.0f, 1.0f, 0.0f, BRICK_ALPHA);
    glutSolidCube(1);
    break;
  default:
    break;
  }
  glColor3f(1.0f, 0.0f, 1.0f);
  glutWireCube(1);
}


void draw_frame(){
  int*** type = tet->get_type();
  bool*** empty = tet->get_empty();
  glTranslatef(0, size_z + 0.5, 0);
  for(int i = 0; i < size_z; i++){
    glTranslatef(0.0f, -1.0f, 0.0f);
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -size_y / 2.0f);
    for(int j = 0; j < size_y; j++){
      glTranslatef(0, 0, 1);
      glPushMatrix();
      glTranslatef(-size_x / 2, 0, 0);
      for(int k = 0; k < size_x; k++){
	draw_cube(type[i][j][k]);
	glTranslatef(1,0,0);
      }
      glPopMatrix();
    }
    glPopMatrix();
  }
}


void reshape(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void camera_Move(int key, int x, int y){
  switch(key){
  case GLUT_KEY_UP:
    move_forward = true;
    break;
  case GLUT_KEY_DOWN:
    move_backward = true;
    break;
  case GLUT_KEY_RIGHT:
    move_right = true;
    break;
  case GLUT_KEY_LEFT:
    move_left = true;
    break;
  default:
    break;
  }
}
void camera_Move_release(int key, int x, int y){
  switch(key){
  case GLUT_KEY_UP:
    move_forward = false;
    break;
  case GLUT_KEY_DOWN:
    move_backward = false;
    break;
  case GLUT_KEY_RIGHT:
    move_right = false;
    break;
  case GLUT_KEY_LEFT:
    move_left = false;
    break;
  default:
    break;
  }
}



void render(void) {
    static int time = glutGet(GLUT_ELAPSED_TIME);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(	camera_x, size_z * 1.0f, camera_z,
		0.0f, 1.0f,  0.0f,
		0.0f, 1.0f,  0.0f);
    
    glColor3f(0.9f, 0.9f, 0.9f);
    
    glBegin(GL_QUADS); //this is the ground
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f); 
    glVertex3f( 100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

    draw_frame();
    if(move_forward || move_backward){
      camera_x += camera_x * 0.1 * ((move_forward)? -1.0: 1.0);
      camera_z += camera_z * 0.1 * ((move_forward)? -1.0: 1.0);
    }
    if(move_left || move_right){
      camera_z += camera_x * 0.1 * ((move_left)? 1.0: -1.0);
      camera_x += camera_z * 0.1 * ((move_left)? -1.0: 1.0);
    }
    printf("X: %.2f , Z: %.2f \n", camera_x, camera_z);
    glutSwapBuffers();
    if(glutGet(GLUT_ELAPSED_TIME) - time > 1000){
      //cout << "TIME: " << time(0) << endl;
      //cout << time(0) - sysTime << endl;
      tet->RandomizeMats();
      //tet->randomize_type();
      time = glutGet(GLUT_ELAPSED_TIME);
    }
}


void initGraphics(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("3D Tetris");

	// register callbacks
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
      	glutIdleFunc(render);

	glutIgnoreKeyRepeat(10);
	//glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(camera_Move);
	glutSpecialUpFunc(camera_Move_release);
	/*
	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);*/

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
	// enter GLUT event processing cycle
	glutMainLoop();
}



int main(int argc, char** argv){
  size_x = 5;
  size_y = 5; 
  size_z = 9;
  tet = new TetrisEngine(size_x, size_y, size_z);
  tet->RandomizeMats();
  initGraphics(argc, argv);

  delete tet;
  return 0;
}

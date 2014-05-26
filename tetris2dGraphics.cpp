#include <iostream>
#include <GL/glut.h>
//#include "tetris2dGraphics.h"
#include "tetris2dEngine.h"
#include "shape.h"
#include <ctime>

using std::cout;
using std::endl;



TetrisEngine* tet;


#define EDGE_SIZE 50


void draw_grid(){
  glColor3f(1.0f,1.0f,1.0f);
  for(int i = 0; i < tet->get_height(); i++){
    glBegin(GL_LINES);
    glVertex2d(-1, -1 + i * 2.0 / tet->get_height());
    glVertex2d(1, -1 + i * 2.0 / tet->get_height());
    glEnd();
  }
  for(int i = 0; i < tet->get_width(); i++){
    glBegin(GL_LINES);
    glVertex2d(-1 + i * 2.0 /tet->get_width(), -1); 
    glVertex2d(-1 + i * 2.0 /tet->get_width(), 1); 
    glEnd();
  }
}


void draw_square(int color, float x, float y){
  float f_color[3] = {0, 1, 1};
  //cout << "COLOR: " << color << "  ";
  switch(color){
  case 1:
    f_color[0] = 1; f_color[1] = 0; f_color[2] = 0;
    break;
  case 2:
    f_color[0] = 0; f_color[1] = 1; f_color[2] = 0;
    break;
  case 3:
    f_color[0] = 1; f_color[1] = 1; f_color[2] = 0;
    break;
  case 4:
    f_color[0] = 0; f_color[1] = 0; f_color[2] = 1;
    break;
  case -1:
    f_color[0] = 0; f_color[1] = 0; f_color[2] = 0;
    break;
  default:
    f_color[0] = 1; f_color[1] = 0; f_color[2] = 1;
    break;
  }
  //cout << f_color[0] << f_color[1] << f_color[2] << endl;
  glBegin(GL_QUADS);
  glColor3f(f_color[0], f_color[1], f_color[2]);
  glVertex2f(x, y);
  glVertex2f(x, y - 2.0 / tet->get_height());
  glVertex2f(x + 2.0 / tet->get_width(), y - 2.0 / tet->get_height());
  glVertex2f(x + 2.0 / tet->get_width(), y);
  glEnd();
}

void KeyInput(unsigned char key, int x, int y){
    switch(key){
    case 'w':
      tet->Rotate_part();
      break;
    case 's':
      tet->Move_part_restricted(DOWN);
      break;
    case 'd':
      tet->Move_part_restricted(RIGHT);
      break;
    case 'a':
      tet->Move_part_restricted(LEFT);
      break;
    case 'r':
      tet->Rotate_part();
    default:
      break;
    }
    tet->PrintEmpty();
}


void render(){
  static int time = glutGet(GLUT_ELAPSED_TIME);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  int** type = tet->get_type();
  draw_square(type[0][0], -1, 1);
  //Draw All Squares
  for(int i = 0; i < tet->get_height(); i++){
    for(int j = 0; j < tet->get_width(); j++){
      draw_square(type[i][j], -1 + j * 2.0 / tet->get_width(), 1 -  i * 2.0 / tet->get_height());
    }
  }
  draw_grid();
  

  glutSwapBuffers();
  if(glutGet(GLUT_ELAPSED_TIME) - time > 1000){
    //cout << "TIME: " << time(0) << endl;
    //cout << time(0) - sysTime << endl;
    tet->Gravity();
    //tet->randomize_type();
    time = glutGet(GLUT_ELAPSED_TIME);
  }
}

void reshape(int w, int h){
  
}

void start_graphics(int argc, char** argv){
  //Initialize GL
  glutInit(&argc, argv);
  glutInitWindowSize( EDGE_SIZE * tet->get_width(), EDGE_SIZE * tet->get_height());
  glutInitWindowPosition(100,100);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("sdfadfs");

  //register callbacks 
  glutDisplayFunc(render);
  //glutReshapeFunc(reshape);
  glutIdleFunc(render);
  glutKeyboardFunc(KeyInput);
  //start event loop
  glutMainLoop();
}


int main(int argc, char** argv){
  /*std::cout << "Hello" << std::endl;
    Tetris2DGraphics z(10, 10);*/
  int size_w = 10; int size_h = 20;
  tet = new TetrisEngine(size_w, size_h);
  tet->ShapeSpawn();
  start_graphics(argc, argv);
  delete tet;
  return 0;
}

#include "tetris2dEngine.h"


#ifndef H_2D_GRAPHICS
#define H_2D_GRAPHICS

class Tetris2DGraphics{
 private:
  int w_b, h_b;
  static int** plot_mat;
  TetrisEngine* tet;
  //static float c_r;
  static void render();
  static void reshape(int w, int h);
 
 public:
  Tetris2DGraphics(int width, int height){
    tet = new TetrisEngine(width, height);
    w_b = width;
    h_b = height;
    plot_mat = tet.get_type();
    //c_r = 0.3;
  }
  ~Tetris2DGraphics(){
    delete tet;
  }
  //for testing
  static void update_mat(){
    randomize_empty();
  }
  void start_graphics(int argc, char** argv);
};

//float Tetris2DGraphics::c_r = 1;
int** Tetris2DGraphics::plot_mat = NULL;

#endif

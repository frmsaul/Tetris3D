#ifndef TETRIS_H
#define TETRIS_H

#include <stdlib.h>
#include <iostream>
#include "shape.h"
using namespace std;

enum Dir{UP, DOWN, LEFT, RIGHT};

class TetrisEngine{
 private:
  int width_blocks;
  int height_blocks;
  bool** empty;
  int** type;
  int rand_counter;
  Shape part;
  bool shape_fits(int x, int y, Shape p);
  bool is_in_bounds(int x, int y);
  int shape_x_pos, shape_y_pos;
  void update_board();
  bool Move_part(Dir d);
 public:
  bool Move_part_restricted(Dir d);
  void Gravity();
  bool Rotate_part();
  bool ShapeSpawn();
  TetrisEngine(int w_b, int h_b);
  ~TetrisEngine();
  int get_width(){ return width_blocks;}
  int get_height(){return height_blocks;}
  int** get_type(){return type;}
  bool** get_empty(){return empty;}
  void PrintType();
  void PrintEmpty();
};








#endif

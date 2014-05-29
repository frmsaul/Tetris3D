#include <iostream>
#include "shape.h"

#ifndef TETRIS_ENGINE_H
#define TETRIS_ENGINE_H

enum Dir {UPX, UPY, UPZ, DOWNX, DOWNY, DOWNZ};

class TetrisEngine{
 private:
  bool*** empty;
  int*** type;
  int sizeX, sizeY, sizeZ;
  int pos_x, pos_y, pos_z;

  Shape shape_block;
  bool in_bounds(int x, int y, int z);
  bool shape_fits(int x, int y, int z, Shape s);
  bool is_empty(int x, int y, int z);
  void update_board();
  void RemovePlaneCheck();
  void RemovePlane(int z);
 public:
  TetrisEngine(int x, int y, int z);
  ~TetrisEngine();
  bool MoveShape(Dir d);
  bool restricted_move(char c);
  void Gravity();
  bool Rotate_x();
  bool Rotate_y();
  bool Rotate_z();


  bool SpawnShape(Shape s);
  void PrintTypeMat();
  void PrintEmptyMat();

  void RandomizeMats(); //Testing Graphics Purposes

  int get_size_X(){ return sizeX;}
  int get_size_Y(){ return sizeY;}
  int get_size_Z(){ return sizeZ;}
  int*** get_type(){ return type;}
  bool*** get_empty(){ return empty;}
};

#endif

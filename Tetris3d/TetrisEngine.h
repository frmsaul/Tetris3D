#include <iostream>


class TetrisEngine{
 private:
  bool*** empty;
  int*** type;
  int sizeX, sizeY, sizeZ; 
 public:
  TetrisEngine(int x, int y, int z);
  ~TetrisEngine();

  void PrintTypeMat();
  void PrintEmptyMat();

  void RandomizeMats(); //Testing Graphics Purposes

  int get_size_X(){ return sizeX;}
  int get_size_Y(){ return sizeY;}
  int get_size_Z(){ return sizeZ;}
  int*** get_type(){ return type;}
  bool*** get_empty(){ return empty;}
};



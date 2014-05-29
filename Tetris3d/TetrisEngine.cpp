#include <iostream>
#include "TetrisEngine.h"
#include <stdio.h>
#include <ctime>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::cin;

bool TetrisEngine::in_bounds(int x, int y, int z){
  if(x < 0 || x >= sizeX)
    return false;
  if(y < 0 || y >= sizeY)
    return false;
  if(z < 0 || z >= sizeZ)
    return false;
  return true;
}

bool TetrisEngine::is_empty(int x, int y, int z){
  for(int i = 0; i < shape_block.points.size(); i++){
    if(x == (shape_block.points[i].X + pos_x) && y == (shape_block.points[i].Y + pos_y) && z == (shape_block.points[i].Z + pos_z)){
      return true;
    }
  }
  return empty[z][y][x];
}

bool TetrisEngine::Rotate_x(){
  Shape copy_s = shape_block;
  copy_s.Rotate_x();
  if(shape_fits(pos_x, pos_y, pos_z, copy_s)){
    for(int i = 0; i < shape_block.points.size(); i++){
      empty[pos_z + shape_block.points[i].Z][pos_y + shape_block.points[i].Y][pos_x + shape_block.points[i].X] = true;
      type[pos_z + shape_block.points[i].Z][pos_y + shape_block.points[i].Y][pos_x + shape_block.points[i].X] = -1;
    }
    shape_block = copy_s;
    update_board();
    return true;
  }
  cout << "SHE CRIDED" << endl;
  return false;
}
bool TetrisEngine::Rotate_y(){
  Shape copy_s = shape_block;
  copy_s.Rotate_y();
  if(shape_fits(pos_x, pos_y, pos_z, copy_s)){
    for(int i = 0; i < shape_block.points.size(); i++){
      empty[pos_z + shape_block.points[i].Z][pos_y + shape_block.points[i].Y][pos_x + shape_block.points[i].X] = true;
      type[pos_z + shape_block.points[i].Z][pos_y + shape_block.points[i].Y][pos_x + shape_block.points[i].X] = -1;
    }
    shape_block = copy_s;
    update_board();
    return true;
  }
  cout << "SHE CRIDED" << endl;
  return false;
}
bool TetrisEngine::Rotate_z(){
  Shape copy_s = shape_block;
  copy_s.Rotate_z();
  if(shape_fits(pos_x, pos_y, pos_z, copy_s)){
    for(int i = 0; i < shape_block.points.size(); i++){
      empty[pos_z + shape_block.points[i].Z][pos_y + shape_block.points[i].Y][pos_x + shape_block.points[i].X] = true;
      type[pos_z + shape_block.points[i].Z][pos_y + shape_block.points[i].Y][pos_x + shape_block.points[i].X] = -1;
    }
    shape_block = copy_s;
    update_board();
    return true;
  }
  cout << "SHE CRIDED" << endl;
  return false;
}

bool TetrisEngine::shape_fits(int x, int y, int z, Shape s){
  for(int i = 0; i < s.points.size(); i++){
    if(!in_bounds(x + s.points[i].X, y + s.points[i].Y, z + s.points[i].Z)){
      cout << "OUT OF BOUNDS" << endl;
      return false;
    }
    if(!is_empty(x + s.points[i].X, y + s.points[i].Y, z + s.points[i].Z)){
      cout << "SOMETHING NOT EMPTY" << endl;
      return false;
    }
  }
  return true;
}

bool TetrisEngine::MoveShape(Dir d){
  block new_position;
  switch(d){
  case UPX:
    new_position = block(pos_x + 1, pos_y, pos_z);
    break;
  case UPY:
    new_position = block(pos_x, pos_y + 1, pos_z);
    break;
  case UPZ:
    new_position = block(pos_x, pos_y, pos_z + 1);
    break;
  case DOWNX:
    new_position = block(pos_x - 1, pos_y, pos_z);
    break;
  case DOWNY:
    new_position = block(pos_x, pos_y - 1, pos_z);
    break;
  case DOWNZ:
    new_position = block(pos_x, pos_y, pos_z - 1);
    break;
  }
  if(!shape_fits(new_position.X, new_position.Y, new_position.Z, shape_block)){
    cout << "SHE CRIED" <<endl;
    return false;
  } else {
    for(int i = 0; i < shape_block.points.size(); i++){
      empty[pos_z + shape_block.points[i].Z][pos_y + shape_block.points[i].Y][pos_x + shape_block.points[i].X] = true;
      type[pos_z + shape_block.points[i].Z][pos_y + shape_block.points[i].Y][pos_x + shape_block.points[i].X] = -1;
    }

    pos_y = new_position.Y;
    pos_z = new_position.Z;
    pos_x =new_position.X;

    update_board();
    return true;
  }
}

void TetrisEngine::update_board(){
    for(int i = 0; i < shape_block.points.size(); i++){
      empty[pos_z + shape_block.points[i].Z][pos_y + shape_block.points[i].Y][pos_x + shape_block.points[i].X] = false;
      type[pos_z + shape_block.points[i].Z][pos_y + shape_block.points[i].Y][pos_x + shape_block.points[i].X] = shape_block.get_type();
    } 
}

bool TetrisEngine::SpawnShape(Shape s){
  shape_block = s;
  pos_x = 0;
  pos_y = 0;
  pos_z = 0;
  if(!shape_fits(pos_x, pos_y, pos_z, s)){
    cout << "YOU LOST TETRIS" << endl;
    return false;
  }
  update_board();
  return true;
}



TetrisEngine::TetrisEngine(int x, int y, int z){
  sizeX = x; 
  sizeY = y;
  sizeZ = z;
  pos_x = -1; pos_y = -1; pos_z = -1;
  
  type = new int**[sizeZ];
  empty = new bool**[sizeZ];

  for(int i = 0; i < sizeZ; i++){
    type[i] = new int*[sizeY];
    empty[i] = new bool*[sizeY];

    for(int j = 0; j < sizeY; j++){
      type[i][j] = new int[sizeX];
      empty[i][j] = new bool[sizeX];

      for(int k = 0; k < sizeX; k++){
	type[i][j][k] = -1;
	empty[i][j][k] = true;
      }
    }
  }
}

TetrisEngine::~TetrisEngine(){
  for(int i = 0; i < sizeZ; i++){
    for(int j = 0; j < sizeY; j++){
      delete [] type[i][j];
      delete [] empty[i][j];
    }
    delete [] type[i];
    delete [] empty[i];
  }
  delete [] type;
  delete [] empty;
}

void TetrisEngine::PrintTypeMat(){
  for(int i = 0; i < sizeZ; i++){
    cout << "LEVEL: " << i << endl;
    for(int j = 0; j < sizeY; j++){
      for(int k = 0; k < sizeX; k++){
	printf("%2i", type[i][j][k]);
      }
      printf("\n");
    }
    for(int k = 0; k < sizeX; k++) printf("__");
    printf("\n");
  }
}
void TetrisEngine::PrintEmptyMat(){
  for(int i = 0; i < sizeZ; i++){
    cout << "LEVEL: " << i << endl;
    for(int j = 0; j < sizeY; j++){
      for(int k = 0; k < sizeX; k++){
	printf("%2i", empty[i][j][k]);
      }
      printf("\n");
    }
    for(int k = 0; k < sizeX; k++) printf("__");
    printf("\n");
  }
}

void TetrisEngine::RandomizeMats(){
  srand(time(0));
  for(int i = 0; i < 20; i++){
    type[rand() % sizeZ][rand() % sizeY][rand() % sizeX] = rand() % 5;
    empty[rand() % sizeZ][rand() % sizeY][rand() % sizeX] = rand() % 2;
  }
  for(int i = 0; i < 20; i++){
    type[rand() % sizeZ][rand() % sizeY][rand() % sizeX] = -1;
  }
}
void TetrisEngine::RemovePlane(int z){
  //Shif All planes downwards
  for(int i = z - 1; z > 0; z--){
    for(int j = 0; j < sizeY; j++){
      for(int k = 0; k < sizeX; k++){
	empty[i][j][k] = empty[i - 1][j][k];
	type[i][j][k] = type[i - 1][j][k];
      }
    }
  }
  //Erases the highest plane 
  for(int j = 0; j < sizeY; j++){
    for(int k = 0; k < sizeX; k++){
      empty[0][j][k] = true;
      type[0][j][k] = -1;
    }
  }
}

bool TetrisEngine::restricted_move(char move){
  switch(move){
  case 'a':
    return MoveShape(DOWNX);
    break;
  case 'd':
    return MoveShape(UPX);
    break;
  case 'w':
    return MoveShape(DOWNY);
    break;
  case 's':
    return MoveShape(UPY);
    break;
  case 'q':
    return MoveShape(UPZ);
    break;
  case 'e':
    return MoveShape(DOWNZ);
    break;
  case 'x':
    return Rotate_x();
    break;
  case 'y':
    return Rotate_y();
    break;
  case 'z':
    return Rotate_z();
    break;
  default:
    return true;
    break;
  }
}

void TetrisEngine::RemovePlaneCheck(){
  for(int i = 0; i < sizeZ; i++){
    for(int j = 0; j < sizeY; j++){
      for(int k = 0; k < sizeX; k++){
	if(empty[i][j][k])
	  goto PlaneIsNotFull;
      }
    }
    RemovePlane(i);
    --i;
  PlaneIsNotFull:
    i = i;
  }
}

void TetrisEngine::Gravity(){
  if(!MoveShape(UPZ)){
    RemovePlaneCheck();
    if(!SpawnShape(Shape()))
      cout << "YOU LOST TETRIS" << endl;
  }
}


/*
int main(){
  /* TetrisEngine tet(3,3,5);
  Shape s; s.Rotate_z();
  tet.SpawnShape(s);
  char input;
  int counter = 1;
  while(true){
    cin >> input;
    tet.restricted_move(input);
    tet.PrintEmptyMat();
    if(counter++ % 5 == 0)
      tet.Gravity();
      }
  return 0;
}
*/

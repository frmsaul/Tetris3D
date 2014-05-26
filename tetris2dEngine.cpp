#include "tetris2dEngine.h"
#include <iostream>
#include "shape.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void TetrisEngine::PrintType(){
  for(int i = 0; i < height_blocks; i++){
    for(int j = 0; j < width_blocks; j++){
      printf("%2i", type[i][j]);
    }
    cout << endl;
  }
}

void TetrisEngine::PrintEmpty(){
  for(int i = 0; i < height_blocks; i++){
    for(int j = 0; j < width_blocks; j++){
      cout << empty[i][j] << ", ";
    }
    cout << endl;
  }
}
bool TetrisEngine::Move_part_restricted(Dir d){
  if(d != UP){
    if(!Move_part(d)){
      cout << "CANT MOVE THIS WAY" << endl;
      return false;
    }
    return true;
  }
  return false;
}


bool TetrisEngine::Move_part(Dir d){
  int new_x; int new_y;
  switch(d){
  case UP:
    new_x = shape_x_pos;
    new_y = shape_y_pos - 1;
    break;
  case DOWN:
    new_x = shape_x_pos;
    new_y = shape_y_pos + 1;
    break;
  case LEFT:
    new_x = shape_x_pos - 1;
    new_y = shape_y_pos;
    break;
  case RIGHT:
    new_x = shape_x_pos + 1;
    new_y = shape_y_pos;
    break;
  }
  if(!shape_fits(new_x, new_y, part)){
    //cout << "CANT MAKE MOVE" << endl;
    return false;
  }

  vector< pair<int, int> > points = part.get_points();
  int x, y;
  for(int i = 0; i < points.size(); i++){
    x = shape_x_pos + get<0>(points[i]);
    y = shape_y_pos + get<1>(points[i]);
    empty[y][x] = true;
    type[y][x] = -1;
  }
  shape_x_pos = new_x;
  shape_y_pos = new_y;
  
  update_board();
  return true;
}

bool TetrisEngine::Rotate_part(){
  Shape part_copy = part; // need to over write this part?
  part_copy.Rotate();
  if(!shape_fits(shape_x_pos , shape_y_pos, part_copy ))
    return false;

  vector< pair<int, int> > points = part.get_points();
  int x, y;
  for(int i = 0; i < points.size(); i++){
    x = shape_x_pos + get<0>(points[i]);
    y = shape_y_pos + get<1>(points[i]);
    empty[y][x] = true;
    type[y][x] = -1;
  }

  part.Rotate();  
  update_board();
}

TetrisEngine::TetrisEngine(int w_b, int h_b){
    width_blocks = w_b;
    height_blocks = h_b;
    
    empty = new bool*[h_b];
    type = new int*[h_b];
   
    for(int i = 0; i < h_b;i++){
      empty[i] = new bool[w_b];
      type[i] = new int[w_b];
      
      for(int j = 0; j < w_b; j++){
	type[i][j] = -1;
	empty[i][j] = true;
      }
    }
    shape_x_pos = -1;
    shape_y_pos = -1;
}

TetrisEngine::~TetrisEngine(){
    for(int i = 0; i < height_blocks; i++){
      delete [] empty[i];
      delete [] type[i];
    }
    delete[] empty;
    delete[] type;
}

bool TetrisEngine::is_in_bounds(int x, int y){
  if(x < 0 || y < 0) return false;
  if(x >= width_blocks|| y >= height_blocks ) return false;
  return true;
}
void TetrisEngine::Gravity(){
  if(!Move_part(DOWN)){
    //This part removes full rows
    for(int i = 0; i < height_blocks; i++){
      for(int j = 0; j < width_blocks; j++){
	if(empty[i][j]){ // row isn't full
	  goto row_not_full;
	}
      }
      //row i is full
      for(int k = i; k > 0; k--){
	for(int j = 0; j < width_blocks; j++){
	  empty[k][j] = empty[k - 1][j];
	  type[k][j] = type[k - 1][j];
	}
      }
      for(int j = 0; j < width_blocks; j++){
	empty[0][j] = true;
	type[0][j] = -1;
      }
    row_not_full:
      i = i;
    }
    shape_x_pos = -1; shape_y_pos = -1;
    ShapeSpawn();
  }
}


bool TetrisEngine::shape_fits(int x, int y, Shape p){
  vector< pair<int, int> > points = p.get_points();
  vector< pair<int, int> > points2 = part.get_points();
  int X, Y;
  for(int i = 0; i < points.size(); i++){
    X = x + get<0>(points[i]);
    Y = y + get<1>(points[i]);
    
    if(!is_in_bounds(X,Y))
      return false;
    
    if(!empty[Y][X]){
      if(shape_x_pos != -1 && shape_y_pos != -1){ //this whole part checks for overlaps
	for(int j = 0; j < points2.size(); j++){
	  if(X == shape_x_pos + get<0>(points2[j]) && Y == shape_y_pos + get<1>(points2[j]))
	    goto here;
	}
      }
      return false;
    here:
      i = i; //menaingless statement
    }
  }
  return true;
}

bool TetrisEngine::ShapeSpawn(){
  part = Shape(random() % 5 + 1); //initialize
  //part.PrintShape();
  if(!shape_fits(0, 0, part)){
    cout << "YOU LOST TETRIS" << endl;
    return false;
  }
  shape_x_pos = 0;
  shape_y_pos = 0;
  update_board();
}

void TetrisEngine::update_board(){
  vector< pair<int, int> > points = part.get_points();
  int x, y;
  for(int i = 0; i < points.size(); i++){
    x = shape_x_pos + get<0>(points[i]);
    y = shape_y_pos + get<1>(points[i]);
    empty[y][x] = false;
    type[y][x] = part.type;
  }
}

/*
int main(){
  /*
  Shape T;
  T.PrintShape();
  for(int i = 0; i < 5;i++){
    cout << "___________" << endl;
    T.Rotate();
    T.PrintShape();
    }.
  
  int w = 10; int h = 10;
  TetrisEngine tet(w,h);
  //int** type_test = tet.get_type();
  //bool** empty_test = tet.get_empty();
  tet.ShapeSpawn();
  char input; int counter = 0;
  while(true){
    cin >> input;
     //tet.PrintType();
    if(counter++ % 2 == 0)
      tet.Gravity();
  }
  return 0;
}
*/







#include "shape.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>


using namespace std; 


bool myFind(vector<block> S_vec, block S){
  for(int i = 0; i < S_vec.size(); i++){
    if(S_vec[i] == S)
      return true;
  }
  return false;
}
void myErase(vector<block>* S_vec, block S){
  for(int i = 0; i < S_vec->size(); i++){
    if(S_vec->at(i) == S){
      S_vec->erase(S_vec->begin() + i);
      i--;
    }
  }
}




void Shape::set_bounding_box(){
  int min_x = 1000; int min_y = 1000; int min_z = 1000;
  int max_x = -1000;int max_y = -1000; int max_z = -1000;
  for(int i = 0; i < points.size(); i++){
    if(points[i].X > max_x)
      max_x = points[i].X;
    if(points[i].Y > max_y)
      max_y = points[i].Y;
    if(points[i].Z > max_z)
      max_z = points[i].Z;
   
    if(points[i].X < min_x)
      min_x = points[i].X;
    if(points[i].Y < min_y)
      min_y = points[i].Y;
    if(points[i].Z < min_z)
      min_z = points[i].Z;
  }
  for(int i = 0; i < points.size(); i++){
    points[i] = block(points[i].X -  min_x, points[i].Y - min_y, points[i].Z - min_z);
  }
  bounding_box = block(max_x - min_x, max_y - min_y, max_z - min_z);
}
void Shape::Rotate_x(){
  for(int i = 0; i < points.size(); i++)
    points[i] = block(-points[i].Y, points[i].Z, points[i].X);
  set_bounding_box();
}
void Shape::Rotate_y(){
  for(int i = 0; i < points.size(); i++)
    points[i] = block(-points[i].X, points[i].Y, points[i].Z);
  set_bounding_box();
}
void Shape::Rotate_z(){
  for(int i = 0; i < points.size(); i++)
    points[i] = block(points[i].Z, -points[i].X, points[i].Y);
  set_bounding_box();
}

void Shape::init(int n){
  srand(time(0));
  
  vector<block> possible_points;
  vector<block> points_in_shape;
 
  possible_points.push_back(block());
  //cout << "SIZE OF POINTS: " << possible_points.size() << endl;
  block random_block;

  for(int i = 0; i < n; i++){
    random_block = possible_points[random() % possible_points.size()];
    
    points_in_shape.push_back(random_block);
    
    points.push_back(random_block);
    myErase(&possible_points ,random_block);
    for(int k1 = -1; k1 <= 1; k1++){
      for(int k2 = -1; k2 <= 1; k2++ ){
	for(int k3 = -1; k3 <=1; k3++){
	  if(abs(k1) + abs(k2) + abs(k3) == 1){ //no diagnols
	    //cout << "ALRIGHT: " << possible_points.size()<< endl;
	    if(!myFind(points_in_shape, block(random_block.X + k1, random_block.Y + k2, random_block.Z + k3))){
	      //cout << "HERE" << endl;
	      possible_points.push_back(block(random_block.X + k1, random_block.Y + k2, random_block.Z + k3)); 
	    }
	  }
	}
      }
    }
  }
  set_bounding_box();
  type = rand() % 5; 
}


Shape::Shape(){
  /*points.push_back(block(0, 0, 0));
  points.push_back(block(1, 0, 0));
  points.push_back(block(0,0,1));
  points.push_back(block(0,1,0));
  set_bounding_box();
  type = 1;*/
  srand(time(0));
  init((rand() % 4) + 1);
}


Shape::Shape(int n){
  srand(0);
  init(n);
}






void Shape::Print(){
  bool print[bounding_box.Z + 1][bounding_box.Y + 1][bounding_box.X + 1];

  for(int i = 0; i < bounding_box.Z + 1; i++) //Initialize array
      for(int j = 0; j < bounding_box.Y + 1; j++)
	  for(int k = 0; k < bounding_box.X + 1; k++)
	    print[i][j][k] = false;
  for(int i = 0; i < points.size(); i++){
    print[points[i].Z][points[i].Y][points[i].X] = true;
  }

  for(int i = 0; i < bounding_box.Z + 1; i++){
    for(int j = 0; j < bounding_box.Y + 1; j++){
      for(int k = 0; k < bounding_box.X + 1; k++){
	cout << ((print[i][j][k])? 'X' :'0');
      }
      cout << endl;
    }
    for(int k = 0; k < bounding_box.X + 1; k++)
      cout << "_";
    cout << endl;
  }
}


/*
int main(){
  Shape S;
  S.Print();
  cout << "Rotation #1" << endl;
  S.Rotate_z();
  S.Print();
  return 0;
}
*/

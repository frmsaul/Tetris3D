#include "shape.h"
#include <vector>
#include <utility>
#include <unordered_set>
#include <stdlib.h>
#include <ctime>

using namespace std;

namespace std {
template <>
    class hash < std::pair< int,int> >{
    public :
        size_t operator()(const pair< int, int> &x ) const
        {
            size_t h =   std::hash<int>()(x.first) ^ std::hash<int>()(x.second);
            return  h ;
        }
    };
}


Shape::Shape(){
  points.push_back(pair<int, int>(0, 0));
  points.push_back(pair<int, int>(-1, 0));
  points.push_back(pair<int, int>(1, 0));
  points.push_back(pair<int, int>(0,1)); 
  set_bounding_box();
  type = 2;
}

pair<int, int> random_point(unordered_set<pair<int, int> > S){
}



Shape::Shape(int n){
  srand(time(0));
  unordered_set<pair<int, int> > possible_points;
  unordered_set<pair<int, int> > points_in_shape;
  possible_points.insert(pair<int,int>(0,0));
  pair<int, int> random_point;
  int random_element, random_counter;

  for(int i = 0; i < n; i++){
    random_element = random() % possible_points.size(); //The inner loop chooses a random element from the set
    random_counter = 0;
    for(auto it = possible_points.begin(); it != possible_points.end(); it++, random_counter++){
      if(random_counter == random_element){
	random_point = *it;
      }
    }

    points_in_shape.insert(random_point);
    
    points.push_back(random_point);
    possible_points.erase(random_point);
    for(int k1 = -1; k1 <= 1; k1++){
      for(int k2 = -1; k2 <= 1; k2++ ){
	if(k2 * k2 != k1 * k1)
	if(points_in_shape.find(pair<int,int>(get<0>(random_point) + k1, get<1>(random_point) + k2)) == points_in_shape.end()){
	  possible_points.insert(pair<int,int>(get<0>(random_point) + k1, get<1>(random_point) + k2));
	}
      }
    }  
  }
  set_bounding_box();
  type = rand() % 5;
}

void Shape::Rotate(){
  vector<pair<int,int> > temp_points;
  for(int i = 0; i < points.size(); i++){
    temp_points.push_back(pair<int, int>(-get<1>(points[i]), get<0>(points[i])));
  }
  points = temp_points;
  set_bounding_box();
}

void Shape::set_bounding_box(){
  int min_x = 1000; int min_y = 1000; int max_x = -1000; int max_y = -1000;
  for(int i = 0; i < points.size(); i++){
    if(min_x > get<0>(points[i])){
      min_x = get<0>(points[i]);
    }
    if(min_y > get<1>(points[i])){
      min_y = get<1>(points[i]);
    }    
    if(max_x < get<0>(points[i])){
      max_x = get<0>(points[i]);
    }    
    if(max_y < get<1>(points[i])){
      max_y = get<1>(points[i]);
    }
  }
  bound_box_max = pair<int,int>(max_x - min_x, max_y - min_y);
  for(int i = 0; i < points.size(); i++){
    points[i] = pair<int, int>(get<0>(points[i]) - min_x, get<1>(points[i]) - min_y);
  }
}

pair<int, int> Shape::get_bounding_box(){
  return bound_box_max;
}
vector<pair<int,int> > Shape::get_points(){
  return points;
}


void Shape::PrintShape(){
  int rows = get<1>(bound_box_max) + 1;
  int cols = get<0>(bound_box_max) + 1;
  bool box[rows][cols];
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      box[i][j] = false;

  for(int i = 0; i < points.size(); i++){
    box[rows - get<1>(points[i]) - 1][get<0>(points[i])] = true;
  }
  char print;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      print = (box[i][j])? '0' : '*';
      cout << print;
    }
    cout << endl;
  }
}
/*
int main(){

  Shape s(5);
  s.PrintShape();
  return 0;
}
*/

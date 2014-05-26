#include <iostream>
#include <vector>
#include <utility>

#ifndef SHAPE_H
#define SHAPE_H

using namespace std;

class Shape{
 private:
  vector<pair<int, int> > points;
  pair<int, int> bound_box_max;
  void set_bounding_box();
 public:
  Shape();
  Shape(int n);
  pair<int, int> get_bounding_box();
  vector< pair<int, int> > get_points();
  int type;
  
  void Rotate();
  void PrintShape();
};

#endif

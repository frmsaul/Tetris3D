#include <vector>

//using namespace std;
#ifndef SHAPE_H
#define SHAPE_H

struct block{
  int X,Y,Z;
  block(int x, int y, int z){
    X = x;
    Y = y;
    Z = z;
  }
  block(){
    X = 0; Y = 0; Z = 0;
  }/*
  static inline bool operator==(const block& lhs, const block& rhs){ 
    return ((lhs.X == rhs.X) && (lhs.Z == rhs.Z) && (lhs.Y == rhs.Y));
  }*/
  bool operator==(const struct block& rhs) const {
    return ((this->X == rhs.X) && (this->Z == rhs.Z) && (this->Y == rhs.Y));
  }
};

class Shape{
 private:
  block bounding_box;
  void set_bounding_box();
  int type;
  void init(int n);
 public:
  Shape();
  Shape(int n);
  std::vector<block> points; //temporery
  void Rotate_x();
  void Rotate_y();
  void Rotate_z();

  void Print();
  int get_type(){return type;}
  std::vector<block> get_points(){return points;}
};

#endif

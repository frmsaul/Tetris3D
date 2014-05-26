#include <iostream>
#include "TetrisEngine.h"
#include <stdio.h>
#include <ctime>
#include <stdlib.h>

using std::cout;
using std::endl;


TetrisEngine::TetrisEngine(int x, int y, int z){
  sizeX = x; 
  sizeY = y;
  sizeZ = z;

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

/*
int main(){
  TetrisEngine tet(10,10,3);
  tet.RandomizeMats();
  tet.PrintTypeMat();
  return 0;
}
*/

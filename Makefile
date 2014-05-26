all: shape.cpp tetris2dEngine.cpp tetris2dGraphics.cpp
  g++ tetris2dEngine.cpp shape.cpp tetris2dGraphics.cpp -o tetris_Graphics -std=c++11 -lGL -lGLU -lglut -I

//---------------HPP files are header files, storing declarations, not definitions. Useful for sharing variables among files-------------------
//decleration: does not allocate memory | definition: allocates memory
#pragma once //prevent definition errors by ensuring only defined once in compilation. define guard
#define SNAKE_GAME_HPP

#include <vector>

//grid
extern char** spaces; //the spaces in the grid that actually get printed out
extern int width;
extern int height;
extern int padding;

//movement
enum direction {up = 0, left = 1, right = 2, down = 3};
extern direction playerDirection;
extern std::vector<direction> moveMemory;

//game logic
extern bool gameActive;
extern char input;
extern int framerate;

//snake
extern long headX; //the head of the snake is where the tail will follow from. It starts at the centre of the grid, and moves right automatically
extern long headY;

extern int tailLength;
extern std::vector<int> tailX;
extern int tailXIncrement;
extern std::vector<int> tailY;
extern int tailYIncrement;
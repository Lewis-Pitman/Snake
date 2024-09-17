//this file contains all the logic needed to initialise and render the grid

#include <iostream> //input output
#include <iomanip> //spacing of grid
#include <string>
#include <cstring>
#include <cmath>
#include <vector>

#include "variables.hpp"

//grid
char** spaces;

//snake
long headX {}; //the head of the snake is where the tail will follow from. It starts at the centre of the grid, and moves right automatically
long headY {}; 

int headXMemory {}; //Contains the last position the head was in. Necessary for adding onto the snake or clearing it to render the snake moving
int headYMemory {};

int tailLength {0};

class Screen
{
    private:
    int width {};
    int height {};
    int spacing {};

    void UpdateSnakePosition(){
        spaces[int(headY)][int(headX)] = '#';//head

        for(int i = 0; i <= tailLength; i++){
            if(i != tailLength){ //if our tail is not the length it should be
                switch(moveMemory[moveMemory.size() - i]){//we need to do the reverse of these directions to properly draw the tail
                    case up://down
                    spaces[int(headY + (i + 1))][int(headX)] = '#';
                    break;
                    case down://up
                    spaces[int(headY - (i + 1))][int(headX)] = '#';
                    break;
                    case left://right
                    spaces[int(headY)][int(headX + (i + 1))] = '#';
                    break;
                    case right://left
                    spaces[int(headY)][int(headX - (i + 1))] = '#';
                    break;
                    default:
                    break;
                }
            } else if(i == tailLength && tailLength != 0){//We have successfully drawn the tail to the desired length. Now we can set the tile before it to ' ' so that the snake isn't leaving parts of it's tail around the grid
                switch(moveMemory[moveMemory.size() - i]){
                    case up://down
                    spaces[int(headY + (i + 1))][int(headX)] = ' ';
                    break;
                    case down://up
                    spaces[int(headY - (i + 1))][int(headX)] = ' ';
                    break;
                    case left://right
                    spaces[int(headY)][int(headX + (i + 1))] = ' ';
                    break;
                    case right://left
                    spaces[int(headY)][int(headX - (i + 1))] = ' ';
                    break;
                    default:
                    break;
                }
            }else{
                break; //failsafe
            }
        }
    }

    void DrawLine(){
            std::cout << std::setw(spacing + 1); //start above the first "|"
            for(int i = 0; i < width; i++){
                for(int j = 0; j < (spacing * 2); j++)
                std::cout << "-"; //print out a line the same width as the grid
            }
            std::cout << "-"; //makes the line neater with an extra dash added to the line
    }

    void DrawScreen(){//contains the logic for drawing screen
        UpdateSnakePosition();
        std::cout << "\n";
        DrawLine(); //dividing line under the number line
        std::cout << "\n";

        for(int i = 0; i < height; i++){
            std::cout << std::setw(spacing + 1); //move grid further away from left side
            for(int j = 0; j < width; j++){
                std::cout << "|" << std::setw(spacing) << spaces[i][j] << std::setw(spacing); 
            }
        
        std::cout << "|";

        std::cout << "\n";
        DrawLine(); //dividing line
        std::cout << "\n";

    }
    }
    public:

    void ClearScreen(){
        //spaces[column][row]
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                spaces[i][j] = ' '; 
            }
        }

        headX = floor(width / 2);
        headY = floor(height / 2);
        headXMemory = headX;
        headYMemory = headY - 1; //to make sure rendering the snake works properly at the start
        spaces[headY][headX] = '#'; //set the beginning position of the player to the middle of the screen (or as close as we can get)
    }
    
    Screen(int _width, int _height, int _spacing){
        width = _width;
        height = _height;
        spacing = _spacing;

        spaces = new char*[_height];
        for(int i = 0; i < _height; i++){
            spaces[i] = new char[_width];
        } //2D array initialisation | "spaces" is a pointer to an array of pointers. Each pointer in this pointer array points to the memory address of another pointer.

        ClearScreen();

    }//constructor

    ~Screen(){
    }//deconstructor

    void Render(){
        DrawScreen();
    }

};
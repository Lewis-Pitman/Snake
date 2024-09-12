//this file contains all the logic needed to initialise and render the grid

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

char** spaces;

class Screen
{
    private:
    int width {};
    int height {};
    int spacing {};
    bool turn {false}; //false = X, true = O

    void DrawLine(){
            std::cout << std::setw(spacing + 1);
            for(int i = 0; i < width; i++){
                for(int j = 0; j < (spacing * 2); j++)
                std::cout << "-";
            }
            std::cout << "-";
    }

    void DrawScreen(){//contains the logic for drawing screen
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
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                spaces[i][j] = ' '; 
            }
        }
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
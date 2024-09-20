//this file contains all the logic needed to initialise and render the grid

#include <iostream> //input output
#include <iomanip> //spacing of grid
#include <cmath> //responsible for flooring the result of divisions later on
#include <vector> //needed to use the vector data type
#include <cstdlib> //C standard library, responsible for the rand() function

#include "variables.hpp"

//grid
char** spaces;

//snake
long headX {}; //the head of the snake is where the tail will follow from. It starts at the centre of the grid, and moves right automatically
long headY {}; 

int tailLength {1};
std::vector<int> tailX;
int tailXIncrement {};
std::vector<int> tailY;
int tailYIncrement {};

//fruit generation
int fruitX {};
int fruitY {};
bool fruitCollected {true};
bool validPosition {false};

int fruitCount {0};
int fruitNeededToWin {};

class Screen
{
    private:
    int width {};
    int height {};
    int spacing {};

    void GenerateFruit(){
        validPosition = false;

        while(!validPosition){
            //using % on rand gives a random number between 0 and the number given (e.g. width) - 1
            fruitX = rand() % width;
            fruitY = rand() % height;

            if(spaces[fruitY][fruitX] == ' '){
                validPosition = true;
            } else{
                validPosition = false;
            }
        }

        spaces[fruitY][fruitX] = '*';
    }

    void CheckCollision(){ //(with either the tail or a fruit)
        switch(spaces[int(headY)][int(headX)]){
            case '#':
            gameActive = false;
            Hang(1);
            break;
            case '*':
            fruitCount++;
            if(fruitCount == fruitNeededToWin){
                gameActive = false;
                Hang(2);
            } else{
                fruitCollected = true;
                tailLength++;
            }
            break;
            default:
            break;
        }
    }

    void UpdateSnakePosition(){
        if(!firstFrame){
            CheckCollision();
        }

        spaces[int(headY)][int(headX)] = '#';//head

        tailXIncrement = tailX.size() - 1;
        tailYIncrement = tailX.size() - 1;
        for(int i = 0; i < tailLength; i++){
            spaces[tailY[tailYIncrement]][tailX[tailXIncrement]] = '#';//updating tail
            tailXIncrement--;
            tailYIncrement--;
        }
        if(tailYIncrement < 0 && tailXIncrement < 0){
            spaces[tailY[0]][tailX[0]] = ' ';
        }else{
            spaces[tailY[tailYIncrement]][tailX[tailXIncrement]] = ' ';//removing the tile behind the snake
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

        if(fruitCollected){
            GenerateFruit();
            fruitCollected = false;
        }

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
        DrawLine();
        std::cout << "\n";
    }
        //score counter
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "\n";
        DrawLine();
        std::cout << "\n";

        std::cout << "Score: " << fruitCount;

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
        tailX.push_back(headX - 1);
        tailY.push_back(headY - 1);

        fruitNeededToWin = width * height;

        srand(time(NULL)); //this sets the seed of rand(). Not setting a seed causes it to default to 1, therefore giving the same output each time and not being random
        //time(null) returns the number of seconds since 00:00 GMT, January 1st 1970. This gives a new seed every time the program runs.

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
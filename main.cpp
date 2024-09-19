#include <iostream>
#include <conio.h> //windows specific terminal controls -> _kbhit checks if a key was pressed -> _getch gets the key pressed
#include <windows.h> //used for sleep() command

#include "includes\screen.cpp"
#include "includes\variables.hpp"


//DEBUG!!
bool swap {false};


//grid
int width;
int height;
int padding;

//game logic
bool gameActive {false};
char input {};
int framerate {};

//input
direction playerDirection {right};

//----------------------------------------
//general functions

void Initialise(){
    std::cout << "Enter width of play area (recommended: 10): ";
    std::cin >> width;
    std::cout << "\nEnter height of play area (recommended: 10): ";
    std::cin >> height;
    std::cout << "\nEnter padding (distance between tiles, recommended: 2) of play area: ";
    std::cin >> padding;
    std::cout << "\nEnter framerate in frames a second (recommended: 3): ";
    std::cin >> framerate;
    system("cls");
    std::cout << "\n-----You must use the WASD keys in order to move!-----";
    Sleep(2000/framerate);
    system("cls");
}

void Hang(int message){//this is so the program doesn't exit straight away, the user has to enter -1 in order to close the program
    int response {};
    while(response != -1){
        switch(message){
            case 0:
            std::cout << "\nYour snake hit the edge of the grid!\nEnter -1 to exit the program: ";
            break;
            case 1:
            std::cout << "\nYour snake ran into itself!\nEnter -1 to exit the program: ";
            break;
            case 2:
            std::cout << "\nYou won!\nEnter -1 to exit the program: ";
            break;
        }
        std::cin >> response;
    }
}

void Logic() {
    Sleep(1000/framerate); //sleep command is in milliseconds -> we can divide 1 second (1000ms) by our framerate to get the interval to update the screen to achieve this framerate
    if (_kbhit()) { //if key has been pressed
        input = _getch(); //assign input to the key that was pressed
        switch(input){
            case 'w':
                playerDirection = up;
            break;
            case 'a':
                playerDirection = left;
            break;
            case 'd':
                playerDirection = right;
            break;
            case 's':
                playerDirection = down;
            break;
            default:
            break;//if the player enters anything else, we should continue moving in the previous direction
        }
    }
        switch(playerDirection){ //handle actual movement
            case up:
            if(headY != 0){
                tailX.push_back(headX);
                tailY.push_back(headY);
                headY--;
            }else{
                gameActive = false; //if the snake hits the border of the screen, the game will end
            }
            break;
            case left:
            if(headX != 0){
                tailX.push_back(headX);
                tailY.push_back(headY);
                headX--;
            }else{
                gameActive = false;
            }
            break;
            case right:
            if(headX != width - 1){
                tailX.push_back(headX);
                tailY.push_back(headY);
                headX++;
            }else{
                gameActive = false;
            }
            break;
            case down:
            if(headY != height - 1){
                tailX.push_back(headX);
                tailY.push_back(headY);
                headY++;
            }else{
                gameActive = false; //if the snake hits the border of the screen, the game will end
            }
            break;
            default:
            break;
            }
    system("cls");
}

int main(){
    Initialise();
    Screen screen(width, height, padding);
    gameActive = true;
    while(gameActive){
        screen.Render();
        Logic();
    }
    Hang(0);
    return 0;
}
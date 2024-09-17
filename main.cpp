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
std::vector<direction> moveMemory;

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

    moveMemory.push_back(right); //starting direction
}

void Hang(){//this is so the program doesn't exit straight away, the user has to enter -1 in order to close the program
    int response {};
    while(response != -1){
        std::cout << "\nYour snake hit the edge of the grid!\nEnter -1 to exit the program: ";
        std::cin >> response;
    }
}

void Logic() {
    Sleep(1000/framerate); //sleep command is in milliseconds -> we can divide 1 second (1000ms) by our framerate to get the interval to update the screen to achieve this framerate
    //if (_kbhit()) { //if key has been pressed
        input = _getch(); //assign input to the key that was pressed
        switch(input){
        case 'w':
            playerDirection = up;
            std::cout << "\n you pressed w";
        break;
        case 'a':
            playerDirection = left;
            std::cout << "\n you pressed a";
        break;
        case 'd':
            playerDirection = right;
            std::cout << "\n you pressed d";
        break;
        case 's':
            playerDirection = down;
            std::cout << "\n you pressed s";
        break;
        default:
        break;//if the player enters anything else, we should continue moving in the previous direction
        }
        moveMemory.push_back(playerDirection);
    /*}else{
        moveMemory.push_back(playerDirection);
    }
    */
    switch(playerDirection){ //handle actual movement
        case up:
        if(headY != 0){
            headYMemory = headY;
            headXMemory = headX;
            headY--;
        }else{
            gameActive = false; //if the snake hits the border of the screen, the game will end
        }
        break;
        case left:
        if(headX != 0){
            headYMemory = headY;
            headXMemory = headX;
            headX--;
        }else{
            gameActive = false;
        }
        break;
        case right:
        if(headX != width - 1){
            headYMemory = headY;
            headXMemory = headX;
            headX++;
        }else{
            gameActive = false;
        }
        break;
        case down:
        if(headY != height - 1){
            headYMemory = headY;
            headXMemory = headX;
            headY++;
        }else{
            gameActive = false; //if the snake hits the border of the screen, the game will end
        }
        break;
        default:
        break;
    }
    //debug---
    if(swap){
        swap = false;
        tailLength++;
    } else{
        swap = true;
    }
    std::cout << "\n Tail length: " << tailLength;
    std::cout << "\n Move memory size: " << moveMemory.size();
    std::cout << "\n Tail memory contents: ";
    for(int i = 0; i < moveMemory.size(); i++){
        std::cout << moveMemory[i] << " -> ";
    }
    std::cout << "\n deleting " << headXMemory << headYMemory;
    std::cout << "\n delay:";
    Hang();
    system("cls"); //clear the terminal
    //-----
}

int main(){
    Initialise();
    Screen screen(width, height, padding);
    gameActive = true;
    while(gameActive){
        screen.Render();
        Logic();
    }
    Hang();
    return 0;
}
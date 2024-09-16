#include <iostream>
#include <conio.h> //windows specific terminal controls -> _kbhit checks if a key was pressed -> _getch gets the key pressed
#include <windows.h> //used for sleep() command
#include "includes\screen.cpp"

//screen
int width;
int height;
int padding;

//game logic
bool gameActive {false};
char input {};
int framerate {60};

//----------------------------------------
//general functions

void Initialise(){
    std::cout << "Enter width of play area (recommended: 10): ";
    std::cin >> width;
    std::cout << "\nEnter height of play area (recommended: 10): ";
    std::cin >> height;
    std::cout << "\nEnter padding (distance between tiles, recommended: 2) of play area: ";
    std::cin >> padding;
}

void Hang(){//this is so the program doesn't exit straight away, the user has to enter -1 in order to close the program
    int response {};
    while(response != -1){
        std::cout << "\nEnter -1 to exit the program: ";
        std::cin >> response;
    }
}

void Logic() {
    Sleep(100); //sleep command is in milliseconds -> 100 milliseconds = 10fps (looks better in terminal (I can't get clear screen to work))
    if (_kbhit()) {// Check if a key was pressed
        input = _getch();// Get the key (no need for Enter)
    }
}

int main(){
    Initialise();
    Screen screen(width, height, padding);
    gameActive = true;
    screen.Render();
    while(gameActive){
        Logic();
        screen.Render();
    }
    Hang();
    return 0;
}
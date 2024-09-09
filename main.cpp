#include <iostream>
#include "includes\screen.cpp"

//screen
int width;
int height;
int padding;

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

int main(){
    Initialise();
    Screen screen(width, height, padding);
    screen.Render();
    Hang();
    return 0;
}
#include <iostream>
#include <conio.h> //windows specific terminal controls -> _kbhit checks if a key was pressed -> _getch gets the key pressed

int main() {
    char input;
    std::cout << "Press any key, 'q' to quit:\n";
    
    while (true) {
        if (_kbhit()) {          // Check if a key was pressed
            input = _getch();        // Get the key (no need for Enter)
            std::cout << "You pressed: " << input << std::endl;
            if (input == 'q') break; // Quit on 'q'
        }
    }

    return 0;
}
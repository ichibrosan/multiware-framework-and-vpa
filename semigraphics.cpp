//
// Created by doug on 4/30/25.
//

#include "include/semigraphics.h"

#include <iostream>

semigraphics::semigraphics() {

}

void semigraphics::singlebox(int line, int col, int width, int height) {

    // Top line of box
    std::cout << "┌";
    for (int iColdex = col; iColdex<width-2; iColdex++) {
        std::cout << "─";
    }
    std::cout << "┐";
    std::cout << std::endl;

    // Middle lines of box
    for (int iLinedex = 1; iLinedex<height-1; iLinedex++) {
        std::cout << "│";
        for (int iLinedex = 0; iLinedex<width-2; iLinedex++) {
            std::cout << "\u0020";
        }
        std::cout << "│";
        std::cout << std::endl;
    }

    // Bottom line of box
    std::cout << "╰";
    for (int iColdex = col; iColdex<width-2; iColdex++) {
        std::cout << "─";
    }
    std::cout << "┘";


}
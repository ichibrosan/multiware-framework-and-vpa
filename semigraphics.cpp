////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/semigraphics.cpp 2025/05/01 16:54 dwg -  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

#include <iostream>

semigraphics::semigraphics() {

}

void semigraphics::singlebox(int line, int col, int width, int height) {
    gpCrt->crtlc(line,col);


    // Top line of box
    std::cout << "┌";
    for (int iColdex = col; iColdex<width-2; iColdex++) {
        std::cout << "─";
    }
    std::cout << "┐";
    std::cout << std::endl;

    // Middle lines of box
    for (int iLinedex = 0; iLinedex<height; iLinedex++) {
        //gpCrt->crtlc(iLinedex+1,1);
        std::cout << "│";
        for (int iColdex = 0; iColdex<width-3; iColdex++) {
            std::cout << "\u0020";
        }
        std::cout << "│";
        std::cout << std::endl;
    }

    // Bottom line of box
    //gpCrt->crtlc(1+height,1);
    std::cout << "╰";
    for (int iColdex = col; iColdex<width-2; iColdex++) {
        std::cout << "─";
    }
    std::cout << "┘";
    std::cout << std::endl;



}

void semigraphics::topline(int line, int col, int width, int height) {
    gpCrt->crtlc(line,col);


    // Top line of box
    std::cout << "┌";
    for (int iColdex = col; iColdex<width-2; iColdex++) {
        std::cout << "─";
    }
    std::cout << "┐";
    std::cout << std::endl;

}

void semigraphics::middleline(int line, int col, int width, int height, std::string ssText) {
        std::cout << "│";
        std::cout << ssText;
        std::cout << "│";
        std::cout << std::endl;
}

void semigraphics::endline(int line, int col, int width, int height) {
    std::cout << "╰";
    for (int iColdex = col; iColdex<width-2; iColdex++) {
        std::cout << "─";
    }
    std::cout << "┘";
    std::cout << std::endl;
}
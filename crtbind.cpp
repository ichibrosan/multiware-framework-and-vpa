//
// Created by doug on 4/30/25.
//

#include "mwfw2.h"

crtbind::crtbind() {

}

void crtbind::crtclr() {
    // erase entire screen
    std::cout << "\x1B[2J";
}

void crtbind::crtlc(int line,int col) {
    // move cursor to line/column
    std::cout << "\x1B[" << line << ";" << col << "H";
}

void crtbind::crtstyle(MODE_T mode, FG_COLORS_T fg, BG_COLORS_T bg) {
    std::cout << "\x1B[" << mode << ";" << fg << ";" << bg << "m";
}

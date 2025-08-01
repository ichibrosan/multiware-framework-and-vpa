////////////////////////////////////////////////////////////////////
// ~/public_html/fw/crtbind.cpp 2025-07-15 18:16 dwg -            //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

crtbind::crtbind()
{
}

void crtbind::crtclr()
{
    // erase entire screen
    std::cout << "\x1B[2J";
}

void crtbind::crtlc(int line, int col)
{
    // move cursor to line/column
    std::cout << "\x1B[" << line << ";" << col << "H";
}

void crtbind::crtstyle(MODE_T mode, FG_COLORS_T fg, BG_COLORS_T bg)
{
    std::cout << "\x1B[" << mode << ";" << fg << ";" << bg << "m";
}

////////////////////////////////////////////////////////////////////
// ~/public_html/fw/crtbind.h 2025-07-16 08:08 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#pragma once

enum MODE_T {
    MODE_RESET = 30,
    MODE_BOLD,
    MODE_DIM,
    MODE_ITALIC,
    MODE_UNDERLINE,
    MODE_BLINK,
    MODE_REVERSE = 37,
    MODE_HIDDEN,
    MODE_STRIKE
};

enum FG_COLORS_T {
    FG_RESET,
    FG_BLACK = 30,
    FG_RED,
    FG_GREEN,
    FG_YELLOW,
    FG_BLUE,
    FG_MAGENTA,
    FG_CYAN,
    FG_WHITE,
    FG_DEFAULT
};

enum BG_COLORS_T {
    BG_RESET,
    BG_BLACK = 40,
    BG_RED,
    BG_GREEN,
    BG_YELLOW,
    BG_BLUE,
    BG_MAGENTA,
    BG_CYAN,
    BG_WHITE,
    BG_DEFAULT
};

class crtbind {
public:
    crtbind();
    void crtclr();
    void crtlc(int line,int col);
    void crtstyle(MODE_T mode,FG_COLORS_T fg,BG_COLORS_T bg);
};

/////////////////////
// eof - crtbind.h //
/////////////////////
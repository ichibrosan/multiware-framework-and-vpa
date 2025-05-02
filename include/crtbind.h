//
// Created by doug on 4/30/25.
//

#ifndef CRTBIND_H
#define CRTBIND_H

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



#endif //CRTBIND_H

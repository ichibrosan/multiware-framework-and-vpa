////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/semigraphics.h   2025/05/01 16:54 dwg -  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#ifndef SEMIGRAPHICS_H
#define SEMIGRAPHICS_H

#define SV  "│"     // single vertical
#define SH  "─"     // single horizontal

// Single Rounded Corners
#define SRUL "╭"    // single rounded upper left
#define SRUR "╮"    // single rounded upper right
#define SRLL "╰"    // single rounded lower left
#define SRLR "╯"    // single rounded lower right

// Single Square Corners
#define SSUL "┌"    // single square upper left
#define SSUR "┐"    // single square upper right
#define SSLL "└"    // single square lower left
#define SSLR "┘"    // single square lower right

// Double Square Corners
#define DSUL "╔"    // double square upper left
#define DSUR "╗"    // double square upper right
#define DSLL "╚"    // double square lower left
#define DSLR "╝"    // double square lower right
#define DHL  "═"    // double horizontal line
#define DVL  "║"    // double vertical lines

// Single Vertical Corners
#define ULDHSV  "╒" // upper left double horizontal single vertical
#define URDHSV  "╕" // upper right double horizontal single vertical
#define LLDHSV  "╘" // lower left double horizontal single vertical
#define LRDHSV  "╛" // lower right double horizontal single vertical

// Double Vertical Corners
#define ULSHDV  "╓" // upper left single horizontal double vertical
#define URSHDV  "╖" // upper right single horizontal double vertical
#define LLSHDV  "╙" // lower left single horizontal double vertical
#define LRSHDV  "╜" // lower right single horizontal double vertical

// Double Line Extentions
#define DVDHR "╠"    // double vertical double right
#define DHDVL "╣"    // double horizontal double vertical
#define DHDVD "╦"   // double horizontal double vertical downward
#define DHDVU "╩"   // double horizontal double vertical upward

// Bi-Directional Extentions
#define DVSHRL  "╫" // double vertical single horizontal right & left
#define DHSVUP  "╪" // double horizontal single vertical up & down
#define DVERTEX "╬" // double horizontal double vertical cross

// Doublel Line Single Extentions
#define DHSDV "╤"   // double horizontal single downward vertical
#define DHSUV "╧"   // double horizontal single upward vertical
#define DVSHL "╢"   // double vertical single horizontal leftward
#define DVSHR "╟"   // double vertical single horizontal rightward

// Single Line Double Extentions
#define SVDHR "╞"   // single vertical double horizontal right
#define SVDHL "╡"   // single vertical double horizontal left
#define SHDVD "╥"   // single horizontal double vertical downward
#define SHDVU "╨"   // single horizontal double vertical upward

// Angular Components
#define FWDSLSH "╱" // lower left to upper right
#define BCKSLSH "╲" // upper left to lower right
#define SLNTEX  "╳"


class semigraphics {
public:
    semigraphics();
    void singlebox(int line, int col, int width, int height);
    void topline(int line, int col, int width, int height);
    void middleline(int line, int col, int width, int height,std::string ssText);
    void endline(int line, int col, int width, int height);
};



#endif //SEMIGRAPHICS_H

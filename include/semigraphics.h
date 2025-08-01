////////////////////////////////////////////////////////////////////
// ~/public_html/fw/semigraphics.h 2025-07-16 08:08 dwg -         //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#pragma once

#define COPR "©"
#define CHECK "✓"

#define SV  "│"     // single vertical
#define SH  "─"     // single horizontal
#define DV  "║"     // double vertical
#define DH  "═"     // double horizontal

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
#define SVSR "├"
#define SVSL "┤"
#define DVSR "╟"
#define DVSL "╢"

#define DVDHL "╣"    // double vertical double horizontal left
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


class semigraphics
{
    std::string m_ssUL;
    std::string m_ssUR;
    std::string m_ssLL;
    std::string m_ssLR;
    std::string m_ssVSR;
    std::string m_ssVSL;
    std::string m_ssHL;
    std::string m_ssVL;

public:
    semigraphics();
    void singlebox(int line, int col, int width, int height);
    void topline(int line, int col, int width, int height);
    void middleline(int line, int col, int width, int height,
                    std::string ssText);
    void vert_splitter(int line, int col, int width, int height);
    void endline(int line, int col, int width, int height);
    void cosmetics(std::string UpperLeft, std::string UpperRight,
                   std::string LowerLeft, std::string LowerRight,
                   std::string VertSplitRight, std::string VertSplitLeft,
                   std::string HorizontalLine, std::string VerticalLine);
};

//////////////////////////
// eof - semigraphics.h //
//////////////////////////

////////////////////////////////////////////////////////////////////
// ~/public_html/fw/crtbind.cpp 2025-07-15 18:16 dwg -            //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * @brief Default constructor for the crtbind class.
 * 
 * Initializes a new instance of the crtbind class, which provides
 * terminal control functionality using ANSI escape sequences.
 */
crtbind::crtbind()
{
}

/**
 * @brief Clears the entire terminal screen.
 * 
 * This method uses the ANSI escape sequence "\x1B[2J" to erase
 * the entire screen content. The cursor position remains unchanged
 * after clearing.
 */
void crtbind::crtclr()
{
    // erase entire screen
    std::cout << "\x1B[2J";
}

/**
 * @brief Positions the cursor at the specified line and column.
 * 
 * This method moves the cursor to the given coordinates using the
 * ANSI escape sequence "\x1B[line;colH". The coordinate system is
 * 1-based, where (1,1) represents the top-left corner of the terminal.
 * 
 * @param line The target line number (1-based indexing)
 * @param col The target column number (1-based indexing)
 */
void crtbind::crtlc(int line, int col)
{
    // move cursor to line/column
    std::cout << "\x1B[" << line << ";" << col << "H";
}

/**
 * @brief Sets terminal text styling attributes.
 * 
 * This method applies formatting styles to subsequent text output
 * using ANSI escape sequences. It allows setting text mode (bold,
 * italic, etc.), foreground color, and background color simultaneously.
 * 
 * @param mode The text mode/style to apply (from MODE_T enum)
 * @param fg The foreground (text) color (from FG_COLORS_T enum)
 * @param bg The background color (from BG_COLORS_T enum)
 * 
 * @note The styling remains active until changed or reset. Use
 *       MODE_RESET to return to default terminal styling.
 */
void crtbind::crtstyle(MODE_T mode, FG_COLORS_T fg, BG_COLORS_T bg)
{
    std::cout << "\x1B[" << mode << ";" << fg << ";" << bg << "m";
}

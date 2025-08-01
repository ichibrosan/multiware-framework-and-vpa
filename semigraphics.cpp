////////////////////////////////////////////////////////////////////
// ~/public_html/fw/semigraphics.cpp 2025-07-15 18:16 dwg -       //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"


/**
 * Constructor for the semigraphics class.
 *
 * Initializes an instance of the semigraphics class. This constructor
 * can be used to set up any necessary data or state specific to
 * semigraphics operations.
 */
semigraphics::semigraphics()
{
}

void semigraphics::cosmetics(std::string ssUL, std::string ssUR,
                             std::string ssLL, std::string ssLR,
                             std::string ssVSR, std::string ssVSL,
                             std::string ssHL, std::string ssVL)
{
    m_ssUL = ssUL;
    m_ssUR = ssUR;
    m_ssLL = ssLL;
    m_ssLR = ssLR;
    m_ssVSR = ssVSR;
    m_ssVSL = ssVSL;
    m_ssHL = ssHL;
    m_ssVL = ssVL;
}

/**
 * @brief Draws a single-line box at the specified starting position and dimensions.
 *
 * This function creates a rectangular box made of single-line border characters (such as ┌, ┐, ─,
 * │, and ╰) on the terminal. The box is drawn starting from the specified position and extends to
 * the given width and height.
 *
 * The box consists of:
 * - A top border containing ┌, ┐, and ─.
 * - Side borders containing │, leaving the inside blank (space characters).
 * - A bottom border containing ╰, ┘, and ─.
 *
 * @param line The starting vertical coordinate (line) for the top-left corner of the box.
 * @param col The starting horizontal coordinate (column) for the top-left corner of the box.
 * @param width The overall width of the box, including the borders.
 * @param height The overall height of the box, excluding the height of the top and bottom borders.
 */
void semigraphics::singlebox(int line, int col, int width, int height)
{
    // Top line of box
    std::cout << m_ssUL;
    for (int iColdex = col; iColdex < width - 2; iColdex++)
    {
        std::cout << m_ssHL;
    }
    std::cout << m_ssUR;
    std::cout << std::endl;

    // Middle lines of box
    for (int iLinedex = 0; iLinedex < height; iLinedex++)
    {
        std::cout << m_ssVL;
        for (int iColdex = 0; iColdex < width - 3; iColdex++)
        {
            std::cout << "\u0020";
        }
        std::cout << m_ssVL;
        std::cout << std::endl;
    }

    // Bottom line of box
    std::cout << m_ssLL;
    for (int iColdex = col; iColdex < width - 2; iColdex++)
    {
        std::cout << m_ssHL;
    }
    std::cout << m_ssLR;
    std::cout << std::endl;
}

/**
 * Draws the top line of a box utilizing semigraphic characters.
 *
 * This function initializes the cursor position using `gpCrt->crtlc()` and
 * outputs the top line of a box using Unicode box-drawing characters.
 * Specifically, it draws a top border starting with "┌", followed by a horizontal line "─"
 * repeated across the specified width (adjusted for the frame),
 * and ends with the corner character "┐".
 *
 * @param line The vertical line coordinate where the drawing starts.
 * @param col The horizontal column coordinate where the drawing starts.
 * @param width The total width of the box, including borders.
 * @param height The total height of the box. This parameter is currently not used in the function.
 */
void semigraphics::topline(int line, int col, int width, int height)
{
    // Top line of box
    std::cout << m_ssUL;
    for (int iColdex = col; iColdex < width - 2; iColdex++)
    {
        std::cout << m_ssHL;
    }
    std::cout << m_ssUR;
    std::cout << std::endl;
}

/**
 * @brief Draws a middle line with specified width and fills the remaining
 * space while centering the provided text within a bordered box.
 *
 * @param line The line position where the middle line is to be drawn.
 * @param col The column position where the middle line is to be drawn.
 * @param width The width of the middle line, inclusive of borders.
 * @param height Unused in the current implementation but retained to maintain
 *               consistency with similar drawing functions.
 * @param ssText The text to be displayed in the middle line.
 *
 * The function prints a line consisting of a vertical border ("│"),
 * followed by the specified text, and then spaces to fill the remaining
 * width until reaching the right border. The text is not justified but
 * simply left-aligned within the line space.
 */
void semigraphics::middleline(int line, int col,
                              int width, int height,
                              std::string ssText)
{
    std::cout << m_ssVL;
    std::cout << ssText;
    int textlen = ssText.size();
    if (textlen < width - 3)
    {
        int fillsize = width - 3 - textlen;
        for (int i = 0; i < fillsize; i++)
        {
            std::cout << " ";
        }
    }
    std::cout << m_ssVL;
    std::cout << std::endl;
}

void semigraphics::vert_splitter(int line, int col, int width, int height)
{
    std::cout << m_ssVSR;
    for (int iColdex = col; iColdex < width - 2; iColdex++)
    {
        std::cout << m_ssHL;
    }
    std::cout << m_ssVSL;
    std::cout << std::endl;
}


/**
 * @brief Renders the bottom line (endline) of a box or frame in semigraphics style.
 *
 * This function outputs a decorative bottom line with a specific semigraphics style.
 * It starts with the "╰" character, followed by a series of horizontal lines "─"
 * that span from the given starting column to the specified width. The line ends with "┘".
 *
 * @param line The starting line position (not utilized in this function).
 * @param col The starting column position on the console output.
 * @param width The total width of the box or frame.
 * @param height The total height of the box or frame (not utilized in this function).
 *
 * @note This function assumes that the output stream is directed to a console or terminal
 * that supports and properly renders Unicode characters such as "╰", "─", and "┘".
 */
void semigraphics::endline(int line, int col, int width, int height)
{
    std::cout << m_ssLL;
    for (int iColdex = col; iColdex < width - 2; iColdex++)
    {
        std::cout << m_ssHL;
    }
    std::cout << m_ssLR;
    std::cout << std::endl;
}

////////////////////////////
// eof - semigraphics.cpp //
////////////////////////////

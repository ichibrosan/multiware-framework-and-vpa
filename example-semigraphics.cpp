//////////////////////////////////////////////////////////////////////
// ~/public_html/fw/example-semigraphics.cpp 2025-08-07 03:26 dwg - //
// This file is part of MultiWare Engineering's VPA and FrameWork   //
//////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

/**
 * @file example-semigraphics.cpp
 * @brief Example application demonstrating the use of semigraphics and window classes
 * 
 * This file demonstrates how to use the MultiWare Engineering Framework (MWFW) to
 * create a simple console application that renders a window with semigraphic borders.
 * The example shows initialization of the framework, window creation, cosmetic
 * configuration, and rendering of content.
 * 
 * @author MultiWare Engineering
 * @date 2025-08-07
 * @version 5.8.7.3
 * @copyright Creative Commons CC0 1.0 Universal Public Domain Dedication
 * 
 * @see mwfw2.h For framework initialization
 * @see window.h For window management
 * @see semigraphics.h For border character definitions
 * @see version.h For version constants
 */

#include "mwfw2.h"

/**
 * @brief Main entry point for the semigraphics example application
 * 
 * This function demonstrates the typical workflow for creating a console
 * application using the MultiWare Framework:
 * 1. Initialize the MWFW framework
 * 2. Create a window instance
 * 3. Configure semigraphics cosmetics (border characters)
 * 4. Set window title with version information
 * 5. Add content to the window
 * 6. Render the window to the console
 * 
 * The example uses rounded single-line border characters for an aesthetically
 * pleasing appearance and displays version and copyright information.
 * 
 * @param argc Number of command-line arguments (unused in this example)
 * @param argv Array of command-line argument strings (unused in this example)
 * 
 * @return EXIT_SUCCESS (0) upon successful execution
 * 
 * @note The application creates dynamic memory allocations (pMwFw, pWin) but
 *       does not explicitly free them, relying on program termination cleanup.
 *       In a production application, proper memory management should be
 *       implemented.
 * 
 * @see mwfw2::mwfw2() For framework initialization details
 * @see window::set_title() For window title configuration
 * @see window::add_row() For adding content rows
 * @see window::render() For window rendering
 * @see semigraphics::cosmetics() For border character configuration
 * 
 * @example
 * Expected console output:
 * ╭────────────────────────────────────────────────────────────╮
 * │ Example Semigraphics Utility Ver 5.8.7.3                   │
 * ├────────────────────────────────────────────────────────────┤
 * │ Creative Commons CC0 1.0 Universal Public Domain Dedication│
 * ╰────────────────────────────────────────────────────────────╯
 */
int main(int argc, char** argv)
{
    /**
     * @brief Initialize the MultiWare Framework
     * 
     * Creates a new instance of the mwfw2 class, which handles:
     * - CGI environment detection
     * - System logging initialization
     * - Framework feature/event/debug set configuration
     * 
     * The __FILE__ and __FUNCTION__ macros provide context for logging.
     */
    auto* pMwFw = new mwfw2(__FILE__, __FUNCTION__);

    /**
     * @brief Create a new window instance
     * 
     * The window class handles:
     * - Dynamic sizing based on content
     * - Border rendering using semigraphics
     * - Text content management
     * - Console output rendering
     */
    auto* pWin = new window();

    /**
     * @brief Configure semigraphics cosmetics for window borders
     * 
     * Sets the character set used for drawing window borders and separators.
     * Uses rounded single-line characters for a modern appearance:
     * 
     * - SRUL (╭): Single Rounded Upper Left corner
     * - SRUR (╮): Single Rounded Upper Right corner  
     * - SRLL (╰): Single Rounded Lower Left corner
     * - SRLR (╯): Single Rounded Lower Right corner
     * - SVSR (├): Single Vertical Split Right (left border with horizontal line)
     * - SVSL (┤): Single Vertical Split Left (right border with horizontal line)
     * - SH (─):   Single Horizontal line
     * - SV (│):   Single Vertical line
     * 
     * @note gpSemiGr is a global pointer to the semigraphics instance,
     *       initialized by the mwfw2 framework
     */
    gpSemiGr->cosmetics(
        SRUL, SRUR, SRLL, // Corner characters: ┌ ┐ └ ┘
        SRLR, SVSR, SVSL, // Right corner and separators
        SH, SV); // Horizontal ─ and vertical │ lines
    
    /**
     * @brief Create and set the window title with version information
     * 
     * Constructs a version string using the version constants from version.h:
     * - RMAJ: Major version number (5)
     * - RMIN: Minor version number (8)
     * - RREV: Revision number (7)
     * - RBLD: Build number (3)
     * 
     * The resulting title provides clear identification of the application
     * and its version for debugging and user reference.
     */
    char szVersion[64];
    sprintf(szVersion, "Example Semigraphics Utility "
            "Ver %d.%d.%d.%d",RMAJ,RMIN,RREV,RBLD);
    pWin->set_title(szVersion);

    /**
     * @brief Add copyright/license information to the window
     * 
     * Adds a content row displaying the Creative Commons license information.
     * This provides legal clarity about the code's public domain status and
     * demonstrates the add_row() functionality for window content.
     */
    std::string ssCopr = "Creative Commons CC0 1.0 Universal Public Domain Dedication";
    pWin->add_row(ssCopr);

    /**
     * @brief Render the complete window to the console
     * 
     * This method handles:
     * - Calculating optimal window dimensions based on content
     * - Drawing the border using configured semigraphics
     * - Rendering the title bar with separator
     * - Outputting all content rows
     * - Positioning everything correctly on the console
     */
    pWin->render();

    /**
     * @brief Return successful execution status
     * 
     * EXIT_SUCCESS (defined as 0) indicates the program completed without errors.
     * This is the standard return value for successful C/C++ program execution.
     */
    return EXIT_SUCCESS;
}

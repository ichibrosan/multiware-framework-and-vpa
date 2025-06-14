

////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/vparpc_server.cpp 2025/02/19 18:38 dwg - //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

/**
 * @file vparpc_server.cpp
 * @brief Entry point for the Virtual Protocol Adapter RPC Server application
 * @author Douglas Wade Goodall
 * @date 2025-06-10
 * @version 5.5.10.2
 * @copyright Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.
 */

#include "mwfw2.h"

/**
 * @brief Entry point for the Virtual Protocol Adapter RPC Server.
 * 
 * This function serves as the main entry point for the Virtual Protocol Adapter RPC Server
 * application. It performs the following operations in sequence:
 * 
 * 1. Initializes the mwfw2 framework component with file and function information
 * 2. Creates and configures a user interface window with cosmetic settings
 * 3. Sets up the application title and copyright information
 * 4. Renders the user interface to display application information
 * 5. Starts the RPC server with the identifier "vparpc"
 * 
 * The application creates a visual interface showing copyright information and version
 * details before launching the RPC server functionality. The window is properly
 * cleaned up after rendering.
 * 
 * @param argc The number of command-line arguments passed to the program.
 *             This includes the program name as the first argument.
 * @param argv An array of C-style strings representing the command-line arguments.
 *             argv[0] typically contains the program name/path.
 * 
 * @return An integer indicating the exit status of the program:
 *         - 0: Program executed successfully
 *         - Non-zero: An error occurred during execution
 * 
 * @note The function uses several global objects:
 *       - gpSemiGr: For setting up UI cosmetics/appearance
 *       - gpVpaRpc: For managing the RPC server functionality
 * 
 * @warning Memory allocated for mwfw2 and window objects should be properly
 *          managed to prevent memory leaks. The window object is deleted
 *          after rendering, but mwfw2 object cleanup should be verified.
 * 
 * @see mwfw2 class for framework initialization details
 * @see window class for UI rendering functionality
 * @see gpVpaRpc->server() for RPC server implementation
 */
int main(int argc, char **argv) {
    // Initialize the middleware framework with current file and function context
    mwfw2 * pMwFw = new mwfw2(__FILE__, __FUNCTION__);

    // Create and configure the application window
    window * pWin = new window();
    
    // Set up UI cosmetics using predefined style constants
    // SRUL, SRUR, SRLL, SRLR, SVSR, SVSL, SH, SV appear to be styling parameters
    gpSemiGr->cosmetics(
        SRUL,  SRUR,  SRLL,
        SRLR,  SVSR,  SVSL,
        SH,    SV);
    
    // Construct copyright notice string
    std::string ssCopr = "Copyright ";
    ssCopr.append("(c)");
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");
    
    // Set application window title with version information
    pWin->set_title("Virtual Protocol Adapter RPC Server "
                    "Ver 5.5.10.2");
    
    // Add copyright information as a row in the window
    pWin->add_row(ssCopr);
    
    // Render the window to display the information
    pWin->render();
    
    // Clean up window resources
    delete pWin;

    // Start the RPC server with identifier "vparpc"
    // This call likely blocks until the server shuts down
    gpVpaRpc->server("vparpc");

    // Note: pMwFw should potentially be deleted here to prevent memory leak
    // delete pMwFw;

    return 0;
}
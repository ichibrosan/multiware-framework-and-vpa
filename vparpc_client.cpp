

////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/vparpc_client.cpp 2025/02/19 18:38 dwg - //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * @brief Entry point for the Virtual Protocol Adapter RPC Client application.
 *
 * This function serves as the main entry point for the VPA RPC Client. It performs
 * a complete client-side workflow including:
 * 
 * 1. Framework initialization using mwfw2 middleware
 * 2. User interface setup and configuration
 * 3. Display of application information and copyright notice
 * 4. RPC client request transmission to remote server
 * 5. Resource cleanup and program termination
 * 
 * The application creates a visual interface to display client information before
 * establishing communication with the RPC server. It sends a predefined test message
 * to demonstrate the RPC functionality.
 * 
 * @param argc The number of command-line arguments passed to the program.
 *             Standard argc parameter including program name as first argument.
 * @param argv Array of C-style strings containing command-line arguments.
 *             argv[0] typically contains the executable path/name.
 * 
 * @return Integer exit status code:
 *         - 0: Successful program execution and RPC communication
 *         - Non-zero: Error occurred during execution or RPC failure
 * 
 * @details Communication Details:
 *          - Target Host: "daphne" (remote server hostname/IP)
 *          - Service Name: "vparpc" (RPC service identifier)
 *          - Test Message: "Hello World Request 2"
 * 
 * @note Global Dependencies:
 *       - gpSemiGr: Semi-graphics interface manager for UI cosmetics
 *       - gpVpaRpc: Virtual Protocol Adapter RPC client interface
 * 
 * @warning Memory Management:
 *          - The mwfw2 instance (pMwFw) is allocated but not explicitly freed
 *          - Consider adding proper cleanup: delete pMwFw; before return
 * 
 * @see mwfw2 class for middleware framework functionality
 * @see window class for UI rendering and display operations
 * @see gpVpaRpc->client() for RPC client communication protocol
 * 
 * @example
 * Typical usage:
 * @code
 * ./vparpc_client
 * // Displays copyright window and sends RPC request to "daphne" server
 * @endcode
 */
int main(int argc, char **argv) {
    // Initialize middleware framework with current file and function context
    // This provides logging, error handling, and framework services
    mwfw2 * pMwFw = new mwfw2(__FILE__, __FUNCTION__);

    // Create user interface window for client information display
    window * pWin = new window();

    // Configure window appearance using semi-graphics cosmetic settings
    // Parameters define border styles, separators, and visual elements:
    // SRUL: Semi-graphic Upper Left, SRUR: Semi-graphic Upper Right
    // SRLL: Semi-graphic Lower Left, SRLR: Semi-graphic Lower Right  
    // SVSR: Semi-graphic Vertical Separator Right, SVSL: Semi-graphic Vertical Separator Left
    // SH: Semi-graphic Horizontal, SV: Semi-graphic Vertical
    gpSemiGr->cosmetics(
        SRUL,  SRUR,  SRLL,
        SRLR,  SVSR,  SVSL,
        SH,    SV);
    
    // Construct copyright notice string for display
    std::string ssCopr = "Copyright ";
    ssCopr.append("(c)");
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");
    
    // Set descriptive window title with application name and version
    pWin->set_title("Virtual Protocol Adapter RPC Client "
                    "Ver 5.5.10.2");
    
    // Add copyright information as a display row in the window
    pWin->add_row(ssCopr);
    
    // Render the configured window to the user interface
    pWin->render();
    
    // Clean up window resources after display
    delete pWin;

    // Prepare RPC request message payload
    // This is a test message to demonstrate RPC communication functionality
    std::string ssBuffer = "Hello World Request 2";
    
    // Execute RPC client request to remote server
    // Parameters:
    // - "daphne": Target server hostname or IP address
    // - "vparpc": RPC service name/identifier on the remote server
    // - ssBuffer: Message payload to transmit to the server
    gpVpaRpc->client(
        "daphne",
        "vparpc",
        ssBuffer);

    // delete pMwFw;

    return 0;
}
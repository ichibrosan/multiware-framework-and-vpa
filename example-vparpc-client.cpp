///////////////////////////////////////////////////////////////////////
// ~/public_html/fw/example-vparpc-client.cpp 2025-07-15 18:16 dwg - //
// This file is part of MultiWare Engineering's VPA and FrameWork /////
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

/**
 * @file example-vparpc-client.cpp
 * @brief Example VPA (Virtual Private Application) RPC Client Implementation
 * @author Douglas Wade Goodall
 * @date 2025-07-15
 * @version 1.0
 * 
 * @details
 * This application demonstrates the usage of the VPA RPC (Remote Procedure Call)
 * client functionality within the MultiWare Engineering Framework. It establishes
 * a connection to a VPA RPC server, performs authentication, retrieves system
 * information, and displays the results in a formatted console window.
 * 
 * The client performs the following operations:
 * 1. Connects to the specified VPA RPC server
 * 2. Retrieves version information from the server
 * 3. Performs service lookup operations
 * 4. Authenticates and retrieves user credentials
 * 5. Fetches server URL configurations
 * 6. Displays all retrieved information in a formatted window
 * 
 * @usage
 * ./example-vparpc-client <server> <service>
 * 
 * @param server The hostname or IP address of the VPA RPC server
 * @param service The service name or port to connect to on the server
 * 
 * @example
 * ./example-vparpc-client localhost 8080
 * ./example-vparpc-client 192.168.1.100 vparpc
 * 
 * @dependencies
 * - mwfw2 (MultiWare Framework v2)
 * - CVpaRpc (VPA RPC client class)
 * - pthread (POSIX threads)
 * - uuid (UUID generation library)
 * - cgicc (CGI C++ library)
 * 
 * @returns
 * - EXIT_SUCCESS (0) on successful completion
 * - EXIT_FAILURE (1) on error or insufficient arguments
 * 
 * @see CVpaRpc
 * @see mwfw2
 * @see window
 */

#include "mwfw2.h"

/**
 * @brief Main entry point for the VPA RPC client application
 * 
 * This function initializes the framework, validates command line arguments,
 * establishes a connection to the VPA RPC server, retrieves various system
 * information, and displays the results in a formatted console window.
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return EXIT_SUCCESS on successful completion, EXIT_FAILURE on error
 */
int main(int argc, char** argv)
{
        // Initialize the MultiWare Framework with current file and function info
        mwfw2* pMwFw = new mwfw2(__FILE__, __FUNCTION__);

        // Validate minimum argument count (program name + server)
        if (argc < 2)
        {
                std::cout << "Usage: " << argv[0] << " <server>" << std::endl;
                return EXIT_FAILURE;
        }

        // Log application startup information
        gpSysLog->loginfo(__FILE__);
        gpSysLog->loginfo(__PRETTY_FUNCTION__);
        
        // Validate complete argument count (program name + server + service)
        if (argc < 3)
        {
                std::cout << "Usage: " << argv[0] << " <server> <service>"
                        << std::endl;
                return EXIT_FAILURE;
        }

        // Create a new window instance for displaying results
        window* pWin = new window();

        // Configure window cosmetics with Unicode box-drawing characters
        // Sets up borders and separators for a professional appearance
        gpSemiGr->cosmetics(
                SRUL, SRUR, SRLL,    // Corner characters: ┌ ┐ └ ┘
                SRLR, SVSR, SVSL,    // Right corner and separators
                SH, SV);             // Horizontal ─ and vertical │ lines

        // Build copyright notice string for display
        std::string ssCopr = "  Copyright ";
        ssCopr.append("(c)"); // Append copyright symbol for compatibility
        ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");

        // Build application title with version information
        std::string ssTitle = "Example VPA RPC Client Version ";
        ssTitle.append(RSTRING);
        
        // Set window title and add copyright row
        pWin->set_title(ssTitle.c_str());
        pWin->add_row(ssCopr);

        // Create VPA RPC client instance with server and service parameters
        CVpaRpc* pVpaRpc = new CVpaRpc(argv[1], argv[2]);

        // Perform RPC calls to retrieve server information
        // Each call populates internal data structures within the CVpaRpc object
        
        pVpaRpc->get_version();  // Retrieve server version information
        pVpaRpc->get_lookup();   // Perform service lookup operation
        pVpaRpc->get_creds();    // Authenticate and get user credentials
        pVpaRpc->get_urls();     // Fetch server URL configurations

        char szAuthToken[64];
        sprintf(szAuthToken, "  auth:         %s",
                pVpaRpc->get_auth().c_str());
        pWin->add_row(szAuthToken);

        char szVersion[64];
        sprintf(szVersion, "  version:      %s",
                pVpaRpc->get_version_version().c_str());
        pWin->add_row(szVersion);

        int iHandle = pVpaRpc->m_vparpc_request_lookup.iHandle;
        char szHandle[64];
        sprintf(szHandle, "  handle:       %d", iHandle);
        pWin->add_row(szHandle);

        char szBuffer[BUFSIZ];

        sprintf(szBuffer, "  UserName:     %s",
                pVpaRpc->get_creds_username().c_str());
        pWin->add_row(szBuffer);

        sprintf(szBuffer, "  FirstName:    %s",
                pVpaRpc->get_creds_firstname().c_str());
        pWin->add_row(szBuffer);

        sprintf(szBuffer, "  LastName:     %s",
                pVpaRpc->get_creds_lastname().c_str());
        pWin->add_row(szBuffer);

        sprintf(szBuffer, "  Auth:         %s",
                pVpaRpc->get_creds_auth().c_str());
        pWin->add_row(szBuffer);

        sprintf(szBuffer, "  Level:        %s",
                pVpaRpc->get_creds_level().c_str());
        pWin->add_row(szBuffer);

        sprintf(szBuffer, "  IP:           %s",
                pVpaRpc->get_urls_ip().c_str());
        pWin->add_row(szBuffer);

        sprintf(szBuffer, "  szCgiRoot:    %s",
                pVpaRpc->get_urls_cgiroot().c_str());
        pWin->add_row(szBuffer);

        sprintf(szBuffer, "  szStylesRoot: %s",
                pVpaRpc->get_urls_stylesroot().c_str());
        pWin->add_row(szBuffer);

        pWin->render();

        return EXIT_SUCCESS;
}

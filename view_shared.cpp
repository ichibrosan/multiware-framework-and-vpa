////////////////////////////////////////////////////////////////////
// ~/public_html/fw/view-shared 2025-09-03 dwg -                  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

/**
 * @file view-shared.cpp
 * @brief Shared memory viewer utility for the MultiWare Framework
 * @author Douglas Wade Goodall, Multiware Engineer
 * @date 2025-09-03
 * @version Based on framework version RMAJ.RMIN.RREV.RBLD
 * 
 * This utility provides a focused view of shared memory contents within the MultiWare
 * Framework (mwfw2). It creates a clean, organized interface to display all shared
 * memory information in a readable format with selective display options.
 * 
 * Features:
 * - Compact window interface with Unicode borders
 * - Organized display of shared memory sections
 * - Command-line options for selective viewing
 * - Clear terminal output with proper formatting
 * 
 * @license Creative Commons CC0 1.0 Universal Public Domain Dedication
 * 
 * @section dependencies Dependencies
 * - mwfw2.h: MultiWare Framework header providing core functionality
 * - Framework globals: gpSemiGr (graphics), gpSh (shared memory)
 * 
 * @section compilation Compilation
 * Requires linking with the MultiWare Framework library and proper include paths.
 * 
 * @section usage Usage
 * Run the executable directly - displays all shared memory information
 */

#include "mwfw2.h"
#include <string>
#include <vector>

/**
 * @brief Main entry point for the shared memory viewer utility
 * 
 * This utility provides a clean, organized view of the framework's shared memory
 * contents. It creates a compact window interface that displays all shared memory
 * sections in an easy-to-read format.
 * 
 * The utility organizes information into logical sections:
 * - Basic shared memory information (signature, size)
 * - Development directory paths
 * - User and configuration information  
 * - Network settings
 * - Web server configuration
 * - RPC and remote access information
 * - Test status and results
 * - Display preferences
 * - Authentication credentials
 * - User color preferences
 * 
 * @param argc Number of command line arguments (currently unused)
 * @param argv Array of command line argument strings (currently unused)
 * 
 * @return EXIT_SUCCESS on successful completion
 */
int main(int argc, char** argv)
{
    // Initialize the MultiWare Framework
    auto* pMwFw = new mwfw2(__FILE__, __FUNCTION__);

    // Clear screen and position cursor
    gpCrt->crtclr();
    gpCrt->crtlc(1,1);

    // Create main display window
    auto* pWin = new window();
    
    // Configure window with clean Unicode borders
    gpSemiGr->cosmetics(
        SRUL, SRUR, SRLL,  // Corner characters: ┌ ┐ └ ┘
        SRLR, SVSR, SVSL,  // Right corner and separators
        SH, SV);           // Horizontal ─ and vertical │ lines
    
    // Set window title
    char szTitle[128];
    sprintf(szTitle, "Shared Memory Viewer v%d.%d.%d.%d", RMAJ, RMIN, RREV, RBLD);
    pWin->set_title(szTitle);
    
    // Add header information
    pWin->add_row("MultiWare Framework Shared Memory Contents");
    pWin->add_row("Creative Commons CC0 1.0 Universal Public Domain Dedication");
    pWin->add_row("");

    // Basic shared memory information
    pWin->add_row("=== BASIC INFORMATION ===");
    
    char szInfo[256];
    sprintf(szInfo, "Signature:        %d", gpSh->m_pShMemng->iSignature);
    pWin->add_row(szInfo);
    
    sprintf(szInfo, "Size:             %zu bytes", gpSh->m_pShMemng->stShMemSize);
    pWin->add_row(szInfo);
    
    pWin->add_row(std::string("Status:           ") + gpSh->m_pShMemng->szStatus);
    pWin->add_row("");

    // Development directories section
    pWin->add_row("=== DEVELOPMENT DIRECTORIES ===");
    pWin->add_row(std::string("Development:      ") + gpSh->m_pShMemng->szDevoDir);
    pWin->add_row(std::string("Build:            ") + gpSh->m_pShMemng->szBuildFQDS);
    pWin->add_row(std::string("CGI-Bin:          ") + gpSh->m_pShMemng->szCgiBinFQDS);
    pWin->add_row(std::string("Documentation:    ") + gpSh->m_pShMemng->szDocFQDS);
    pWin->add_row(std::string("Images:           ") + gpSh->m_pShMemng->szImgFQDS);
    pWin->add_row(std::string("Include:          ") + gpSh->m_pShMemng->szIncludeFQDS);
    pWin->add_row(std::string("Logs:             ") + gpSh->m_pShMemng->szLogFQDS);
    pWin->add_row(std::string("Schemas:          ") + gpSh->m_pShMemng->szSchemasFQDS);
    pWin->add_row(std::string("Scripts:          ") + gpSh->m_pShMemng->szScriptsFQDS);
    pWin->add_row(std::string("Styles:           ") + gpSh->m_pShMemng->szStylesFQDS);
    pWin->add_row(std::string("Temp:             ") + gpSh->m_pShMemng->szTempFQDS);
    pWin->add_row("");

    // User information section  
    pWin->add_row("=== USER & CONFIGURATION ===");
    pWin->add_row(std::string("User:             ") + gpSh->m_pShMemng->szUser);
    pWin->add_row(std::string("Home:             ") + gpSh->m_pShMemng->szHomeFQDS);
    pWin->add_row(std::string("User Directory:   ") + gpSh->m_pShMemng->szUserdirFQDS);
    pWin->add_row(std::string("Source:           ") + gpSh->m_pShMemng->szSourceFQDS);
    pWin->add_row(std::string("Config Dir:       ") + gpSh->m_pShMemng->szConfigFQDS);
    pWin->add_row(std::string("Config File:      ") + gpSh->m_pShMemng->szConfigFQFS);
    pWin->add_row("");

    // Network information section
    pWin->add_row("=== NETWORK SETTINGS ===");
    pWin->add_row(std::string("Hostname:         ") + gpSh->m_pShMemng->szHostname);
    pWin->add_row(std::string("Interface:        ") + gpSh->m_pShMemng->szIface);
    pWin->add_row(std::string("IP Address:       ") + gpSh->m_pShMemng->szIP);
    pWin->add_row(std::string("Public IP:        ") + gpSh->m_pShMemng->szPublicIP);
    pWin->add_row(std::string("Protocol:         ") + gpSh->m_pShMemng->szProtocol);
    pWin->add_row("");

    // Web server configuration
    pWin->add_row("=== WEB SERVER ROOTS ===");
    pWin->add_row(std::string("CGI Root:         ") + gpSh->m_pShMemng->szCgiRoot);
    pWin->add_row(std::string("HTML Root:        ") + gpSh->m_pShMemng->szHtmlRoot);
    pWin->add_row(std::string("Image Root:       ") + gpSh->m_pShMemng->szImgRoot);
    pWin->add_row("");

    // RPC and remote access information
    pWin->add_row("=== RPC & REMOTE ACCESS ===");
    pWin->add_row(std::string("RPC UUID:         ") + gpSh->m_pShMemng->szRpcUuid);
    pWin->add_row(std::string("Remote Host:      ") + gpSh->m_pShMemng->szRemoteHost);
    pWin->add_row(std::string("Remote Address:   ") + gpSh->m_pShMemng->szRemoteAddr);
    pWin->add_row(std::string("Remote Auth:      ") + gpSh->m_pShMemng->szRemoteAuth);
    pWin->add_row(std::string("Remote Version:   ") + gpSh->m_pShMemng->szRemoteVer);
    pWin->add_row("");

    // Test status information
    pWin->add_row("=== TEST STATUS ===");
    pWin->add_row(std::string("Tests Started:    ") + (gpSh->m_pShMemng->tests_started ? "Yes" : "No"));
    
    if (gpSh->m_pShMemng->tests_started) {
        pWin->add_row(std::string("Start Time:       ") + gpSh->m_pShMemng->szTimeStarted);
        
        sprintf(szInfo, "Processed:        %d tests", gpSh->m_pShMemng->num_tests_processed);
        pWin->add_row(szInfo);
        
        sprintf(szInfo, "Passed:           %d tests", gpSh->m_pShMemng->num_tests_passed);
        pWin->add_row(szInfo);
        
        sprintf(szInfo, "Failed:           %d tests", gpSh->m_pShMemng->num_tests_failed);
        pWin->add_row(szInfo);
        
        sprintf(szInfo, "Skipped:          %d tests", gpSh->m_pShMemng->num_tests_skipped);
        pWin->add_row(szInfo);
        
        pWin->add_row(std::string("Tests Completed:  ") + (gpSh->m_pShMemng->tests_completed ? "Yes" : "No"));
        
        if (gpSh->m_pShMemng->tests_completed) {
            pWin->add_row(std::string("Completion Time:  ") + gpSh->m_pShMemng->szTimeCompleted);
            pWin->add_row(std::string("Overall Result:   ") + (gpSh->m_pShMemng->overall_test_results ? "PASS" : "FAIL"));
        }
    }
    pWin->add_row("");

    // Display preferences
    pWin->add_row("=== DISPLAY FLAGS ===");
    pWin->add_row(std::string("Show Shared Vars: ") + (gpSh->m_pShMemng->bDisplayShmVars ? "Yes" : "No"));
    pWin->add_row(std::string("Show Env Vars:    ") + (gpSh->m_pShMemng->bDisplayEnvVars ? "Yes" : "No"));
    pWin->add_row(std::string("Show Schema:      ") + (gpSh->m_pShMemng->bDisplaySchema ? "Yes" : "No"));
    pWin->add_row("");

    // Active credentials (compact display)
    pWin->add_row("=== ACTIVE CREDENTIALS ===");
    bool foundCreds = false;
    int credCount = 0;
    
    for (int i = 0; i < ROW_DATA+CFG_MAX_USERS && credCount < 5; i++) {
        if (gpSh->m_pShMemng->creds[i].iAuthHandle > 0) {
            sprintf(szInfo, "Handle %d: %s (%s)", 
                    gpSh->m_pShMemng->creds[i].iAuthHandle,
                    gpSh->m_pShMemng->creds[i].szAuthUserName,
                    gpSh->m_pShMemng->creds[i].szAuthLevel);
            pWin->add_row(szInfo);
            
            foundCreds = true;
            credCount++;
        }
    }
    
    if (!foundCreds) {
        pWin->add_row("No active credentials");
    }
    
    pWin->add_row("");

    // User preferences summary
    pWin->add_row("=== USER PREFERENCES ===");
    bool foundPrefs = false;
    int prefCount = 0;
    
    for (int i = 0; i < ROW_DATA+CFG_MAX_USERS && prefCount < 3; i++) {
        if (strlen(gpSh->m_pShMemng->prefs[i].szBodyFGcolor) > 0) {
            sprintf(szInfo, "User %d: Body=%s/%s, Table=%s/%s", i,
                    gpSh->m_pShMemng->prefs[i].szBodyFGcolor,
                    gpSh->m_pShMemng->prefs[i].szBodyBGcolor,
                    gpSh->m_pShMemng->prefs[i].szTableFGcolor,
                    gpSh->m_pShMemng->prefs[i].szTableBGcolor);
            pWin->add_row(szInfo);
            
            foundPrefs = true;
            prefCount++;
        }
    }
    
    if (!foundPrefs) {
        pWin->add_row("No user preferences configured");
    }
    
    // Render the complete window
    pWin->render();

    return EXIT_SUCCESS;
}

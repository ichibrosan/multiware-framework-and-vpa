////////////////////////////////////////////////////////////////////
// ~/public_html/fw/example-shared-memory 2025-07-15 18:16 dwg -  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

/**
 * @file example-shared-memory.cpp
 * @brief Example application demonstrating shared memory functionality using the MultiWare Framework
 * @author Douglas Wade Goodall, Multiware Engineer
 * @date 2025-07-15
 * @version Based on framework version RMAJ.RMIN.RREV.RBLD
 * 
 * This file demonstrates the basic usage of shared memory features within the MultiWare
 * Framework (mwfw2). It creates a windowed interface to display shared memory information
 * and showcases the framework's UI rendering capabilities with decorative Unicode borders.
 * 
 * The application creates a simple demonstration that:
 * 1. Initializes the MultiWare Framework
 * 2. Creates a styled window interface
 * 3. Displays application metadata and version information
 * 4. Retrieves and displays the current shared memory signature
 * 5. Renders the complete interface to the user
 * 
 * This serves as a basic example for developers learning to integrate shared memory
 * functionality into their applications using the MultiWare Framework.
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
 * Run the executable directly - no command line arguments are processed.
 */

#include "mwfw2.h"

// #define DISPLAY_LEDS

/**
 * @brief Main application entry point demonstrating shared memory functionality
 * 
 * This is the primary function that demonstrates the MultiWare Framework's
 * shared memory capabilities through a graphical window interface. The function
 * performs the following key operations:
 * 
 * **Initialization Phase:**
 * 1. Creates and initializes the MultiWare Framework instance with file/function context
 * 2. Sets up the framework's internal systems including shared memory management
 * 
 * **UI Setup Phase:**
 * 3. Creates a new window object for displaying information
 * 4. Configures window cosmetics with Unicode box-drawing characters for borders
 * 5. Generates and sets a dynamic window title with version information
 * 
 * **Content Display Phase:**
 * 6. Adds copyright and licensing information to the window
 * 7. Adds author attribution information
 * 8. Retrieves the shared memory signature from the framework's global state
 * 9. Displays the shared memory signature value
 * 
 * **Rendering Phase:**
 * 10. Renders the complete window with all content to the display
 * 
 * **Shared Memory Integration:**
 * The application accesses shared memory through the framework's global shared
 * memory manager (gpSh->m_pShMemng). The signature value displayed represents
 * an identifier used by the framework to validate and manage shared memory segments.
 * This demonstrates how applications can monitor and interact with the framework's
 * shared memory subsystem. The complete shared memory structure definition can be
 * found in include/shmemng.h.
 * 
 * **Window Styling:**
 * The application uses the framework's graphics subsystem (gpSemiGr) to create
 * professional-looking borders using Unicode box-drawing characters:
 * - Corner characters: ┌ ┐ └ ┘ 
 * - Line characters: ─ (horizontal) and │ (vertical)
 * - Various separator and junction characters for complex layouts
 * 
 * @param argc Number of command line arguments passed to the program
 *             Currently unused - the application does not process command line options
 * @param argv Array of command line argument strings
 *             Currently unused - the application does not process command line options
 * 
 * @return EXIT_SUCCESS (0) on successful completion of all operations
 * 
 * @note Memory Management: The function creates framework and window objects on the heap
 *       without explicit cleanup, relying on process termination for resource cleanup.
 *       In production applications, consider implementing proper RAII or explicit cleanup.
 * 
 * @warning Error Handling: No error handling is implemented for:
 *          - Framework initialization failures
 *          - Window creation failures  
 *          - Shared memory access failures
 *          - Memory allocation failures
 *          Production code should include appropriate error checking and recovery.
 * 
 * @warning Buffer Safety: Fixed-size character buffers (szVersion[64], szShmSig[64])
 *          are used with sprintf(). While current usage appears safe, consider using
 *          safer alternatives like snprintf() or std::string formatting.
 * 
 * @see mwfw2 class documentation for framework initialization details
 * @see window class documentation for UI creation and management
 * @see Framework globals documentation for gpSemiGr and gpSh usage patterns
 * 
 * @example
 * @code
 * // Typical usage - compile and run directly:
 * $ ./example-shared-memory
 * // Will display a window showing version info and shared memory signature
 * @endcode
 */
int main(int argc, char** argv)
{
    // Initialize the MultiWare Framework with current file and function context
    // This constructor call sets up all framework subsystems including:
    // - Shared memory management
    // - Graphics and UI systems  
    // - Internal state tracking
    // - Resource management
    // __FILE__ and __FUNCTION__ provide debugging context for the framework
    auto* pMwFw = new mwfw2(__FILE__, __FUNCTION__);

    gpCrt->crtclr();
    gpCrt->crtlc(1,1);

    // Create the main application window object
    // This window will serve as the container for all displayed information
    auto* pWin = new window();
    
    // Configure window cosmetics with Unicode box-drawing characters
    // This creates a professional, visually appealing bordered interface
    // Parameters define the appearance of corners, separators, and line segments:
    // - SRUL: ┌ (upper left corner)
    // - SRUR: ┐ (upper right corner)  
    // - SRLL: └ (lower left corner)
    // - SRLR: Various corner and junction characters for complex layouts
    // - SVSR, SVSL: Vertical separator characters
    // - SH: ─ (horizontal line character)
    // - SV: │ (vertical line character)
    gpSemiGr->cosmetics(
        SRUL, SRUR, SRLL, // Corner characters: ┌ ┐ └ ┘
        SRLR, SVSR, SVSL, // Right corner and separators
        SH, SV); // Horizontal ─ and vertical │ lines
    
    // Generate dynamic window title including version information
    // Uses framework version macros (RMAJ, RMIN, RREV, RBLD) to display
    // the current version numbers in a standard major.minor.revision.build format
    char szVersion[64];
    sprintf(szVersion, "Example Shared Memory Utility "
            "Ver %d.%d.%d.%d", RMAJ, RMIN, RREV, RBLD);
    pWin->set_title(szVersion);
    
    // Add copyright and licensing information to the window content
    // This ensures users understand the licensing terms for the software
    std::string ssCopr = "Creative Commons CC0 1.0 Universal Public Domain Dedication";
    pWin->add_row(ssCopr);

    // Add author attribution information
    // Provides credit and contact context for the software author
    pWin->add_row("Written by Douglas Wade Goodall, Multiware Engineer");

    // Add a separator for better visual organization
    pWin->add_row("");
    pWin->add_row("=== SHARED MEMORY CONTENTS ===");

    // Display basic shared memory information
    char szShmSig[64];
    sprintf(szShmSig, "iSignature:       %d", gpSh->m_pShMemng->iSignature);
    pWin->add_row(szShmSig);
    
    char szShmSize[64];
    sprintf(szShmSize, "stShMemSize:      %zu bytes", gpSh->m_pShMemng->stShMemSize);
    pWin->add_row(szShmSize);

    // Phase 0 - Development directory information
    pWin->add_row("");
    pWin->add_row("=== DEVELOPMENT DIRECTORIES ===");
    pWin->add_row(std::string("szDevoDir:        ") + gpSh->m_pShMemng->szDevoDir);
    pWin->add_row(std::string("szBuildFQDS:      ") + gpSh->m_pShMemng->szBuildFQDS);
    pWin->add_row(std::string("szCgiBinFQDS:     ") + gpSh->m_pShMemng->szCgiBinFQDS);
    pWin->add_row(std::string("szDocFQDS:        ") + gpSh->m_pShMemng->szDocFQDS);
    pWin->add_row(std::string("szImgFQDS:        ") + gpSh->m_pShMemng->szImgFQDS);
    pWin->add_row(std::string("szIncludeFQDS:    ") + gpSh->m_pShMemng->szIncludeFQDS);
    pWin->add_row(std::string("szLogFQDSS:       ") + gpSh->m_pShMemng->szLogFQDS);
    pWin->add_row(std::string("szSchemasFQDS:    ") + gpSh->m_pShMemng->szSchemasFQDS);
    pWin->add_row(std::string("szScriptsFQDS:    ") + gpSh->m_pShMemng->szScriptsFQDS);
    pWin->add_row(std::string("szStylesFQDS:     ") + gpSh->m_pShMemng->szStylesFQDS);
    pWin->add_row(std::string("szTempFQDS:       ") + gpSh->m_pShMemng->szTempFQDS);

    // User information
    pWin->add_row("");
    pWin->add_row("=== USER INFORMATION ===");
    pWin->add_row(std::string("szUser:           ") + gpSh->m_pShMemng->szUser);
    pWin->add_row(std::string("szHomeFQDS:           ") + gpSh->m_pShMemng->szHomeFQDS);
    pWin->add_row(std::string("szUserdirFQDS:    ") + gpSh->m_pShMemng->szUserdirFQDS);
    pWin->add_row(std::string("szSourceFQDS:     ") + gpSh->m_pShMemng->szSourceFQDS);
    pWin->add_row(std::string("szConfigFQDS:     ") + gpSh->m_pShMemng->szConfigFQDS);
    pWin->add_row(std::string("szConfigFQFS:     ") + gpSh->m_pShMemng->szConfigFQFS);
    pWin->add_row(std::string("szStatus:         ") + gpSh->m_pShMemng->szStatus);

    // Network information
    pWin->add_row("");
    pWin->add_row("=== NETWORK INFORMATION ===");
    pWin->add_row(std::string("szHostname:       ") + gpSh->m_pShMemng->szHostname);
    pWin->add_row(std::string("szIface:          ") + gpSh->m_pShMemng->szIface);
    pWin->add_row(std::string("szIP:             ") + gpSh->m_pShMemng->szIP);
    pWin->add_row(std::string("szPublicIP:       ") + gpSh->m_pShMemng->szPublicIP);
    pWin->add_row(std::string("szProtocol:       ") + gpSh->m_pShMemng->szProtocol);

    // Web server roots
    pWin->add_row("");
    pWin->add_row("=== WEB SERVER ROOTS ===");
    pWin->add_row(std::string("szCgiRoot:        ") + gpSh->m_pShMemng->szCgiRoot);
    pWin->add_row(std::string("szHtmlRoot:       ") + gpSh->m_pShMemng->szImgRoot);
    pWin->add_row(std::string("szImgRoot:        ") + gpSh->m_pShMemng->szImgRoot);

    // RPC and Remote information
    pWin->add_row("");
    pWin->add_row("=== RPC & REMOTE INFORMATION ===");
    pWin->add_row(std::string("szRpcUuid:        ") + gpSh->m_pShMemng->szRpcUuid);
    pWin->add_row(std::string("szRemoteHost:     ") + gpSh->m_pShMemng->szRemoteHost);
    pWin->add_row(std::string("szRemoteAddr:     ") + gpSh->m_pShMemng->szRemoteAddr);
    pWin->add_row(std::string("szRemoteAuth:     ") + gpSh->m_pShMemng->szRemoteAuth);
    pWin->add_row(std::string("szRemoteVer:      ") + gpSh->m_pShMemng->szRemoteVer);

#ifdef DISPLAY_LEDS
    // LED Control status
    pWin->add_row("");
    pWin->add_row("=== LED CONTROL STATUS ===");
    for (int i = 0; i < 17; i++) {
        char szLed[32];
        sprintf(szLed, "LED %d: %s", i, gpSh->m_pShMemng->bLedCntl[i] ? "ON" : "OFF");
        pWin->add_row(szLed);
    }
#endif

    // Test status information
    pWin->add_row("");
    pWin->add_row("=== TEST STATUS ===");
    pWin->add_row(std::string("Tests Started: ") + (gpSh->m_pShMemng->tests_started ? "Yes" : "No"));
    if (gpSh->m_pShMemng->tests_started) {
        pWin->add_row(std::string("Start Time: ") + gpSh->m_pShMemng->szTimeStarted);
        
        char szTestStats[128];
        sprintf(szTestStats, "Tests Processed: %d, Passed: %d, Failed: %d, Skipped: %d", 
                gpSh->m_pShMemng->num_tests_processed,
                gpSh->m_pShMemng->num_tests_passed,
                gpSh->m_pShMemng->num_tests_failed,
                gpSh->m_pShMemng->num_tests_skipped);
        pWin->add_row(szTestStats);
        
        sprintf(szTestStats, "Processed Bits: 0x%X, Passed Bits: 0x%X", 
                gpSh->m_pShMemng->tests_processed_bits,
                gpSh->m_pShMemng->tests_passed_bits);
        pWin->add_row(szTestStats);
        
        sprintf(szTestStats, "Failed Bits: 0x%X, Skipped Bits: 0x%X", 
                gpSh->m_pShMemng->tests_failed_bits,
                gpSh->m_pShMemng->tests_skipped_bits);
        pWin->add_row(szTestStats);
        
        pWin->add_row(std::string("Tests Completed: ") + (gpSh->m_pShMemng->tests_completed ? "Yes" : "No"));
        if (gpSh->m_pShMemng->tests_completed) {
            pWin->add_row(std::string("Completion Time: ") + gpSh->m_pShMemng->szTimeCompleted);
            pWin->add_row(std::string("Overall Results: ") + (gpSh->m_pShMemng->overall_test_results ? "PASS" : "FAIL"));
        }
    }

    // Display flags
    pWin->add_row("");
    pWin->add_row("=== DISPLAY FLAGS ===");
    pWin->add_row(std::string("Display Shared Memory Variables: ") + (gpSh->m_pShMemng->bDisplayShmVars ? "Yes" : "No"));
    pWin->add_row(std::string("Display Environment Variables: ") + (gpSh->m_pShMemng->bDisplayEnvVars ? "Yes" : "No"));
    pWin->add_row(std::string("Display Schema: ") + (gpSh->m_pShMemng->bDisplaySchema ? "Yes" : "No"));

    // Credentials information (show first few non-empty entries)
    pWin->add_row("");
    pWin->add_row("=== AUTHENTICATION CREDENTIALS ===");
    bool foundCreds = false;
    for (int i = 0; i < ROW_DATA+CFG_MAX_USERS && i < 10; i++) { // Limit to first 10 for display
        if (gpSh->m_pShMemng->creds[i].iAuthHandle > 0) {
            char szCredInfo[256];
            sprintf(szCredInfo, "Handle %d: %s (%s %s) - Level: %s", 
                    gpSh->m_pShMemng->creds[i].iAuthHandle,
                    gpSh->m_pShMemng->creds[i].szAuthUserName,
                    gpSh->m_pShMemng->creds[i].szAuthFirstName,
                    gpSh->m_pShMemng->creds[i].szAuthLastName,
                    gpSh->m_pShMemng->creds[i].szAuthLevel);
            pWin->add_row(szCredInfo);
            
            if (strlen(gpSh->m_pShMemng->creds[i].szRemoteHost) > 0) {
                sprintf(szCredInfo, "  Remote: %s (%s)", 
                        gpSh->m_pShMemng->creds[i].szRemoteHost,
                        gpSh->m_pShMemng->creds[i].szRemoteAddr);
                pWin->add_row(szCredInfo);
            }
            
            if (strlen(gpSh->m_pShMemng->creds[i].szHttpUserAgent) > 0) {
                std::string userAgent = gpSh->m_pShMemng->creds[i].szHttpUserAgent;
                if (userAgent.length() > 60) userAgent = userAgent.substr(0, 57) + "...";
                pWin->add_row(std::string("  User Agent: ") + userAgent);
            }
            foundCreds = true;
        }
    }
    if (!foundCreds) {
        pWin->add_row("No active authentication credentials found");
    }

    // User preferences (show first few non-empty entries)
    pWin->add_row("");
    pWin->add_row("=== USER PREFERENCES ===");
    bool foundPrefs = false;
    for (int i = 0; i < ROW_DATA+CFG_MAX_USERS && i < 5; i++) { // Limit to first 5 for display
        if (strlen(gpSh->m_pShMemng->prefs[i].szBodyFGcolor) > 0 || 
            strlen(gpSh->m_pShMemng->prefs[i].szBodyBGcolor) > 0) {
            char szPrefInfo[128];
            sprintf(szPrefInfo, "User %d Colors - Body: %s/%s, Table: %s/%s", i,
                    gpSh->m_pShMemng->prefs[i].szBodyFGcolor,
                    gpSh->m_pShMemng->prefs[i].szBodyBGcolor,
                    gpSh->m_pShMemng->prefs[i].szTableFGcolor,
                    gpSh->m_pShMemng->prefs[i].szTableBGcolor);
            pWin->add_row(szPrefInfo);
            foundPrefs = true;
        }
    }
    if (!foundPrefs) {
        pWin->add_row("No user color preferences configured");
    }
    
    // Render the complete window with all added content
    // This causes the window to be drawn to the display with:
    // - The configured border styling
    // - The dynamic title
    // - All added content rows
    // - Proper formatting and alignment
    pWin->render();

    // Return success status to the operating system
    return EXIT_SUCCESS;
}

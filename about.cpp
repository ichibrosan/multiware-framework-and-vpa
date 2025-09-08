////////////////////////////////////////////////////////////////////
// ~/public_html/fw/about.cpp 2025-09-08 11:21 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

/**
 * @file about.cpp
 * @brief About page CGI that displays dashboard and version information
 * @author Douglas Wade Goodall, Multiware Engineer
 * @date 2025-09-05
 * @version Based on framework version RMAJ.RMIN.RREV.RBLD
 * 
 * This CGI program provides an "About" page for the MultiWare Framework
 * that displays both the standard dashboard interface and comprehensive
 * version information from version.h. This gives users and administrators
 * a complete view of the framework's build and configuration details.
 * 
 * Features:
 * - Standard dashboard interface with authentication
 * - Complete version information display
 * - Build details and system information
 * - Formatted HTML output with consistent styling
 * 
 * @license Creative Commons CC0 1.0 Universal Public Domain Dedication
 */

#include "mwfw2.h"

/**
 * @brief Main entry point for the about.cgi program
 * 
 * This function creates a comprehensive "About" page that combines the
 * standard dashboard interface with detailed version information from
 * version.h. It handles authentication, displays the navigation interface,
 * and presents all build and system information in a formatted table.
 * 
 * The page includes:
 * - Standard dashboard with authentication and navigation
 * - Version numbers (major, minor, revision, build)
 * - Build information (date, time, type, architecture)
 * - System information (OS, host, user, domain)
 * - Network details (IP, MAC address)
 * - Development environment details
 * 
 * @param argc Number of command line arguments (standard CGI)
 * @param argv Array of command line argument strings (standard CGI)
 * 
 * @return EXIT_SUCCESS on successful completion
 */
int main(int argc, char* argv[])
{
    // Initialize the MultiWare Framework
    auto* pMwFw = new mwfw2(__FILE__, __FUNCTION__);

    // Parse CGI form data
    cgicc::Cgicc cgi;
    /**
      * @brief Initialize and parse the password database
      *
      * Creates a CSV reader instance for the passwd.csv file and parses
      * the user credential data into memory for authentication processing.
      */
    // gpCsv = new readCsv("passwd.csv");
    // gpCsv->parseData();

    // Extract authentication parameters
    std::string ssUsername = cgi("username");
    std::string ssPassword = cgi("password");
    
    // Initialize HTML output
    gpHtml->open_html();
    gpHtml->open_head();
    gpHtml->title("About - MultiWare Framework");
    

    gpHtml->close_head();
    gpHtml->open_body();

   // Add main content area with version information
    gpHtml->open_div("main-content");
    
    // Page title
    gpHtml->print("<h1>About MultiWare Framework</h1>");
    gpHtml->print("<p>Complete version information for the MultiWare Framework</p>");
    
    gpHtml->open_table(1);
    
    // Table header
    gpHtml->print("<tr><th>Property</th><th>Value</th><th>Description</th></tr>");

    char szTemp[128];

    // Version numbers
    gpHtml->print("<tr><td><strong>Major Version</strong></td>");
    sprintf(szTemp,"<td>%d</td>", RMAJ);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Major release number</td></tr>");
    
    gpHtml->print("<tr><td><strong>Minor Version</strong></td>");
    sprintf(szTemp,"<td>%d</td>", RMIN);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Minor release number</td></tr>");

    gpHtml->print("<tr><td><strong>Revision</strong></td>");
    sprintf(szTemp,"<td>%d</td>", RREV);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Revision number</td></tr>");

    gpHtml->print("<tr><td><strong>Build</strong></td>");
    sprintf(szTemp,"<td>%d</td>", RBLD);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Build number</td></tr>");

    gpHtml->print("<tr><td><strong>Version String</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RSTRING);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Complete version string</td></tr>");

    gpHtml->print("<tr><td><strong>Short Version</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RSHORT);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Abbreviated version string</td></tr>");

    // // Build Information
    gpHtml->print("<tr><td colspan='3'><h3>Build Information</h3></td></tr>");
    //
    gpHtml->print("<tr><td><strong>Build Date</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RDATE);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Date when framework was compiled</td></tr>");

    gpHtml->print("<tr><td><strong>Build Time</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RTIME);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Time when framework was compiled</td></tr>");

    gpHtml->print("<tr><td><strong>Build Hash</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RBUILD);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Git commit hash for this build</td></tr>");

    gpHtml->print("<tr><td><strong>Build Type</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RTYPE);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Debug or Release build</td></tr>");

    // System Information
    gpHtml->print("<tr><td colspan='3'><h3>System Information</h3></td></tr>");

    gpHtml->print("<tr><td><strong>Architecture</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RARCH);
    gpHtml->print(szTemp);

    gpHtml->print("<td>System architecture</td></tr>");

    gpHtml->print("<tr><td><strong>CPU</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RCPU);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Processor architecture</td></tr>");

    gpHtml->print("<tr><td><strong>Operating System</strong></td>");
    sprintf(szTemp,"<td>%s</td>", ROS);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Operating system</td></tr>");

    gpHtml->print("<tr><td><strong>Hostname</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RHOST);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Build system hostname</td></tr>");

    gpHtml->print("<tr><td><strong>Build User</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RUSER);
    gpHtml->print(szTemp);
    gpHtml->print("<td>User who built the framework</td></tr>");

    gpHtml->print("<tr><td><strong>Domain</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RDOMAIN);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Domain name</td></tr>");


    // Network Information

    gpHtml->print("<tr><td colspan='3'><h3>Network Information</h3></td></tr>");

    gpHtml->print("<tr><td><strong>IP Address</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RIP);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Build system IP address</td></tr>");

    gpHtml->print("<tr><td><strong>MAC Address</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RMAC);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Build system MAC address</td></tr>");

    // Product Information
    gpHtml->print("<tr><td colspan='3'><h3>Product Information</h3></td></tr>");

    gpHtml->print("<tr><td><strong>Company</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RCOMPANY);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Company name</td></tr>");

    gpHtml->print("<tr><td><strong>Product</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RPRODUCT);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Product name</td></tr>");

    gpHtml->print("<tr><td><strong>Development IDE</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RIDEVER);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Development environment version</td></tr>");


    gpHtml->print("<tr><td><strong>License</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RCOPR);
    gpHtml->print(szTemp);
    gpHtml->print("<td>License information</td></tr>");

    gpHtml->print("<tr><td><strong>Comment</strong></td>");
    sprintf(szTemp,"<td>%s</td>", RCOMMENT);
    gpHtml->print(szTemp);
    gpHtml->print("<td>Build comment</td></tr>");
    
    gpHtml->close_table();
    

    gpHtml->close_body();
    gpHtml->close_html();

    delete pMwFw;
    
    return EXIT_SUCCESS;
}

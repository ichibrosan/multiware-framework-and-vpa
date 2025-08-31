////////////////////////////////////////////////////////////////////
// ~/public_html/fw/look.cpp 2025-07-15 18:16 dwg -               //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

void sine()
{
    auto* pWin = new window();
    gpSemiGr->cosmetics(
        SRUL, SRUR, SRLL, // Corner characters: ┌ ┐ └ ┘
        SRLR, SVSR, SVSL, // Right corner and separators
        SH, SV); // Horizontal ─ and vertical │ lines
    char szVersion[64];
    sprintf(szVersion, "Virtual Protocol Adapter Look Utility "
            "Ver %d.%d.%d.%d",RMAJ,RMIN,RREV,RBLD);
    pWin->set_title(szVersion);
    std::string ssCopr = "  Copyright ";
    ssCopr.append("(c)"); // Append copyright symbol for compatibility
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");
    pWin->add_row(ssCopr);
    pWin->render();
}


/**
 * The main entry point of the application. This function initializes
 * necessary components, executes core functionality by invoking specific
 * diagnostic and utility methods, and manages the overall application logic.
 *
 * @return An integer indicating the application's exit status. EXIT_SUCCESS
 * is returned upon successful completion.
 */
int main(int argc, char** argv)
{
    auto* pMwFw = new mwfw2(__FILE__, __FUNCTION__);
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    sine();
    cliLogin::checkPreviousLogin();

    if (argc > 1)
    {
        if (strcmp(argv[1], "-v") == 0)
        {
            std::cout << "Version: " << RMAJ << "." << RMIN << "." << RREV <<
                "." << RBLD << std::endl;
        }
        else if (strcmp(argv[1], "-h") == 0)
        {
            std::cout << "Usage: vpautil [-v] [-h] [-l]" << std::endl;
        }
        else if (strcmp(argv[1], "-l") == 0)
        {
            system("rm -f /home/devo/public_html/fw/log/*.log");
        }
        else if (strcmp(argv[1], "-p") == 0)
        {
            system(
                "/home/devo/public_html/fw/scripts/"
                         "push-ichibrosan-github-io.sh");
        }
    }


    return EXIT_SUCCESS;
}

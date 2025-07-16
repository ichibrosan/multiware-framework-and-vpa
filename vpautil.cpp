////////////////////////////////////////////////////////////////////
// ~/public_html/fw/look.cpp 2025-07-15 18:16 dwg -               //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
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
int main()
{
    auto* pMwFw = new mwfw2(__FILE__, __FUNCTION__);
    sine();
    cliLogin::checkPreviousLogin(
        "/home/doug/.config/multiware/config.ini");

    return EXIT_SUCCESS;
}

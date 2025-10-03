//////////////////////////////////////////////////////////////////////
// ~/public_html/fw/example-osrelease.cpp 2025-10-03 dwg -          //
// This file is part of MultiWare Engineering's VPA and FrameWork   //
//////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////


#include "mwfw2.h"

int main(int argc, char** argv)
{
    auto* pMwFw = new mwfw2(__FILE__, __FUNCTION__);

    system("cat /home/devo/public_html/fw/cfg/cfg-section.ini /etc/os-release > /home/devo/public_html/fw/tmp/os-release.ini");

    auto* pWin = new window();
    
    gpSemiGr->cosmetics(
        SRUL, SRUR, SRLL,
        // Corner characters: ┌ ┐ └ ┘
        SRLR, SVSR, SVSL,
        // Right corner and separators
        SH, SV);
        // Horizontal ─ and vertical │ lines
    
    char szVersion[64];
    sprintf(szVersion, "Multiware os-release Utility "
            "Ver %d.%d.%d.%d", RMAJ, RMIN, RREV, RBLD);
    pWin->set_title(szVersion);
    
    std::string ssCopr =
        "Creative Commons CC0 1.0 Universal Public Domain Dedication";
    pWin->add_row(ssCopr);
    pWin->add_row("Written by Douglas Wade Goodall, Multiware Engineer");


    // Create configuration manager object with the constructed file path
    cfgini config("/home/devo/public_html/fw/tmp/os-release.ini");
    if (config.load("/home/devo/public_html/fw/tmp/os-release.ini"))
    {
        //pWin->add_row("load was successful");
    }
    
    // // Define section names using descriptive variables for maintainability
    // // Structure is inspired by COBOL program divisions for logical organization
    // std::string ssCM = "ConfigurationMetadata";    // metadata
    // std::string ssID = "IdentificationDivision";   // Program identity
    // std::string ssED = "EnvironmentDivision";      // Runtime environment
    // std::string ssDD = "DataDivision";             // Data-related config
    // std::string ssPD = "ProcedureDivision";        // Procedural config
    

    // ================================
    // User Interface Display
    // ================================

    std::string ssTemp;
    std::string ssName;

    //pWin->add_row("Config file: /etc/os-release");

    ssName = "PRETTY_NAME";
    ssTemp = ssName;
    ssTemp.append(":        ");
    ssTemp.append(config.getVariable("os-release",ssName));
    pWin->add_row(ssTemp.c_str());

    ssName = "NAME";
    ssTemp = ssName;
    ssTemp.append(":               ");
    ssTemp.append(config.getVariable("os-release",ssName));
    pWin->add_row(ssTemp.c_str());

    ssName = "VERSION_ID";
    ssTemp = ssName;
    ssTemp.append(":         ");
    ssTemp.append(config.getVariable("os-release",ssName));
    pWin->add_row(ssTemp.c_str());

    ssName = "VERSION";
    ssTemp = ssName;
    ssTemp.append(":            ");
    ssTemp.append(config.getVariable("os-release",ssName));
    pWin->add_row(ssTemp.c_str());

    ssName = "VERSION_CODENAME";
    ssTemp = ssName;
    ssTemp.append(":   ");
    ssTemp.append(config.getVariable("os-release",ssName));
    pWin->add_row(ssTemp.c_str());

    ssName = "ID";
    ssTemp = ssName;
    ssTemp.append(":                 ");
    ssTemp.append(config.getVariable("os-release",ssName));
    pWin->add_row(ssTemp.c_str());

    ssName = "HOME_URL";
    ssTemp = ssName;
    ssTemp.append(":           ");
    ssTemp.append(config.getVariable("os-release",ssName));
    pWin->add_row(ssTemp.c_str());

    ssName = "SUPPORT_URL";
    ssTemp = ssName;
    ssTemp.append(":        ");
    ssTemp.append(config.getVariable("os-release",ssName));
    pWin->add_row(ssTemp.c_str());

    ssName = "BUG_REPORT_URL";
    ssTemp = ssName;
    ssTemp.append(":     ");
    ssTemp.append(config.getVariable("os-release",ssName));
    pWin->add_row(ssTemp.c_str());

    ssName = "PRIVACY_POLICY_URL";
    ssTemp = ssName;
    ssTemp.append(": ");
    ssTemp.append(config.getVariable("os-release",ssName));
    pWin->add_row(ssTemp.c_str());

    ssName = "ID_LIKE";
    ssTemp = ssName;
    ssTemp.append(":            ");
    ssTemp.append(config.getVariable("os-release",ssName));
    pWin->add_row(ssTemp.c_str());

    ssName = "DEBIAN_CODENAME";
    ssTemp = ssName;
    ssTemp.append(":    ");
    ssTemp.append(config.getVariable("os-release",ssName));
    pWin->add_row(ssTemp.c_str());



    // Render the complete window with all information
    pWin->render();

    /**
     * @brief Return successful execution status
     *
     * EXIT_SUCCESS (defined as 0) indicates the program completed without errors.
     * This is the standard return value for successful C/C++ program execution.
     * 
     * At this point:
     * - Configuration file has been created or updated
     * - All application metadata has been stored
     * - User interface has been displayed with status information
     * - All framework resources are ready for cleanup at process termination
     */
    return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////
// ~/public_html/fw/init_xinetd_vpa.cpp 2025-07-15 18:16 dwg -    //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**************************************************************
 * Display Retro Header Information IBM 5150 Monochrome style *
 **************************************************************/
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


void services_diag()
{
    CServices services;

    // // Get service information
    // ServiceInfo httpService = services.getService("http", "tcp");
    // if (!httpService.name.empty()) {
    //     std::cout << "HTTP runs on port " << httpService.port << std::endl;
    // }

    // Check if a service exists
    if (services.hasService("vpa"))
    {
        std::cout << "vpa service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa", 5164, "tcp", {"vpa-alias"}))
        {
            std::cout << "Service added successfully - vpa" << std::endl;
        }
    }

    if (services.hasService("vpa-disc"))
    {
        std::cout << "vpa-disc service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-disc", 5164, "udp", {"vpa-disc-alias"}))
        {
            std::cout << "Service added successfully - vpa-disc" << std::endl;
        }
    }


    if (services.hasService("vpad-start"))
    {
        std::cout << "vpa-start service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpad-start", 65353, "tcp",
                                {"vpa-start-alias"}))
        {
            std::cout << "Service added successfully - vpad-start" << std::endl;
        }
    }

    if (services.hasService("vpa-netstat"))
    {
        std::cout << "vpa-netstat service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-netstat", 65354, "tcp",
                                {"vpa-netstat-alias"}))
        {
            std::cout << "Service added successfully - vpa-netstat" <<
                std::endl;
        }
    }

    if (services.hasService("vpa-ip"))
    {
        std::cout << "vpa-ip service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-ip", 65355, "tcp", {"vpa-ip-alias"}))
        {
            std::cout << "Service added successfully - vpa-ip" << std::endl;
        }
    }

    if (services.hasService("vpa-curl"))
    {
        std::cout << "vpa-curl service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-curl", 5164, "tcp", {"vpa-curl-alias"}))
        {
            std::cout << "Service added successfully - vpa-curl" << std::endl;
        }
    }

    if (services.hasService("vpa-http"))
    {
        std::cout << "vpa-http service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-http", 65357, "tcp", {"vpa-http-alias"}))
        {
            std::cout << "Service added successfully - vpa-http" << std::endl;
        }
    }

    if (services.hasService("vpa-https"))
    {
        std::cout << "vpa-https service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-https", 65358, "tcp", {"vpa-https-alias"}))
        {
            std::cout << "Service added successfully - vpa-https" << std::endl;
        }
    }

    if (services.hasService("vpa-ipcs"))
    {
        std::cout << "vpa-ipcs service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-ipcs", 65359, "tcp", {"vpa-ipcs-alias"}))
        {
            std::cout << "Service added successfully - vpa" << std::endl;
        }
    }


    // Find services by pattern
    auto webServices = services.findServices("http");
    for (const auto& service : webServices)
    {
        std::cout << service.name << " on port " << service.port << std::endl;
    }
}

int xinetdcfg_diag()
{
    xinetcfg config;

    // Test VPA configuration generation
    std::cout << "=== VPA Xinetd Configuration Test ===" << std::endl;
    std::cout << "Number of services configured: " << config.getServiceCount()
        << std::endl;

    // Display service status
    config.displayVpaServiceStatus();

    // Generate and display configuration
    std::cout << "\n=== Generated VPA Configuration ===" << std::endl;
    std::string vpaConfig = config.generateVpaXinetdConfig();
    std::cout << vpaConfig << std::endl;

    // Check permissions before attempting to save
    if (!config.canModifyXinetd())
    {
        std::cout << "\n=== PERMISSION NOTICE ===" << std::endl;
        std::cout <<
            "Cannot modify /etc/xinetd.d/vpa - insufficient privileges." <<
            std::endl;
        config.displaySudoInstructions();
        std::cout << "\nConfiguration displayed above (dry-run mode)." <<
            std::endl;
        return 0;
    }

    // Automatically save the configuration without prompting
    std::cout << "\nSaving configuration to /etc/xinetd.d/vpa..." << std::endl;

    // Create backup first
    std::cout << "Creating backup of existing configuration..." << std::endl;
    if (!config.createBackup())
    {
        std::cout << "WARNING: Could not create backup file." << std::endl;
    }

    // Save the configuration
    if (config.saveConfig())
    {
        std::cout << "SUCCESS: Configuration saved to /etc/xinetd.d/vpa" <<
            std::endl;

        // Automatically reload xinetd
        std::cout << "Reloading xinetd service..." << std::endl;
        if (config.reloadXinetd())
        {
            std::cout << "SUCCESS: xinetd reloaded successfully." << std::endl;
        }
        else
        {
            std::cout <<
                "ERROR: Failed to reload xinetd. You may need to restart it manually."
                << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR: Failed to save configuration to /etc/xinetd.d/vpa"
            << std::endl;
        return 1;
    }

    return 0;
}

int main()
{
    auto* pMwFw = new mwfw2(__FILE__, __FUNCTION__);
    sine();
    services_diag();
    xinetdcfg_diag();
    return EXIT_SUCCESS;
}

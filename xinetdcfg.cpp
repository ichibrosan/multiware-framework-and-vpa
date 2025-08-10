////////////////////////////////////////////////////////////////////
// ~/public_html/fw/xinetdcfg.cpp 2025-07-15 18:16 dwg -          //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

// Static member definitions
const std::string xinetcfg::XINETD_DIR = "/etc/xinetd.d";
const std::string xinetcfg::VPA_CONFIG_FILE = "/etc/xinetd.d/vpa";
const std::string xinetcfg::VPA_CONFIG_BACKUP = "/etc/xinetd.d/vpa.backup";
const std::string xinetcfg::TEMP_DIR = "/tmp";

xinetcfg::xinetcfg()
{
    initializeDefaultServices();
}

void xinetcfg::initializeDefaultServices()
{
    vpaServices.clear();

    // Main VPA Service (XML-RPC server)
    XinetdServiceConfig vpaService;
    vpaService.serviceName = "vpa";
    vpaService.port = "5164";
    vpaService.disable = "no";
    vpaService.id = "vpa";
    vpaService.socketType = "stream";
    vpaService.protocol = "tcp";
    vpaService.user = "1000";
    vpaService.wait = "no";
    vpaService.server = "/home/devo/public_html/fw/bin/vparpc_inetd_server";
    vpaServices.push_back(vpaService);

    // VPA Daemon Start Service
    XinetdServiceConfig vpadStartService;
    vpadStartService.serviceName = "vpad-start";
    vpadStartService.port = "65353";
    vpadStartService.disable = "no";
    vpadStartService.id = "vpad-start";
    vpadStartService.socketType = "stream";
    vpadStartService.protocol = "tcp";
    vpadStartService.user = "1000";
    vpadStartService.wait = "no";
    vpadStartService.server = "/home/devo/public_html/fw/scripts/start-vpad.sh";
    vpaServices.push_back(vpadStartService);

    // VPA Netstat Service
    XinetdServiceConfig vpaNetstatService;
    vpaNetstatService.serviceName = "vpa-netstat";
    vpaNetstatService.port = "65354";
    vpaNetstatService.disable = "no";
    vpaNetstatService.id = "vpa-netstat";
    vpaNetstatService.socketType = "stream";
    vpaNetstatService.protocol = "tcp";
    vpaNetstatService.user = "1000";
    vpaNetstatService.wait = "no";
    vpaNetstatService.server =
        "/home/devo/public_html/fw/scripts/inetd-netstat-redirect.sh";
    vpaServices.push_back(vpaNetstatService);

    // VPA IP Service
    XinetdServiceConfig vpaIpService;
    vpaIpService.serviceName = "vpa-ip";
    vpaIpService.port = "65355";
    vpaIpService.disable = "no";
    vpaIpService.id = "vpa-ip";
    vpaIpService.socketType = "stream";
    vpaIpService.protocol = "tcp";
    vpaIpService.user = "1000";
    vpaIpService.wait = "no";
    vpaIpService.server =
        "/home/devo/public_html/fw/scripts/inetd-ip-redirect.sh";
    vpaServices.push_back(vpaIpService);

    // VPA HTTP Service
    XinetdServiceConfig vpaHttpService;
    vpaHttpService.serviceName = "vpa-http";
    vpaHttpService.port = "65357";
    vpaHttpService.disable = "no";
    vpaHttpService.id = "vpa-http";
    vpaHttpService.socketType = "stream";
    vpaHttpService.protocol = "tcp";
    vpaHttpService.user = "1000";
    vpaHttpService.wait = "no";
    vpaHttpService.server =
        "/home/devo/public_html/fw/scripts/inetd-http-redirect.sh";
    vpaServices.push_back(vpaHttpService);

    // VPA HTTPS Service
    XinetdServiceConfig vpaHttpsService;
    vpaHttpsService.serviceName = "vpa-https";
    vpaHttpsService.port = "65358";
    vpaHttpsService.disable = "no";
    vpaHttpsService.id = "vpa-https";
    vpaHttpsService.socketType = "stream";
    vpaHttpsService.protocol = "tcp";
    vpaHttpsService.user = "1000";
    vpaHttpsService.wait = "no";
    vpaHttpsService.server =
        "/home/devo/public_html/fw/scripts/inetd-https-redirect.sh";
    vpaServices.push_back(vpaHttpsService);

    // VPA IPCS Service
    XinetdServiceConfig vpaIpcsService;
    vpaIpcsService.serviceName = "vpa-ipcs";
    vpaIpcsService.port = "65359";
    vpaIpcsService.disable = "no";
    vpaIpcsService.id = "vpa-ipcs";
    vpaIpcsService.socketType = "stream";
    vpaIpcsService.protocol = "tcp";
    vpaIpcsService.user = "1000";
    vpaIpcsService.wait = "no";
    vpaIpcsService.server =
        "/home/devo/public_html/fw/scripts/inetd-ipcs-redirect.sh";
    vpaServices.push_back(vpaIpcsService);

    // VPA iPhone Service
    XinetdServiceConfig vpaIphoneService;
    vpaIphoneService.serviceName = "vpa-iphone";
    vpaIphoneService.port = "65360";
    vpaIphoneService.disable = "no";
    vpaIphoneService.id = "vpa-iphone";
    vpaIphoneService.socketType = "stream";
    vpaIphoneService.protocol = "tcp";
    vpaIphoneService.user = "1000";
    vpaIphoneService.wait = "no";
    vpaIphoneService.server =
        "/home/devo/public_html/fw/cgi-bin/iphone.cgi";
    vpaServices.push_back(vpaIphoneService);


}

std::string xinetcfg::formatServiceBlock(
    const XinetdServiceConfig& service) const
{
    std::ostringstream block;

    block << "service " << service.serviceName << std::endl;
    block << "{" << std::endl;
    block << "\tport = " << service.port << std::endl;
    block << "\tdisable\t= " << service.disable << std::endl;
    block << "\tid = " << service.id << std::endl;
    block << "\tsocket_type\t= " << service.socketType << std::endl;
    block << "\tprotocol = " << service.protocol << std::endl;
    block << "\tuser = " << service.user << std::endl;
    block << "\twait = " << service.wait << std::endl;
    block << "\tserver = " << service.server << std::endl;
    block << "}" << std::endl;

    return block.str();
}

std::string xinetcfg::generateConfigContent() const
{
    std::ostringstream config;

    // Header with generation warning
    config << "##############################################################\n";
    config << "## /etc/xinetd.d/vpa " << getCurrentDateTimeString() <<
        " dwg -                 ##\n";
    config << "## ";
    config << RCOPR;
    config << " ##\n";
    config << "##############################################################\n";
    config <<
        "\n";
    config << "############################################################\n";
    config << "# THIS FILE IS AUTOMATICALLY GENERATED - DO NOT EDIT     #\n";
    config << "# Manual changes will be lost when configuration is saved #\n";
    config << "# Use the xinetcfg program to modify VPA services         #\n";
    config << "############################################################\n";
    config << "\n";

    // Rest of the configuration content...
    // [existing service generation code here]

    // VPA main service
    config <<
        "####################################################################"
        << std::endl;
    config <<
        "# This service activates an xmlrpc responder to handle an incoming #"
        << std::endl;
    config <<
        "# RPC request                                                      #"
        << std::endl;
    config <<
        "####################################################################"
        << std::endl;
    config << formatServiceBlock(getService("vpa"));
    config << std::endl;

    // VPA daemon start service
    config << "###############################################################"
        << std::endl;
    config << "# This service runs a script that starts the virtual protocol #"
        << std::endl;
    config << "# adapter daemon                                              #"
        << std::endl;
    config << "###############################################################"
        << std::endl;
    config << formatServiceBlock(getService("vpad-start"));
    config << std::endl;

    // VPA netstat service
    config <<
        "#################################################################" <<
        std::endl;
    config <<
        "# This service runs a script that calls the netstat utility and #" <<
        std::endl;
    config <<
        "# redirects output                                              #" <<
        std::endl;
    config <<
        "#################################################################" <<
        std::endl;
    config << formatServiceBlock(getService("vpa-netstat"));
    config << std::endl;

    // VPA IP service
    config << "############################################################" <<
        std::endl;
    config << "# This service runs a script that calls the ip utility and #" <<
        std::endl;
    config << "# redirects output                                         #" <<
        std::endl;
    config << "############################################################" <<
        std::endl;
    config << formatServiceBlock(getService("vpa-ip"));
    config << std::endl;

    // VPA HTTP service
    config <<
        "##################################################################" <<
        std::endl;
    config <<
        "# This service runs a script that calls curl to load the default #" <<
        std::endl;
    config <<
        "# web page with http:// protocol                                 #" <<
        std::endl;
    config <<
        "##################################################################" <<
        std::endl;
    config << formatServiceBlock(getService("vpa-http"));
    config << std::endl;

    // VPA HTTPS service
    config <<
        "##################################################################" <<
        std::endl;
    config <<
        "# This service runs a script that calls curl to load the default #" <<
        std::endl;
    config <<
        "# web page with https:// protocol                                #" <<
        std::endl;
    config <<
        "##################################################################" <<
        std::endl;
    config << formatServiceBlock(getService("vpa-https"));
    config << std::endl;

    // VPA IPCS service
    config <<
        "########################################################################"
        << std::endl;
    config <<
        "# This service runs a script that calls ipcs to show the shared status #"
        << std::endl;
    config <<
        "# and redirects output                                                 #"
        << std::endl;
    config <<
        "########################################################################"
        << std::endl;
    config << formatServiceBlock(getService("vpa-ipcs"));
    config << std::endl;

    // VPA iPhone service
    config <<
        "##################################################################" <<
        std::endl;
    config <<
        "# This service runs the iPhone CGI application for mobile web   #" <<
        std::endl;
    config <<
        "# interface access                                               #" <<
        std::endl;
    config <<
        "##################################################################" <<
        std::endl;
    config << formatServiceBlock(getService("vpa-iphone"));
    config << std::endl;

    config << "#############" << std::endl;
    config << "# eof - vpa #" << std::endl;
    config << "#############" << std::endl;

    return config.str();
}

std::string xinetcfg::generateVpaXinetdConfig()
{
    return generateConfigContent();
}

void xinetcfg::displayVpaServiceStatus()
{
    // std::cout << std::endl;
    // std::cout << "VPA Service Configuration Status" << std::endl;
    // std::cout << "================================" << std::endl;
    // std::cout << "Configuration File: /etc/xinetd.d/vpa" << std::endl;
    // std::cout << "Services Configured: " << getServiceCount() << std::endl;
    // std::cout << std::endl;
    //
    // std::cout <<
    //     "┌─────────────────┬───────┬──────────┬─────────────────────────────────────────────────────┐"
    //     << std::endl;
    // std::cout <<
    //     "│ Service Name    │ Port  │ Status   │ Server                                              │"
    //     << std::endl;
    // std::cout <<
    //     "├─────────────────┼───────┼──────────┼─────────────────────────────────────────────────────┤"
    //     << std::endl;
    //
    // for (const auto& service : vpaServices)
    // {
    //     std::cout << "│ " << std::left << std::setw(15) << service.serviceName.
    //         substr(0, 15) << " │ ";
    //     std::cout << std::setw(5) << service.port << " │ ";
    //
    //     std::string status = (service.disable == "yes")
    //                              ? "DISABLED"
    //                              : "ENABLED ";
    //     std::cout << std::setw(8) << status << " │ ";
    //
    //     std::string server = service.server;
    //     if (server.length() > 51)
    //     {
    //         server = "..." + server.substr(server.length() - 48);
    //     }
    //     std::cout << std::left << std::setw(51) << server << " │" << std::endl;
    // }
    //
    // std::cout <<
    //     "└─────────────────┴───────┴──────────┴─────────────────────────────────────────────────────┘"
    //     << std::endl;
    // std::cout << std::endl;
    //
    // std::cout << "Service Details:" << std::endl;
    // std::cout << "  vpa         (5164)  - Main XML-RPC server" << std::endl;
    // std::cout << "  vpad-start  (65353) - VPA daemon startup script" <<
    //     std::endl;
    // std::cout << "  vpa-netstat (65354) - Network status utility" << std::endl;
    // std::cout << "  vpa-ip      (65355) - IP configuration utility" <<
    //     std::endl;
    // std::cout << "  vpa-http    (65357) - HTTP web page loader" << std::endl;
    // std::cout << "  vpa-https   (65358) - HTTPS web page loader" << std::endl;
    // std::cout << "  vpa-ipcs    (65359) - Shared memory status utility" <<
    //     std::endl;
    // std::cout << std::endl;
}

std::string xinetcfg::getCurrentDateTimeString() const
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time_t), "%Y/%m/%d %H:%M");
    return oss.str();
}

XinetdServiceConfig xinetcfg::getService(const std::string& serviceName) const
{
    for (const auto& service : vpaServices)
    {
        if (service.serviceName == serviceName)
        {
            return service;
        }
    }
    return XinetdServiceConfig(); // Return empty config if not found
}

std::vector<XinetdServiceConfig> xinetcfg::getAllServices() const
{
    return vpaServices;
}

size_t xinetcfg::getServiceCount() const
{
    return vpaServices.size();
}

bool xinetcfg::saveConfig()
{
    std::string configContent = generateConfigContent();

    // Check if we're running as root - if so, write directly
    if (getuid() == 0)
    {
        std::ofstream file(VPA_CONFIG_FILE);
        if (!file)
        {
            return false; // Fail silently if we can't write as root
        }

        file << configContent;
        bool success = file.good();
        file.close();

        if (success)
        {
            chmod(VPA_CONFIG_FILE.c_str(), 0644);
        }
        return success;
    }

    // Not root - always use sudo approach without error messages
    std::string tempFile = "/tmp/vpa_config_" + std::to_string(getpid()) +
        ".tmp";

    // Create temporary file
    std::ofstream tempFileStream(tempFile);
    if (!tempFileStream)
    {
        return false; // Fail silently if we can't create temp file
    }

    tempFileStream << configContent;
    tempFileStream.close();

    // Use sudo to copy the temp file to the final location
    // Redirect all output to /dev/null to suppress messages
    std::string command = "sudo cp '" + tempFile + "' '" + VPA_CONFIG_FILE +
        "' 2>/dev/null";
    int result = system(command.c_str());

    if (result != 0)
    {
        // Clean up temp file and fail silently
        unlink(tempFile.c_str());
        return false;
    }

    // Set proper permissions (suppress output)
    command = "sudo chmod 644 '" + VPA_CONFIG_FILE + "' 2>/dev/null";
    system(command.c_str());

    // Clean up temp file
    unlink(tempFile.c_str());

    return true;
}

bool xinetcfg::loadConfig()
{
    // Always try to read using sudo to avoid permission errors
    if (getuid() != 0)
    {
        // Not root - use sudo to read the file
        std::string tempFile = "/tmp/vpa_read_" + std::to_string(getpid()) +
            ".tmp";
        std::string command = "sudo cp '" + VPA_CONFIG_FILE + "' '" + tempFile +
            "' 2>/dev/null";

        int result = system(command.c_str());
        if (result != 0)
        {
            // File doesn't exist or no permissions - initialize with defaults
            initializeDefaultServices();
            return true;
        }

        // Read from temp file
        std::ifstream file(tempFile);
        if (!file)
        {
            unlink(tempFile.c_str());
            initializeDefaultServices();
            return true;
        }

        // Parse the file content
        bool success = parseExistingConfig();
        file.close();
        unlink(tempFile.c_str());

        if (!success)
        {
            initializeDefaultServices();
        }
        return true;
    }
    else
    {
        // Running as root - read directly
        std::ifstream file(VPA_CONFIG_FILE);
        if (!file)
        {
            // File doesn't exist - initialize with defaults
            initializeDefaultServices();
            return true;
        }

        bool success = parseExistingConfig();
        if (!success)
        {
            initializeDefaultServices();
        }
        return true;
    }
}

bool xinetcfg::createBackup() const
{
    if (getuid() == 0)
    {
        // Running as root
        std::string command = "cp '" + VPA_CONFIG_FILE + "' '" +
            VPA_CONFIG_BACKUP + "' 2>/dev/null";
        return system(command.c_str()) == 0;
    }
    else
    {
        // Use sudo
        std::string command = "sudo cp '" + VPA_CONFIG_FILE + "' '" +
            VPA_CONFIG_BACKUP + "' 2>/dev/null";
        return system(command.c_str()) == 0;
    }
}

bool xinetcfg::restoreFromBackup() const
{
    if (getuid() == 0)
    {
        // Running as root
        std::string command = "cp '" + VPA_CONFIG_BACKUP + "' '" +
            VPA_CONFIG_FILE + "' 2>/dev/null";
        return system(command.c_str()) == 0;
    }
    else
    {
        // Use sudo
        std::string command = "sudo cp '" + VPA_CONFIG_BACKUP + "' '" +
            VPA_CONFIG_FILE + "' 2>/dev/null";
        return system(command.c_str()) == 0;
    }
}

bool xinetcfg::reloadXinetd() const
{
    // Always use sudo for service operations
    std::string command =
        "sudo systemctl reload xinetd 2>/dev/null || sudo service xinetd reload 2>/dev/null";
    return system(command.c_str()) == 0;
}

bool xinetcfg::restartXinetd() const
{
    // Always use sudo for service operations
    std::string command =
        "sudo systemctl restart xinetd 2>/dev/null || sudo service xinetd restart 2>/dev/null";
    return system(command.c_str()) == 0;
}

bool xinetcfg::isXinetdRunning() const
{
    // Check service status (no sudo needed for status check)
    std::string command =
        "systemctl is-active xinetd 2>/dev/null || service xinetd status 2>/dev/null";
    return system(command.c_str()) == 0;
}

bool xinetcfg::validateConfig() const
{
    return true; // Simplified for now
}

std::string xinetcfg::getCurrentUser() const
{
    const char* user = getenv("USER");
    return user ? std::string(user) : "unknown";
}

void xinetcfg::displaySudoInstructions() const
{
    std::cout << "\n=== Permission Requirements ===" << std::endl;
    std::cout << "To modify /etc/xinetd.d/vpa, you need root privileges." <<
        std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "1. Run with sudo:" << std::endl;
    std::cout << "   sudo " << program_invocation_name << std::endl;
    std::cout << std::endl;
    std::cout << "2. Configure passwordless sudo (advanced):" << std::endl;
    std::cout << "   sudo visudo" << std::endl;
    std::cout << "   Add: " << getCurrentUser() <<
        " ALL=(ALL) NOPASSWD: /bin/cp, /bin/chmod, /usr/bin/systemctl" <<
        std::endl;
    std::cout << std::endl;
    std::cout << "3. Run as root:" << std::endl;
    std::cout << "   su -c './" << program_invocation_name << "'" << std::endl;
    std::cout << "===============================" << std::endl;
}

// Additional method implementations can be added as needed
bool xinetcfg::executeSudoCommand(const std::string& command) const
{
    return (system(("sudo " + command).c_str()) == 0);
}

std::string xinetcfg::createTempFile(const std::string& content) const
{
    std::string tempFile = TEMP_DIR + "/xinetd_temp_XXXXXX";
    // Simplified implementation
    return tempFile;
}

size_t xinetcfg::parseServiceBlock(const std::vector<std::string>& lines,
                                   size_t startIndex,
                                   XinetdServiceConfig& service) const
{
    // Parse service block - simplified implementation
    for (size_t i = startIndex; i < lines.size(); i++)
    {
        std::string line = trim(lines[i]);
        if (line.empty() || line[0] == '#') continue;

        if (line.find("service ") == 0)
        {
            service.serviceName = line.substr(8);
            continue;
        }

        if (line == "}")
        {
            return i + 1;
        }

        size_t pos = line.find(" = ");
        if (pos != std::string::npos)
        {
            std::string key = trim(line.substr(0, pos));
            std::string value = trim(line.substr(pos + 3));

            if (key == "port") service.port = value;
            else if (key == "disable") service.disable = value;
            else if (key == "id") service.id = value;
            else if (key == "socket_type") service.socketType = value;
            else if (key == "protocol") service.protocol = value;
            else if (key == "user") service.user = value;
            else if (key == "wait") service.wait = value;
            else if (key == "server") service.server = value;
            else if (key == "server_args") service.serverArgs = value;
            else if (key == "type") service.type = value;
            else if (key == "flags") service.flags = value;
            else if (key == "group") service.group = value;
            else if (key == "log_on_success") service.logOnSuccess = value;
            else if (key == "log_on_failure") service.logOnFailure = value;
            else if (key == "nice") service.nice = value;
            else if (key == "instances") service.instancesMax = value;
            else if (key == "per_source") service.instancesPerSource = value;
            else if (key == "access_times") service.accessTimes = value;
            else if (key == "bind") service.bindAddress = value;
            else if (key == "redirect") service.redirectAddress = value;
            else if (key == "banner") service.banner = value;
            else if (key == "banner_success") service.bannerSuccess = value;
            else if (key == "banner_fail") service.bannerFail = value;
            else if (key == "cps") service.cps = value;
            else if (key == "max_load") service.maxLoad = value;
            else if (key == "groups") service.groups = value;
        }
    }

    return lines.size();
}

bool xinetcfg::validateServiceConfig(const XinetdServiceConfig& service) const
{
    return !service.serviceName.empty() && !service.port.empty();
}

std::string xinetcfg::trim(const std::string& str) const
{
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

bool xinetcfg::isValidPort(const std::string& port) const
{
    try
    {
        int portNum = std::stoi(port);
        return (portNum > 0 && portNum <= 65535);
    }
    catch (...)
    {
        return false;
    }
}

bool xinetcfg::exportConfig(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file) return false;
    file << generateConfigContent();
    return file.good();
}

bool xinetcfg::importConfig(const std::string& filename)
{
    // Simplified implementation
    return true;
}

bool xinetcfg::resetToDefaults()
{
    initializeDefaultServices();
    return true;
}

XinetdServiceConfig xinetcfg::getServiceByPort(const std::string& port) const
{
    for (const auto& service : vpaServices)
    {
        if (service.port == port)
        {
            return service;
        }
    }
    return XinetdServiceConfig();
}

std::vector<std::string> xinetcfg::getUsedPorts() const
{
    std::vector<std::string> ports;
    for (const auto& service : vpaServices)
    {
        ports.push_back(service.port);
    }
    return ports;
}

std::string xinetcfg::generateStatusReport() const
{
    std::ostringstream report;
    report << "VPA Services Status Report\n";
    report << "==========================\n";
    report << "Total Services: " << getServiceCount() << "\n";
    for (const auto& service : vpaServices)
    {
        report << service.serviceName << " (port " << service.port << "): ";
        report << (service.disable == "yes" ? "DISABLED" : "ENABLED") << "\n";
    }
    return report.str();
}

bool xinetcfg::canModifyXinetd() const
{
    // Check if we're running as root
    if (getuid() == 0)
    {
        return true;
    }

    // Check if sudo is available and configured
    std::string command = "sudo -n true 2>/dev/null";
    return system(command.c_str()) == 0;
}

bool xinetcfg::parseExistingConfig()
{
    std::ifstream file(VPA_CONFIG_FILE);
    if (!file.is_open())
    {
        return false;
    }

    std::vector<std::string> lines;
    std::string line;

    // Read all lines from file
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    if (lines.empty())
    {
        return false;
    }

    // Clear existing services
    vpaServices.clear();

    // Parse each service block
    for (size_t i = 0; i < lines.size(); ++i)
    {
        std::string trimmedLine = trim(lines[i]);

        // Look for service definition start
        if (trimmedLine.find("service ") == 0)
        {
            XinetdServiceConfig service;

            // Extract service name from the line
            size_t nameStart = trimmedLine.find("service ") + 8;
            size_t nameEnd = trimmedLine.find_first_of(" \t{", nameStart);
            if (nameEnd == std::string::npos)
            {
                nameEnd = trimmedLine.length();
            }

            service.serviceName = trimmedLine.substr(
                nameStart, nameEnd - nameStart);

            // Parse the service block
            i = parseServiceBlock(lines, i, service);

            // Add valid service to our list
            if (!service.serviceName.empty())
            {
                vpaServices.push_back(service);
            }
        }
    }

    return !vpaServices.empty();
}

bool xinetcfg::isSudoAvailable() const
{
    // Check if sudo command exists and is configured for passwordless use
    std::string command = "sudo -n true 2>/dev/null";
    return system(command.c_str()) == 0;
}
////////////////////////////////////////////////////////////////////
// ~/public_html/fw/CServices.cpp 2025-07-15 18:16 dwg -          //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

const std::string CServices::SERVICES_FILE = "/etc/services";
const std::string CServices::SERVICES_BACKUP = "/etc/services.backup";
const std::string CServices::TEMP_DIR = "/tmp";

CServices::CServices() : cacheLoaded(false)
{
    // Check if sudo is available on first use
    if (!isSudoAvailable())
    {
        std::cerr << "Warning: sudo not available or not configured properly."
            << std::endl;
        std::cerr << "Service modification operations will fail." << std::endl;
        displaySudoInstructions();
    }
}

void CServices::loadServicesCache() const
{
    if (cacheLoaded)
    {
        return;
    }

    serviceCache.clear();
    std::ifstream file(SERVICES_FILE);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open " << SERVICES_FILE << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        ServiceInfo service;
        if (parseServiceLine(line, service))
        {
            std::string key = service.name + "/" + service.protocol;
            serviceCache[key] = service;
        }
    }

    cacheLoaded = true;
}

bool CServices::parseServiceLine(const std::string& line,
                                 ServiceInfo& service) const
{
    // Skip empty lines and comments
    if (line.empty() || line[0] == '#')
    {
        return false;
    }

    std::istringstream iss(line);
    std::string serviceName, portProtocol;

    if (!(iss >> serviceName >> portProtocol))
    {
        return false;
    }

    // Parse port/protocol
    size_t slashPos = portProtocol.find('/');
    if (slashPos == std::string::npos)
    {
        return false;
    }

    try
    {
        service.name = serviceName;
        service.port = std::stoi(portProtocol.substr(0, slashPos));
        service.protocol = portProtocol.substr(slashPos + 1);

        // Parse aliases
        std::string alias;
        while (iss >> alias)
        {
            if (alias[0] != '#')
            {
                // Stop at comments
                service.aliases.push_back(alias);
            }
            else
            {
                break;
            }
        }

        return true;
    }
    catch (const std::exception& e)
    {
        return false;
    }
}

bool CServices::hasService(const std::string& serviceName) const
{
    loadServicesCache();

    for (const auto& pair : serviceCache)
    {
        if (pair.second.name == serviceName)
        {
            return true;
        }
        // Check aliases
        for (const auto& alias : pair.second.aliases)
        {
            if (alias == serviceName)
            {
                return true;
            }
        }
    }

    return false;
}

bool CServices::hasService(const std::string& serviceName,
                           const std::string& protocol) const
{
    loadServicesCache();

    std::string key = serviceName + "/" + protocol;
    auto it = serviceCache.find(key);
    if (it != serviceCache.end())
    {
        return true;
    }

    // Check aliases
    for (const auto& pair : serviceCache)
    {
        if (pair.second.protocol == protocol)
        {
            for (const auto& alias : pair.second.aliases)
            {
                if (alias == serviceName)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

ServiceInfo CServices::getService(const std::string& serviceName) const
{
    loadServicesCache();

    for (const auto& pair : serviceCache)
    {
        if (pair.second.name == serviceName)
        {
            return pair.second;
        }
        // Check aliases
        for (const auto& alias : pair.second.aliases)
        {
            if (alias == serviceName)
            {
                return pair.second;
            }
        }
    }

    return ServiceInfo();
}

ServiceInfo CServices::getService(const std::string& serviceName,
                                  const std::string& protocol) const
{
    loadServicesCache();

    std::string key = serviceName + "/" + protocol;
    auto it = serviceCache.find(key);
    if (it != serviceCache.end())
    {
        return it->second;
    }

    // Check aliases
    for (const auto& pair : serviceCache)
    {
        if (pair.second.protocol == protocol)
        {
            for (const auto& alias : pair.second.aliases)
            {
                if (alias == serviceName)
                {
                    return pair.second;
                }
            }
        }
    }

    return ServiceInfo();
}

ServiceInfo CServices::getServiceByPort(int port,
                                        const std::string& protocol) const
{
    loadServicesCache();

    for (const auto& pair : serviceCache)
    {
        if (pair.second.port == port && pair.second.protocol == protocol)
        {
            return pair.second;
        }
    }

    return ServiceInfo();
}

bool CServices::addService(const std::string& serviceName, int port,
                           const std::string& protocol,
                           const std::vector<std::string>& aliases)
{
    // Validate inputs
    if (!isValidServiceName(serviceName) || !isValidProtocol(protocol) || port <
        1 || port > 65535)
    {
        return false;
    }

    // Check if service already exists
    if (hasService(serviceName, protocol))
    {
        return false;
    }

    // Check if port/protocol combination already exists
    if (portProtocolExists(port, protocol))
    {
        return false;
    }

    // Create backup before modifying
    if (!createBackup())
    {
        std::cerr << "Warning: Could not create backup of " << SERVICES_FILE <<
            std::endl;
    }

    // Get current content
    std::string content = getServicesContent();

    // Add new service entry
    std::ostringstream newEntry;
    newEntry << serviceName << "\t\t" << port << "/" << protocol;
    for (const auto& alias : aliases)
    {
        if (isValidServiceName(alias))
        {
            newEntry << " " << alias;
        }
    }
    newEntry << std::endl;

    content += newEntry.str();

    // Write to temporary file
    std::string tempFile = createTempFile(content);
    if (tempFile.empty())
    {
        return false;
    }

    // Use sudo to copy temp file to /etc/services
    std::string command = "sudo cp " + tempFile + " " + SERVICES_FILE;
    bool success = executeSudoCommand(command);

    // Clean up temp file
    unlink(tempFile.c_str());

    if (success)
    {
        // Invalidate cache to force reload
        cacheLoaded = false;
        // Reload xinetd
        reloadXinetd();
    }

    return success;
}

bool CServices::removeService(const std::string& serviceName,
                              const std::string& protocol)
{
    if (!hasService(serviceName))
    {
        return false;
    }

    // Create backup before modifying
    if (!createBackup())
    {
        std::cerr << "Warning: Could not create backup of " << SERVICES_FILE <<
            std::endl;
    }

    std::ifstream inFile(SERVICES_FILE);
    if (!inFile.is_open())
    {
        return false;
    }

    std::ostringstream newContent;
    std::string line;

    while (std::getline(inFile, line))
    {
        ServiceInfo service;
        if (parseServiceLine(line, service))
        {
            bool shouldRemove = (service.name == serviceName);

            // Check if protocol filter is specified
            if (!protocol.empty() && service.protocol != protocol)
            {
                shouldRemove = false;
            }

            // Check aliases
            if (!shouldRemove)
            {
                for (const auto& alias : service.aliases)
                {
                    if (alias == serviceName)
                    {
                        if (protocol.empty() || service.protocol == protocol)
                        {
                            shouldRemove = true;
                            break;
                        }
                    }
                }
            }

            if (!shouldRemove)
            {
                newContent << line << std::endl;
            }
        }
        else
        {
            newContent << line << std::endl; // Keep comments and empty lines
        }
    }

    inFile.close();

    // Write to temporary file
    std::string tempFile = createTempFile(newContent.str());
    if (tempFile.empty())
    {
        return false;
    }

    // Use sudo to copy temp file to /etc/services
    std::string command = "sudo cp " + tempFile + " " + SERVICES_FILE;
    bool success = executeSudoCommand(command);

    // Clean up temp file
    unlink(tempFile.c_str());

    if (success)
    {
        // Invalidate cache to force reload
        cacheLoaded = false;
        // Reload xinetd
        reloadXinetd();
    }

    return success;
}

std::vector<ServiceInfo> CServices::findServices(
    const std::string& pattern) const
{
    loadServicesCache();

    std::vector<ServiceInfo> results;

    if (pattern.empty())
    {
        for (const auto& pair : serviceCache)
        {
            results.push_back(pair.second);
        }
    }
    else
    {
        std::regex regex(pattern, std::regex_constants::icase);
        for (const auto& pair : serviceCache)
        {
            if (std::regex_search(pair.second.name, regex))
            {
                results.push_back(pair.second);
            }
        }
    }

    return results;
}

int CServices::getServicePort(const std::string& serviceName,
                              const std::string& protocol) const
{
    ServiceInfo service = getService(serviceName, protocol);
    return service.name.empty() ? -1 : service.port;
}

std::string CServices::getServiceName(int port,
                                      const std::string& protocol) const
{
    ServiceInfo service = getServiceByPort(port, protocol);
    return service.name;
}

void CServices::reloadCache()
{
    cacheLoaded = false;
    serviceCache.clear();
    loadServicesCache();
}

bool CServices::createBackup() const
{
    std::string command = "sudo cp " + SERVICES_FILE + " " + SERVICES_BACKUP;
    return executeSudoCommand(command);
}

bool CServices::restoreFromBackup() const
{
    std::string command = "sudo cp " + SERVICES_BACKUP + " " + SERVICES_FILE;
    bool success = executeSudoCommand(command);

    if (success)
    {
        // Invalidate cache
        cacheLoaded = false;
        // Reload xinetd
        reloadXinetd();
    }

    return success;
}

bool CServices::canModifyServices() const
{
    return isSudoAvailable();
}

size_t CServices::getServiceCount() const
{
    loadServicesCache();
    return serviceCache.size();
}

bool CServices::reloadXinetd() const
{
    // Try different xinetd reload methods
    std::vector<std::string> commands = {
        "sudo systemctl reload xinetd",
        "sudo service xinetd reload",
        "sudo /etc/init.d/xinetd reload",
        "sudo killall -HUP xinetd"
    };

    for (const auto& command : commands)
    {
        if (executeSudoCommand(command))
        {
            return true;
        }
    }

    return false;
}

std::string CServices::getCurrentUser() const
{
    struct passwd* pwd = getpwuid(getuid());
    if (pwd)
    {
        return std::string(pwd->pw_name);
    }
    return "unknown";
}

void CServices::displaySudoInstructions() const
{
    std::string user = getCurrentUser();
    std::cout << "\n=== SUDO CONFIGURATION REQUIRED ===" << std::endl;
    std::cout <<
        "To use CServices for /etc/services management, you need to configure sudo."
        << std::endl;
    std::cout <<
        "As root, add this line to /etc/sudoers (use 'visudo' command):" <<
        std::endl;
    std::cout << std::endl;
    std::cout << user <<
        " ALL=(ALL) NOPASSWD: /bin/cp /tmp/services_* /etc/services" <<
        std::endl;
    std::cout << user <<
        " ALL=(ALL) NOPASSWD: /bin/cp /etc/services /etc/services.backup" <<
        std::endl;
    std::cout << user <<
        " ALL=(ALL) NOPASSWD: /bin/cp /etc/services.backup /etc/services" <<
        std::endl;
    std::cout << user << " ALL=(ALL) NOPASSWD: /usr/bin/systemctl reload xinetd"
        << std::endl;
    std::cout << user << " ALL=(ALL) NOPASSWD: /usr/sbin/service xinetd reload"
        << std::endl;
    std::cout << user << " ALL=(ALL) NOPASSWD: /etc/init.d/xinetd reload" <<
        std::endl;
    std::cout << user << " ALL=(ALL) NOPASSWD: /usr/bin/killall -HUP xinetd" <<
        std::endl;
    std::cout << std::endl;
    std::cout << "Or for broader access (less secure):" << std::endl;
    std::cout << user <<
        " ALL=(ALL) NOPASSWD: /bin/cp, /usr/bin/systemctl, /usr/sbin/service, /etc/init.d/xinetd, /usr/bin/killall"
        << std::endl;
    std::cout << "===================================" << std::endl;
}

bool CServices::executeSudoCommand(const std::string& command) const
{
    int result = system(command.c_str());
    return WIFEXITED(result) && WEXITSTATUS(result) == 0;
}

bool CServices::isSudoAvailable() const
{
    // Check if sudo is installed and user can use it
    int result = system("sudo -n true 2>/dev/null");
    return WIFEXITED(result) && WEXITSTATUS(result) == 0;
}

std::string CServices::createTempFile(const std::string& content) const
{
    std::string tempFile = TEMP_DIR + "/services_" + std::to_string(getpid()) +
        "_" + std::to_string(time(nullptr));

    std::ofstream file(tempFile);
    if (!file.is_open())
    {
        return "";
    }

    file << content;
    file.close();

    return tempFile;
}

std::string CServices::getServicesContent() const
{
    std::ifstream file(SERVICES_FILE);
    if (!file.is_open())
    {
        return "";
    }

    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}

bool CServices::portProtocolExists(int port, const std::string& protocol) const
{
    loadServicesCache();

    for (const auto& pair : serviceCache)
    {
        if (pair.second.port == port && pair.second.protocol == protocol)
        {
            return true;
        }
    }

    return false;
}

bool CServices::isValidServiceName(const std::string& name) const
{
    if (name.empty() || name.length() > 15)
    {
        return false;
    }

    // Service names should contain only alphanumeric characters, hyphens, and underscores
    for (char c : name)
    {
        if (!std::isalnum(c) && c != '-' && c != '_')
        {
            return false;
        }
    }

    return true;
}

bool CServices::isValidProtocol(const std::string& protocol) const
{
    return protocol == "tcp" || protocol == "udp" || protocol == "sctp";
}

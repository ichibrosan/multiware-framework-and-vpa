#ifndef CSERVICES_H
#define CSERVICES_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>

/**
 * @brief Service information structure
 */
struct ServiceInfo {
    std::string name;
    int port;
    std::string protocol;
    std::vector<std::string> aliases;
    
    ServiceInfo() : port(0) {}
    ServiceInfo(const std::string& n, int p, const std::string& proto) 
        : name(n), port(p), protocol(proto) {}
};

/**
 * @brief System services management class for /etc/services
 * 
 * This class provides functionality to check for the existence of named services
 * in /etc/services and add new named services using sudo for privilege escalation.
 */
class CServices {
private:
    static const std::string SERVICES_FILE;
    static const std::string SERVICES_BACKUP;
    static const std::string TEMP_DIR;
    
    // Cache for loaded services
    mutable std::unordered_map<std::string, ServiceInfo> serviceCache;
    mutable bool cacheLoaded;
    
    /**
     * @brief Load services from /etc/services into cache
     */
    void loadServicesCache() const;
    
    /**
     * @brief Parse a service line from /etc/services
     * @param line The line to parse
     * @param service Reference to ServiceInfo to populate
     * @return true if parsing was successful
     */
    bool parseServiceLine(const std::string& line, ServiceInfo& service) const;
    
    /**
     * @brief Check if a port/protocol combination already exists
     * @param port The port number
     * @param protocol The protocol (tcp/udp)
     * @return true if the combination exists
     */
    bool portProtocolExists(int port, const std::string& protocol) const;
    
    /**
     * @brief Validate service name format
     * @param name The service name to validate
     * @return true if the name is valid
     */
    bool isValidServiceName(const std::string& name) const;
    
    /**
     * @brief Validate protocol name
     * @param protocol The protocol to validate
     * @return true if the protocol is valid
     */
    bool isValidProtocol(const std::string& protocol) const;
    
    /**
     * @brief Execute a command with sudo
     * @param command The command to execute
     * @return true if successful
     */
    bool executeSudoCommand(const std::string& command) const;
    
    /**
     * @brief Check if sudo is available and configured
     * @return true if sudo can be used
     */
    bool isSudoAvailable() const;
    
    /**
     * @brief Create a temporary file with new services content
     * @param content The content to write
     * @return Path to temporary file, empty if failed
     */
    std::string createTempFile(const std::string& content) const;
    
    /**
     * @brief Get current /etc/services content
     * @return Content of /etc/services
     */
    std::string getServicesContent() const;

public:
    /**
     * @brief Default constructor
     */
    CServices();
    
    /**
     * @brief Destructor
     */
    ~CServices() = default;
    
    /**
     * @brief Copy constructor (deleted to prevent copying)
     */
    CServices(const CServices&) = delete;
    
    /**
     * @brief Assignment operator (deleted to prevent copying)
     */
    CServices& operator=(const CServices&) = delete;
    
    /**
     * @brief Check if a service with the given name exists in /etc/services
     * @param serviceName The name of the service to check
     * @return true if the service exists, false otherwise
     */
    bool hasService(const std::string& serviceName) const;
    
    /**
     * @brief Check if a service exists for a specific protocol
     * @param serviceName The name of the service
     * @param protocol The protocol (tcp/udp)
     * @return true if the service exists for the specified protocol
     */
    bool hasService(const std::string& serviceName, const std::string& protocol) const;
    
    /**
     * @brief Get service information by name
     * @param serviceName The name of the service
     * @return ServiceInfo structure, empty if not found
     */
    ServiceInfo getService(const std::string& serviceName) const;
    
    /**
     * @brief Get service information by name and protocol
     * @param serviceName The name of the service
     * @param protocol The protocol (tcp/udp)
     * @return ServiceInfo structure, empty if not found
     */
    ServiceInfo getService(const std::string& serviceName, const std::string& protocol) const;
    
    /**
     * @brief Get service information by port and protocol
     * @param port The port number
     * @param protocol The protocol (tcp/udp)
     * @return ServiceInfo structure, empty if not found
     */
    ServiceInfo getServiceByPort(int port, const std::string& protocol) const;
    
    /**
     * @brief Add a new service to /etc/services using sudo
     * @param serviceName The name of the service
     * @param port The port number
     * @param protocol The protocol (tcp/udp)
     * @param aliases Optional aliases for the service
     * @return true if the service was added successfully
     */
    bool addService(const std::string& serviceName, int port, const std::string& protocol, 
                   const std::vector<std::string>& aliases = {});
    
    /**
     * @brief Remove a service from /etc/services using sudo
     * @param serviceName The name of the service to remove
     * @param protocol Optional protocol filter
     * @return true if the service was removed successfully
     */
    bool removeService(const std::string& serviceName, const std::string& protocol = "");
    
    /**
     * @brief Get all services matching a pattern
     * @param pattern Pattern to match (empty for all services)
     * @return Vector of ServiceInfo structures
     */
    std::vector<ServiceInfo> findServices(const std::string& pattern = "") const;
    
    /**
     * @brief Get port number for a service
     * @param serviceName The name of the service
     * @param protocol The protocol (tcp/udp)
     * @return Port number, or -1 if not found
     */
    int getServicePort(const std::string& serviceName, const std::string& protocol) const;
    
    /**
     * @brief Get service name for a port
     * @param port The port number
     * @param protocol The protocol (tcp/udp)
     * @return Service name, or empty string if not found
     */
    std::string getServiceName(int port, const std::string& protocol) const;
    
    /**
     * @brief Reload services cache from /etc/services
     */
    void reloadCache();
    
    /**
     * @brief Create a backup of /etc/services using sudo
     * @return true if backup was created successfully
     */
    bool createBackup() const;
    
    /**
     * @brief Restore /etc/services from backup using sudo
     * @return true if restore was successful
     */
    bool restoreFromBackup() const;
    
    /**
     * @brief Check if sudo is properly configured for services management
     * @return true if sudo can be used for /etc/services operations
     */
    bool canModifyServices() const;
    
    /**
     * @brief Get the number of services in the system
     * @return Number of services
     */
    size_t getServiceCount() const;
    
    /**
     * @brief Reload xinetd after services file changes
     * @return true if xinetd was reloaded successfully
     */
    bool reloadXinetd() const;
    
    /**
     * @brief Get current user name
     * @return Current user name
     */
    std::string getCurrentUser() const;
    
    /**
     * @brief Display sudo configuration instructions
     */
    void displaySudoInstructions() const;
};

#endif // CSERVICES_H
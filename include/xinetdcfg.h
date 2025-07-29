////////////////////////////////////////////////////////////////////
// ~/public_html/fw/xinetdcfg.h 2025-07-16 08:08 dwg -            //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>

/**
 * @brief Xinetd service configuration structure
 */
struct XinetdServiceConfig
{
    std::string serviceName;
    std::string port;
    std::string disable;
    std::string id; // Added to match your config
    std::string socketType;
    std::string protocol;
    std::string user;
    std::string wait;
    std::string server;
    std::string serverArgs; // Optional - not used in your config

    // Optional fields not used in your config but available
    std::string type;
    std::string flags;
    std::string group;
    std::string logOnSuccess;
    std::string logOnFailure;
    std::string nice;
    std::string instancesMax;
    std::string instancesPerSource;
    std::string accessTimes;

    // Additional fields that might be used in parsing
    std::string bindAddress;
    std::string redirectAddress;
    std::string banner;
    std::string bannerSuccess;
    std::string bannerFail;
    std::string cps;
    std::string maxLoad;
    std::string groups;

    XinetdServiceConfig()
    {
        disable = "no";
        socketType = "stream";
        protocol = "tcp";
        user = "1000";
        wait = "no";
    }
};

/**
 * @brief Xinetd configuration manager for VPA services
 *
 * This class manages the /etc/xinetd.d/vpa configuration file containing
 * seven different VPA services with different configurations.
 */
class xinetcfg
{
private:
    static const std::string XINETD_DIR;
    static const std::string VPA_CONFIG_FILE;
    static const std::string VPA_CONFIG_BACKUP;
    static const std::string TEMP_DIR;

    // Seven VPA services configuration
    std::vector<XinetdServiceConfig> vpaServices;

    /**
     * @brief Initialize default VPA services configuration
     */
    void initializeDefaultServices();

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
     * @brief Create a temporary file with xinetd configuration content
     * @param content The content to write
     * @return Path to temporary file, empty if failed
     */
    std::string createTempFile(const std::string& content) const;

    /**
     * @brief Parse existing xinetd configuration file
     * @return true if parsing was successful
     */
    bool parseExistingConfig();

    /**
     * @brief Parse a single service block from configuration
     * @param lines Vector of configuration lines
     * @param startIndex Starting index of service block
     * @param service Reference to service config to populate
     * @return Next index after service block
     */
    size_t parseServiceBlock(const std::vector<std::string>& lines,
                             size_t startIndex,
                             XinetdServiceConfig& service) const;

    /**
     * @brief Validate service configuration
     * @param service The service configuration to validate
     * @return true if valid
     */
    bool validateServiceConfig(const XinetdServiceConfig& service) const;

    /**
     * @brief Generate xinetd configuration content
     * @return Generated configuration content
     */
    std::string generateConfigContent() const;

    /**
     * @brief Format a single service configuration block
     * @param service The service configuration
     * @return Formatted service block
     */
    std::string formatServiceBlock(const XinetdServiceConfig& service) const;

    /**
     * @brief Trim whitespace from string
     * @param str String to trim
     * @return Trimmed string
     */
    std::string trim(const std::string& str) const;

    /**
     * @brief Check if port is valid and available
     * @param port Port number to check
     * @return true if valid
     */
    bool isValidPort(const std::string& port) const;

    /**
     * @brief Get current date time string
     * @return Current date time formatted string
     */
    std::string getCurrentDateTimeString() const;

public:
    /**
     * @brief Default constructor
     */
    xinetcfg();

    /**
     * @brief Destructor
     */
    ~xinetcfg() = default;

    /**
     * @brief Copy constructor (deleted to prevent copying)
     */
    xinetcfg(const xinetcfg&) = delete;

    /**
     * @brief Assignment operator (deleted to prevent copying)
     */
    xinetcfg& operator=(const xinetcfg&) = delete;

    /**
     * @brief Load existing configuration from /etc/xinetd.d/vpa
     * @return true if successful
     */
    bool loadConfig();

    /**
     * @brief Save configuration to /etc/xinetd.d/vpa
     * @return true if successful
     */
    bool saveConfig();

    /**
     * @brief Get service configuration by name
     * @param serviceName Name of the service
     * @return Service configuration, empty if not found
     */
    XinetdServiceConfig getService(const std::string& serviceName) const;

    /**
     * @brief Get all service configurations
     * @return Vector of all service configurations
     */
    std::vector<XinetdServiceConfig> getAllServices() const;

    /**
     * @brief Update service configuration
     * @param serviceName Name of the service to update
     * @param config New configuration
     * @return true if successful
     */
    bool updateService(const std::string& serviceName,
                       const XinetdServiceConfig& config);

    /**
     * @brief Add a new service configuration
     * @param config Service configuration to add
     * @return true if successful
     */
    bool addService(const XinetdServiceConfig& config);

    /**
     * @brief Remove a service configuration
     * @param serviceName Name of the service to remove
     * @return true if successful
     */
    bool removeService(const std::string& serviceName);

    /**
     * @brief Enable a service
     * @param serviceName Name of the service to enable
     * @return true if successful
     */
    bool enableService(const std::string& serviceName);

    /**
     * @brief Disable a service
     * @param serviceName Name of the service to disable
     * @return true if successful
     */
    bool disableService(const std::string& serviceName);

    /**
     * @brief Check if a service is enabled
     * @param serviceName Name of the service to check
     * @return true if enabled
     */
    bool isServiceEnabled(const std::string& serviceName) const;

    /**
     * @brief Get number of configured services
     * @return Number of services
     */
    size_t getServiceCount() const;

    /**
     * @brief Create backup of xinetd configuration
     * @return true if successful
     */
    bool createBackup() const;

    /**
     * @brief Restore xinetd configuration from backup
     * @return true if successful
     */
    bool restoreFromBackup() const;

    /**
     * @brief Reload xinetd daemon
     * @return true if successful
     */
    bool reloadXinetd() const;

    /**
     * @brief Restart xinetd daemon
     * @return true if successful
     */
    bool restartXinetd() const;

    /**
     * @brief Check xinetd daemon status
     * @return true if running
     */
    bool isXinetdRunning() const;

    /**
     * @brief Validate entire configuration
     * @return true if all services are valid
     */
    bool validateConfig() const;

    /**
     * @brief Get current user name
     * @return Current user name
     */
    std::string getCurrentUser() const;

    /**
     * @brief Display sudo configuration instructions
     */
    void displaySudoInstructions() const;

    /**
     * @brief Check if xinetd operations can be performed
     * @return true if sudo is properly configured
     */
    bool canModifyXinetd() const;

    /**
     * @brief Export configuration to file
     * @param filename Path to export file
     * @return true if successful
     */
    bool exportConfig(const std::string& filename) const;

    /**
     * @brief Import configuration from file
     * @param filename Path to import file
     * @return true if successful
     */
    bool importConfig(const std::string& filename);

    /**
     * @brief Reset to default VPA services configuration
     * @return true if successful
     */
    bool resetToDefaults();

    /**
     * @brief Get service by port number
     * @param port Port number to search for
     * @return Service configuration, empty if not found
     */
    XinetdServiceConfig getServiceByPort(const std::string& port) const;

    /**
     * @brief List all ports used by services
     * @return Vector of port numbers
     */
    std::vector<std::string> getUsedPorts() const;

    /**
     * @brief Generate service status report
     * @return Status report string
     */
    std::string generateStatusReport() const;

    /**
     * @brief Generate VPA xinetd configuration
     * @return Generated VPA configuration content
     */
    std::string generateVpaXinetdConfig();

    /**
     * @brief Display VPA service status
     */
    void displayVpaServiceStatus();
};

///////////////////////
// eof - xinetdcfg.h //
///////////////////////

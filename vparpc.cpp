//////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/vparpc.cpp 2025/01/17 - dwg //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.       //
//////////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

#include "vparpc.h"

#include <netdb.h>
#include <arpa/inet.h>

#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <cctype>

/**
 * Default constructor for the vparpc class.
 *
 * Initializes an instance of the vparpc class. This constructor
 * does not perform any specific initialization logic; it simply
 * creates an empty object of the vparpc class.
 */
vparpc::vparpc() {

}

/**
 * Collects endpoint information for subsequent call to UDP layer.
 *
 * This function displays the source and destination address, service information,
 * and destination port information in the console. It uses `svc2port()` to retrieve
 * the destination port corresponding to the provided destination service.
 *
 * @param ssVpaSrcAddr The source address as a string.
 * @param ssVpaSrcSvc The name of the source service as a string.
 * @param ssVpaDstAddr The destination address as a string.
 * @param ssVpaDstSvc The name of the destination service as a string.
 * @return Always returns `EXIT_SUCCESS` to indicate successful execution.
 */
int vparpc::vparpc_open(std::string ssVpaSrcAddr, std::string ssVpaSrcSvc,
                        std::string ssVpaDstAddr, std::string ssVpaDstSvc) {
    std::cout << "ssVpaSrcAddr is " << ssVpaSrcAddr << std::endl;
    std::cout << "ssVpaSrcSvc is " << ssVpaSrcSvc << std::endl;
    std::cout << "ssVpaDstAddr is " << ssVpaDstAddr << std::endl;
    std::cout << "ssVpaDstSvc is " << ssVpaDstSvc << std::endl;
    std::cout << "ssVpaDstPort is " << svc2port(ssVpaDstSvc) << std::endl;

    return EXIT_SUCCESS;
}

/**
 * @brief Resolves a service name to its corresponding port number.
 *
 * This function attempts to find the port number associated with a given
 * service name. It first checks for the service in the TCP protocol context.
 * If a match is found, the corresponding port number is returned, converted
 * from network byte order to host byte order. If no match is found for the
 * service in the TCP protocol, the function then checks within the UDP
 * protocol context and performs a similar conversion if a match is found.
 * If the service name is not found in either protocol context, the function
 * returns -1.
 *
 * @param ssSvcName Service name as a string.
 * @return Integer representing the port number associated with the service
 *         in host byte order if found, or -1 if the service is not found in
 *         both TCP and UDP protocols.
 */
int vparpc::svc2port(std::string ssSvcName) {
    struct servent *serviceEntry;
    
    // Look up the service by name for TCP protocol
    serviceEntry = getservbyname(ssSvcName.c_str(), "tcp");
    
    if (serviceEntry != nullptr) {
        // Convert network byte order to host byte order
        return ntohs(serviceEntry->s_port);
    }
    
    // If TCP lookup failed, try UDP
    serviceEntry = getservbyname(ssSvcName.c_str(), "udp");
    
    if (serviceEntry != nullptr) {
        // Convert network byte order to host byte order
        return ntohs(serviceEntry->s_port);
    }
    
    // Service not found
    return -1;
}

/**
 * Resolves a given hostname to its IPv4 address.
 *
 * This function first checks if the input string is already a valid IPv4
 * address. If it is, the input is returned directly. Otherwise, it searches
 * for the hostname in common system-specific hosts file locations such as
 * `/etc/hosts` (Linux/Unix), `C:\Windows\System32\drivers\etc\hosts`
 * (Windows), and `/System/Library/etc/hosts` (alternative macOS path).
 *
 * The function handles case-insensitive hostname matching and skips comments
 * or invalid lines in the hosts file. If the hostname is found, its
 * corresponding IPv4 address is returned. If the hostname is not found or
 * the function fails to open the hosts file, an empty string is returned.
 *
 * @param hostname The hostname to resolve.
 * @return A string containing the resolved IPv4 address if successful,
 *         or an empty string if the hostname could not be resolved or
 *         the hosts file could not be accessed.
 */
std::string vparpc::host2ipv4addr(const std::string& hostname) {
    // First check if the input is already an IPv4 address
    std::regex ipv4_regex(R"(^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)");
    if (std::regex_match(hostname, ipv4_regex)) {
        return hostname; // Already an IP address
    }
    
    // Try to open the hosts file
    std::ifstream hosts_file;
    
    // Common hosts file locations
    const std::vector<std::string> hosts_paths = {
        "/etc/hosts",           // Linux/Unix
        "C:\\Windows\\System32\\drivers\\etc\\hosts",  // Windows
        "/System/Library/etc/hosts"  // macOS (alternative path)
    };
    
    for (const auto& path : hosts_paths) {
        hosts_file.open(path);
        if (hosts_file.is_open()) {
            break;
        }
    }
    
    if (!hosts_file.is_open()) {
        return ""; // Could not open hosts file
    }
    
    std::string line;
    std::string target_hostname = hostname;
    
    // Convert target hostname to lowercase for case-insensitive comparison
    std::transform(target_hostname.begin(), target_hostname.end(), 
                   target_hostname.begin(), ::tolower);
    
    while (std::getline(hosts_file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Remove leading/trailing whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        
        if (line.empty()) {
            continue;
        }
        
        std::istringstream iss(line);
        std::string ip_addr;
        std::string host_entry;
        
        // Get the IP address (first token)
        if (!(iss >> ip_addr)) {
            continue;
        }
        
        // Validate that it's an IPv4 address
        if (!std::regex_match(ip_addr, ipv4_regex)) {
            continue; // Skip IPv6 or invalid entries
        }
        
        // Check all hostnames on this line
        while (iss >> host_entry) {
            // Convert to lowercase for comparison
            std::transform(host_entry.begin(), host_entry.end(), 
                          host_entry.begin(), ::tolower);
            
            if (host_entry == target_hostname) {
                hosts_file.close();
                return ip_addr;
            }
        }
    }
    
    hosts_file.close();
    return ""; // Hostname not found
}
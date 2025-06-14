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
 * @brief Default constructor for vparpc class
 * 
 * Initializes a new instance of the vparpc (Visual Panel Application Remote Procedure Call) class.
 * This class provides TCP client-server communication functionality with a visual interface
 * for monitoring connection status and data transfer.
 */
vparpc::vparpc() {
}

/*******************************************************
      ####   ######  #####   #    #  ######  #####
     #       #       #    #  #    #  #       #    #
      ####   #####   #    #  #    #  #####   #    #
          #  #       #####   #    #  #       #####
     #    #  #       #   #    #  #   #       #   #
      ####   ######  #    #    ##    ######  #    #
********************************************************/

/**
 * @brief Starts a TCP server that listens for incoming client connections
 * 
 * Creates a TCP server socket that binds to the specified service port and enters
 * an infinite loop to handle client connections. Each client connection is processed
 * synchronously, receiving data and sending appropriate responses based on the
 * received commands.
 * 
 * Supported commands:
 * - "/GET version": Returns the application version string (RSTRING)
 * - "/GET szRpcUuid": Returns the RPC UUID from shared memory
 * 
 * @param ssService The service name to resolve to a port number using system service lookup
 * 
 * @note This function runs indefinitely and will not return under normal circumstances
 * @note Each client connection is handled sequentially (not multi-threaded)
 * @note Creates a visual window to display server status and client interactions
 * @note Memory allocated for window objects is properly cleaned up after each client
 * 
 * @warning The server socket cleanup code at the end is unreachable due to infinite loop
 * @warning No authentication or authorization is implemented
 * @warning Buffer overflow protection relies on BUFSIZ-1 limit
 */
void vparpc::server(std::string ssService) {
    std::string response;

    // Create visual window for server status display
    auto * pWin = new window();
    gpSemiGr->cosmetics( SRUL,  SRUR,  SRLL,
                    SRLR,SVSR,SVSL,
                    SH,  SV);

    // Resolve service name to port number
    int iPort = svc2port(ssService);

    // Set window title with server information
    std::string ssSine = "vparpc::server() - Starting TCP server on port " + std::to_string(iPort);
    pWin->set_title(ssSine);
    
    // Socket file descriptors
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFSIZ];  // Buffer for receiving client data (typically 8192 bytes)
    
    // Create TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        pWin->add_row("  Error: socket creation failed");
        pWin->render();
        return;
    }
    pWin->add_row("  Server socket created");

    // Set socket options to allow address reuse (prevents "Address already in use" errors)
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        pWin->add_row("  Error: setsockopt failed");
        pWin->render();
        close(server_fd);
        return;
    }
    pWin->add_row("  Socket options set");

    // Configure server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Listen on all available interfaces
    server_addr.sin_port = htons(iPort);       // Convert port to network byte order
    
    // Bind socket to the specified address and port
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        pWin->add_row("  Error: bind failed");
        pWin->render();
        close(server_fd);
        return;
    }
    pWin->add_row("  Server bound to port "+ std::to_string(iPort) );

    // Start listening for incoming connections (queue up to 5 pending connections)
    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        close(server_fd);
        return;
    }
    
    pWin->add_row("Server listening on port " + std::to_string(iPort));
    
    // Main server loop - handles clients sequentially
    while (true) {
        // Create new window for each client connection
        auto * pWin = new window();
        pWin->set_title("  Main server loop");

        // Accept incoming client connection (blocking call)
        if ((client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len)) < 0) {
            pWin->add_row("  Error: accept failed");
            continue;  // Continue to next iteration on error
        }
        
        // Extract client address and port information
        std::string ssClientAddr = inet_ntoa(client_addr.sin_addr);
        std::string ssClientPort = std::to_string(ntohs(client_addr.sin_port));
        std::string ssClient = ssClientAddr + ":" + ssClientPort;
        pWin->add_row("  Client connected from " + ssClient);

        // Clear receive buffer
        memset(buffer, 0, BUFSIZ);
        
        // Receive data from client
        ssize_t bytes_received = recv(client_fd, buffer, BUFSIZ - 1, 0);
        if (bytes_received < 0) {
            pWin->add_row("  Error: recv failed");
        } else if (bytes_received == 0) {
            pWin->add_row("  Error: Client disconnected");
        } else {
            buffer[bytes_received] = '\0';  // Null-terminate the received data
            pWin->add_row("  Received "+std::to_string(bytes_received)+" bytes: "+buffer);

            // Process client commands and generate responses
            if (0 == strcmp("/GET version", buffer)) {
                response = RSTRING;  // Application version string
            }

            if (0 == strcmp("/GET szRpcUuid", buffer)) {
                response = gpSh->m_pShMemng->szRpcUuid;  // RPC UUID from shared memory
            }

            // Send response back to client
            ssize_t bytes_sent = send(client_fd, response.c_str(), response.length(), 0);
            pWin->add_row("  Sent     "+std::to_string(bytes_sent)+" bytes: "+response.c_str());

            if (bytes_sent < 0) {
                pWin->add_row("  Error: send failed");
            } else {
                pWin->add_row("  Response sent to client");
            }
        }
        
        // Close client connection
        close(client_fd);
        pWin->add_row("  Client connection closed");
        pWin->render();
        delete pWin;  // Clean up window memory
    }
    
    // Close server socket (unreachable code due to infinite loop above)
    close(server_fd);
}

/*************************************************
      ####   #       #  ######  #    #  #####
     #    #  #       #  #       ##   #    #
     #       #       #  #####   # #  #    #
     #       #       #  #       #  # #    #
     #    #  #       #  #       #   ##    #
      ####   ######  #  ######  #    #    #
 *************************************************/

/**
 * @brief Establishes a TCP client connection to a remote server and sends data
 * 
 * Creates a TCP client socket, resolves the target hostname, connects to the
 * specified service port, sends a data packet, receives the response, and
 * displays all communication details in a visual window.
 * 
 * @param ssHostName The hostname or IP address of the target server
 * @param ssServiceName The service name to resolve to a port number
 * @param packet The data packet to send to the server
 * 
 * @note Creates a visual window to display connection progress and data transfer
 * @note Uses gethostbyname() for hostname resolution (IPv4 only)
 * @note Synchronous operation - blocks until completion or error
 * @note Automatically closes connection after single request-response cycle
 * 
 * @warning Uses deprecated gethostbyname() function (not thread-safe)
 * @warning No timeout mechanism implemented for network operations
 * @warning Response buffer limited to BUFSIZ (typically 8192 bytes)
 */
void vparpc::client(std::string ssHostName, std::string ssServiceName, const std::string& packet) {

    // Create visual window for client status display
    auto * pWin = new window();
    gpSemiGr->cosmetics( SRUL,  SRUR,  SRLL,
                        SRLR,SVSR,SVSL,
                        SH,  SV);
    
    // Build copyright string
    std::string ssCopr = "Copyright ";
    ssCopr.append("(c)");
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");
    
    // Set window title with connection parameters
    pWin->set_title("vparpc::client(" + ssHostName + "," + ssServiceName + ")");

    int client_fd;
    struct sockaddr_in server_addr;
    struct hostent *host_entry;
    char response_buffer[BUFSIZ];       // Response buffer (BUFSIZ = 8192)
    
    // Resolve hostname to IP address using system DNS lookup
    host_entry = gethostbyname(ssHostName.c_str());
    if (host_entry == nullptr) {
        pWin->add_row(" Error: Could not resolve hostname "+ssHostName);
        pWin->render();
        return;
    }
    
    pWin->add_row("  Host resolved: "+ssHostName);

    // Create TCP client socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        pWin->add_row(" Error: socket creation failed");
        pWin->render();
        return;
    }
    pWin->add_row("  Client socket created");

    // Configure server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(svc2port(ssServiceName));  // Convert service to port
    server_addr.sin_addr.s_addr = *((unsigned long *) host_entry->h_addr);  // Set IP address
    
    pWin->add_row("  Connecting to port "+std::to_string(svc2port(ssServiceName)));

    // Establish connection to server
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        pWin->add_row(" Error: connection failed");
        close(client_fd);
        return;
    }
    pWin->add_row("  Connected to server");
    
    // Send data packet to server
    ssize_t bytes_sent = send(client_fd, packet.c_str(), packet.length(), 0);
    if (bytes_sent < 0) {
        pWin->add_row(" Error: send failed");
        close(client_fd);
        pWin->render();
        return;
    }
    pWin->add_row("  Sent     "+std::to_string(bytes_sent)+" bytes: "+packet);

    // Clear response buffer
    memset(response_buffer, 0, BUFSIZ);
    
    // Receive response from server
    ssize_t bytes_received = recv(client_fd, response_buffer, BUFSIZ - 1, 0);
    if (bytes_received < 0) {
        perror("recv failed");
    } else if (bytes_received == 0) {
        std::cout << "  Server closed connection" << std::endl;
    } else {
        response_buffer[bytes_received] = '\0';  // Null-terminate response
        pWin->add_row("  Received "+std::to_string(bytes_received)+" bytes: "+response_buffer);
    }
    
    // Close client connection
    close(client_fd);
    pWin->add_row("  Client connection closed");
    pWin->render();
}

/**
 * @brief Converts a service name to its corresponding port number
 * 
 * Looks up the port number associated with a given service name using the
 * system's service database (/etc/services on Unix-like systems). First
 * attempts TCP lookup, then falls back to UDP if TCP lookup fails.
 * 
 * @param ssSvcName The service name to look up (e.g., "http", "ssh", "ftp")
 * 
 * @return int The port number in host byte order, or -1 if service not found
 * 
 * @note Uses getservbyname() which consults /etc/services and other system databases
 * @note Tries TCP protocol first, then UDP as fallback
 * @note Returns port in host byte order (ready for use with htons())
 * 
 * @example
 * int port = svc2port("http");     // Returns 80
 * int port = svc2port("ssh");      // Returns 22
 * int port = svc2port("unknown");  // Returns -1
 */
int vparpc::svc2port(std::string ssSvcName) {

    struct servent *serviceEntry;
    
    // First try TCP protocol lookup
    serviceEntry = getservbyname(ssSvcName.c_str(), "tcp");

    if (serviceEntry != nullptr) {
        // Convert network byte order to host byte order
        return ntohs(serviceEntry->s_port);
    }

    // If TCP lookup failed, try UDP protocol
    serviceEntry = getservbyname(ssSvcName.c_str(), "udp");

    if (serviceEntry != nullptr) {
        // Convert network byte order to host byte order
        return ntohs(serviceEntry->s_port);
    }

    // Service not found in either TCP or UDP
    return -1;
}

/**
 * @brief Resolves a hostname to its IPv4 address using the system hosts file
 * 
 * This function performs hostname-to-IP resolution by parsing the local hosts file
 * rather than using DNS. It supports multiple operating systems by checking
 * common hosts file locations. If the input is already a valid IPv4 address,
 * it returns the input unchanged.
 * 
 * @param hostname The hostname to resolve or IPv4 address to validate
 * 
 * @return std::string The corresponding IPv4 address, or empty string if:
 *         - Hostname not found in hosts file
 *         - Hosts file cannot be opened
 *         - Invalid input format
 * 
 * @note Performs case-insensitive hostname matching
 * @note Only supports IPv4 addresses (skips IPv6 entries)
 * @note Checks hosts files in this order:
 *       1. /etc/hosts (Linux/Unix)
 *       2. C:\Windows\System32\drivers\etc\hosts (Windows)
 *       3. /System/Library/etc/hosts (macOS alternative)
 * @note Uses regex validation for IPv4 address format
 * 
 * @example
 * std::string ip = host2ipv4addr("localhost");     // May return "127.0.0.1"
 * std::string ip = host2ipv4addr("192.168.1.1");  // Returns "192.168.1.1"
 * std::string ip = host2ipv4addr("unknown");       // Returns ""
 * 
 * @warning Does not perform DNS lookups - only consults local hosts file
 * @warning IPv6 addresses in hosts file are ignored
 */
std::string vparpc::host2ipv4addr(const std::string& hostname) {

    // IPv4 address validation regex pattern
    // Matches: 0.0.0.0 to 255.255.255.255
    std::regex ipv4_regex(R"(^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)");
    
    // Check if input is already a valid IPv4 address
    if (std::regex_match(hostname, ipv4_regex)) {
        return hostname; // Already an IP address, return as-is
    }

    // File stream for reading hosts file
    std::ifstream hosts_file;

    // Common hosts file locations across different operating systems
    const std::vector<std::string> hosts_paths = {
        "/etc/hosts",           // Linux/Unix standard location
        "C:\\Windows\\System32\\drivers\\etc\\hosts",  // Windows standard location
        "/System/Library/etc/hosts"  // macOS alternative location
    };

    // Try to open hosts file from known locations
    for (const auto& path : hosts_paths) {
        hosts_file.open(path);
        if (hosts_file.is_open()) {
            break;  // Successfully opened, exit loop
        }
    }

    if (!hosts_file.is_open()) {
        return ""; // Could not open any hosts file
    }

    std::string line;
    std::string target_hostname = hostname;

    // Convert target hostname to lowercase for case-insensitive comparison
    std::transform(target_hostname.begin(), target_hostname.end(),
                   target_hostname.begin(), ::tolower);

    // Parse hosts file line by line
    while (std::getline(hosts_file, line)) {
        // Skip empty lines and comment lines (starting with #)
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Remove leading and trailing whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) {
            continue;
        }

        // Parse line into tokens
        std::istringstream iss(line);
        std::string ip_addr;
        std::string host_entry;

        // Get the IP address (first token on the line)
        if (!(iss >> ip_addr)) {
            continue;  // Skip malformed lines
        }

        // Validate that the first token is a valid IPv4 address
        if (!std::regex_match(ip_addr, ipv4_regex)) {
            continue; // Skip IPv6 entries or invalid IP addresses
        }

        // Check all hostnames/aliases on this line
        while (iss >> host_entry) {
            // Convert hostname to lowercase for case-insensitive comparison
            std::transform(host_entry.begin(), host_entry.end(),
                          host_entry.begin(), ::tolower);

            // Check if this hostname matches our target
            if (host_entry == target_hostname) {
                hosts_file.close();
                return ip_addr;  // Found match, return corresponding IP
            }
        }
    }

    hosts_file.close();
    return ""; // Hostname not found in hosts file
}

/////////
// eof //
/////////
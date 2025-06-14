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



vparpc::vparpc() {
}



int vparpc::svc2port(std::string ssSvcName) {


    struct servent *serviceEntry;
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




void vparpc::server(std::string ssService) {
    int iPort = svc2port(ssService);
    std::cout << "vparpc::server() - Starting TCP server on port " + std::to_string(iPort) << std::endl;
    
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFSIZ];
    
    // Create socket
    if ((server_fd =
            socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        return;
    }
    std::cout << "Server socket created" << std::endl;

    // Set socket options to reuse address
    int opt = 1;
    if (setsockopt(server_fd,
                   SOL_SOCKET,
                   SO_REUSEADDR,
                   &opt,
                   sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server_fd);
        return;
    }
    std::cout << "Socket options set" << std::endl;

    
    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces
    server_addr.sin_port = htons(iPort);
    
    // Bind socket to address and port
    if (bind(server_fd,
             (struct sockaddr*)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        return;
    }
    std::cout << "Server bound to port " << iPort << std::endl;

    // Start listening for connections
    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        close(server_fd);
        return;
    }
    
    std::cout << "Server listening on port " << iPort << "..." << std::endl;
    
    // Main server loop
    while (true) {
        // Accept incoming connection
        if ((client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len)) < 0) {
            perror("accept failed");
            continue;  // Continue to next iteration on error
        }
        
        std::cout << "Client connected from " << inet_ntoa(client_addr.sin_addr) 
                  << ":" << ntohs(client_addr.sin_port) << std::endl;
        
        // Clear buffer
        memset(buffer, 0, BUFSIZ);
        
        // Receive data from client
        ssize_t bytes_received = recv(client_fd, buffer, BUFSIZ - 1, 0);
        if (bytes_received < 0) {
            perror("recv failed");
        } else if (bytes_received == 0) {
            std::cout << "Client disconnected" << std::endl;
        } else {
            buffer[bytes_received] = '\0';  // Null-terminate the received data
            std::cout << "Received " << bytes_received << " bytes: " << buffer << std::endl;
            
            // Prepare response
            //std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nHello, World!";
            std::string response = "This is the response";

            // Send response
            if (send(client_fd, response.c_str(), response.length(), 0) < 0) {
                perror("send failed");
            } else {
                std::cout << "Response sent to client" << std::endl;
            }
        }
        
        // Close client connection
        close(client_fd);
        std::cout << "Client connection closed" << std::endl;
    }
    
    // Close server socket (this won't be reached in the current implementation)
    close(server_fd);
}

void vparpc::client(std::string ssHostName, std::string ssServiceName, const std::string& packet) {

    auto * pWin = new window();    gpSemiGr->cosmetics( SRUL,  SRUR,  SRLL,
                        SRLR,SVSR,SVSL,
                        SH,  SV);
    std::string ssCopr = "Copyright ";
    ssCopr.append("(c)");
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");
    pWin->set_title("vparpc::client(" + ssHostName + "," + ssServiceName + ")");

    int client_fd;
    struct sockaddr_in server_addr;
    struct hostent *host_entry;
    char response_buffer[BUFSIZ];       // BUFSIZ = 8192
    
    // Get host information
    host_entry = gethostbyname(ssHostName.c_str());
    if (host_entry == nullptr) {
        pWin->add_row(" Error: Could not resolve hostname "+ssHostName);
        pWin->render();
        return;
    }
    
    //std::cout << "  Host resolved: " << host_entry->h_name << std::endl;
    pWin->add_row("  Host resolved: "+ssHostName);

    // Create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        pWin->add_row(" Error: socket creation failed");
        pWin->render();
        return;
    }
    pWin->add_row("  Client socket created");

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(svc2port(ssServiceName));
    server_addr.sin_addr.s_addr = *((unsigned long *) host_entry->h_addr);
    
    pWin->add_row("  Connecting to port "+std::to_string(svc2port(ssServiceName)));

    // Connect to server
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        pWin->add_row(" Error: connection failed");
        close(client_fd);
        return;
    }
    pWin->add_row("  Connected to server");
    
    // Send packet to server
    ssize_t bytes_sent = send(client_fd, packet.c_str(), packet.length(), 0);
    if (bytes_sent < 0) {
        pWin->add_row(" Error: send failed");
        close(client_fd);
        pWin->render();
        return;
    }
    //std::string ssBytesSent = " Sent  Bytes sent "+std::to_string(bytes_sent);
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
        response_buffer[bytes_received] = '\0';  // Null-terminate
        //std::cout << "  Received " << bytes_received << " bytes: " << response_buffer << std::endl;
        pWin->add_row("  Received "+std::to_string(bytes_received)+" bytes: "+response_buffer);

    }
    
    // Close connection
    close(client_fd);
    pWin->add_row("  Client connection closed");
    pWin->render();
}
/////////
///
///
///
// eof //
/////////
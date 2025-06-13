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
    v_pWin = new window();
    v_pWin->set_title(__PRETTY_FUNCTION__);
}




//void vparpc::request(int iPort) {
void vparpc::request(std::string ssHostName,std::string ssServiceName) {

    std::cout << "vparpc::request(" + ssHostName + "," + ssServiceName + ")";
    std::cout << std::endl;

  #define USE_STREAM_SOCKET


    char buf[BUFSIZ];               /* data buffer for sending & receiving */
    struct hostent *hostnm;         /* server host name information        */
    struct sockaddr_in server;      /* server address                      */
    int s;                          /* client socket                       */
    socklen_t server_address_length = sizeof(server);

    hostnm = gethostbyname(ssHostName.c_str());
    std::cout << "  hostnm.h_name     is " << hostnm->h_name << std::endl;
    std::cout << "  hostnm.h_addrtype is " << hostnm->h_addrtype << std::endl;
    std::cout << "  hostnm.h_length   is " << hostnm->h_length << std::endl;
    //std::cout << "  hostnm.h_addr_list[0] is " << hostnm->h_addr_list[0] << std::endl;
    // std::cout << "hostnm.h_addr_list[1] is " << hostnm->h_addr_list[1] << std::endl;
    // std::cout << "hostnm.h_addr_list[2] is " << hostnm->h_addr_list[2] << std::endl;
    // std::cout << "hostnm.h_addr_list[3] is " << hostnm->h_addr_list[3] << std::endl;
    // std::cout << "hostnm.h_addr_list[4] is " << hostnm->h_addr_list[4] << std::endl;
    // std::cout << "hostnm.h_addr_list[5] is " << hostnm->h_addr_list[5] << std::endl;
    // std::cout << "hostnm.h_addr_list[6] is " << hostnm->h_addr_list[6] << std::endl;
    // std::cout << "hostnm.h_addr_list[7] is " << hostnm->h_addr_list[7] << std::endl;
    // std::cout << "hostnm.h_addr_list[8] is " << hostnm->h_addr_list[8] << std::endl;
    // std::cout << "hostnm.h_addr_list[9] is " << hostnm->h_addr_list[9] << std::endl;
    //
    /*
     * Put the server information into the server structure.
     * The port must be put into network byte order.
     */
    server.sin_family = AF_INET;    /* Address Family: Internet           */
    /*
     * Convert the port number from host to network byte order
     */

    std::cout << "  svc2port(" << ssServiceName << ")     is " << svc2port(ssServiceName) << std::endl;
    server.sin_port = htons(svc2port(ssServiceName));

    /*
     * Set the IP address of the target
     */
    server.sin_addr.s_addr = *((unsigned long *) hostnm->h_addr);

    /*
     * Get a socket.
     */
    if ((s = socket(AF_INET,SOCK_STREAM, 0)) < 0) {
        printf("%s", "socket error");
        exit(3);
    }

    /*
     * Connect to the server.
     */
    if (connect(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("%s::%s#%d %s",
            __FILE__,__FUNCTION__,__LINE__,"connect error");
        exit(4);
    }

    /*
     * Send a message to the destination to wake up xinetd
     */
    char szBuffer[] = {"GET / HTTP/1.1"};
    if (send(s, // socket descriptor
             szBuffer, // output buffer
             sizeof(szBuffer), // size of output buffer
             0) < 0) // flags (none required)
    {
        printf("%s", "Send error");
        exit(5);
    }

    char rxBuffer[BUFSIZ];

    ssize_t bytes_read = recv(s, rxBuffer,BUFSIZ, 0);
    std::cout << "bytes_read is " << bytes_read << std::endl;
    if ( bytes_read < 0) {
        printf("%s", "recv error");
        exit(6);
    }
    if (bytes_read > 0) {
        std::cout << "rxBuffer is " << rxBuffer << std::endl;
    }


    /*
     * Close the session and socket
     */
    close(s);
}

void vparpc::response(std::string ssServiceName) {

    std::cout << "vparpc::request(" + ssServiceName + ")";
    std::cout << std::endl;

    struct sockaddr addr;
    int sfd, cfd;
    ssize_t num_read;
    char buf[BUFSIZ];

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("socket");
        exit(1);
    }
    






    
//  #define USE_STREAM_SOCKET


    // char buf[BUFSIZ];               /* data buffer for sending & receiving */
    // struct hostent *hostnm;         /* server host name information        */
    // struct sockaddr_in server;      /* server address                      */
    // int s;                          /* client socket                       */
    // socklen_t server_address_length = sizeof(server);
    //
    // hostnm = gethostbyname(ssHostName.c_str());
    // std::cout << "  hostnm.h_name     is " << hostnm->h_name << std::endl;
    // std::cout << "  hostnm.h_addrtype is " << hostnm->h_addrtype << std::endl;
    // std::cout << "  hostnm.h_length   is " << hostnm->h_length << std::endl;
    // //std::cout << "  hostnm.h_addr_list[0] is " << hostnm->h_addr_list[0] << std::endl;
    // // std::cout << "hostnm.h_addr_list[1] is " << hostnm->h_addr_list[1] << std::endl;
    // // std::cout << "hostnm.h_addr_list[2] is " << hostnm->h_addr_list[2] << std::endl;
    // // std::cout << "hostnm.h_addr_list[3] is " << hostnm->h_addr_list[3] << std::endl;
    // // std::cout << "hostnm.h_addr_list[4] is " << hostnm->h_addr_list[4] << std::endl;
    // // std::cout << "hostnm.h_addr_list[5] is " << hostnm->h_addr_list[5] << std::endl;
    // // std::cout << "hostnm.h_addr_list[6] is " << hostnm->h_addr_list[6] << std::endl;
    // // std::cout << "hostnm.h_addr_list[7] is " << hostnm->h_addr_list[7] << std::endl;
    // // std::cout << "hostnm.h_addr_list[8] is " << hostnm->h_addr_list[8] << std::endl;
    // // std::cout << "hostnm.h_addr_list[9] is " << hostnm->h_addr_list[9] << std::endl;
    // //
    // // /*
    // //  * Put the server information into the server structure.
    // //  * The port must be put into network byte order.
    // //  */
    // // server.sin_family = AF_INET;    /* Address Family: Internet           */
    // // /*
    // //  * Convert the port number from host to network byte order
    // //  */
    // //
    // // std::cout << "  svc2port(" << ssServiceName << ")     is " << svc2port(ssServiceName) << std::endl;
    // // server.sin_port = htons(svc2port(ssServiceName));
    // //
    // // /*
    // //  * Set the IP address of the target
    // //  */
    // // server.sin_addr.s_addr = *((unsigned long *) hostnm->h_addr);
    // //
    // // /*
    // //  * Get a socket.
    // //  */
    // // if ((s = socket(AF_INET,SOCK_STREAM, 0)) < 0) {
    // //     printf("%s", "socket error");
    // //     exit(3);
    // // }
    // //
    // // /*
    // //  * Connect to the server.
    // //  */
    // // if (connect(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    // //     printf("%s::%s#%d %s",
    // //         __FILE__,__FUNCTION__,__LINE__,"connect error");
    // //     exit(4);
    // // }
    // //
    // // /*
    // //  * Send a message to the destination to wake up xinetd
    // //  */
    // // char szBuffer[] = {"GET / HTTP/1.1"};
    // // if (send(s, // socket descriptor
    // //          szBuffer, // output buffer
    // //          sizeof(szBuffer), // size of output buffer
    // //          0) < 0) // flags (none required)
    // // {
    // //     printf("%s", "Send error");
    // //     exit(5);
    // // }
    // //
    // // char rxBuffer[BUFSIZ];
    // //
    // // ssize_t bytes_read = recv(s, rxBuffer,BUFSIZ, 0);
    // // std::cout << "bytes_read is " << bytes_read << std::endl;
    // // if ( bytes_read < 0) {
    // //     printf("%s", "recv error");
    // //     exit(6);
    // // }
    // // if (bytes_read > 0) {
    // //     std::cout << "rxBuffer is " << rxBuffer << std::endl;
    // // }
    // //
    // //
    // // /*
    // //  * Close the session and socket
    // //  */
    // // close(s);
}





int vparpc::svc2port(std::string ssSvcName) {
    v_pWin->set_title(__PRETTY_FUNCTION__);

    std::string ssTemp = "vparpc::svc2port(" + ssSvcName + ")";
    v_pWin->add_row(ssTemp);


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
    v_pWin->add_row(__PRETTY_FUNCTION__);
    v_pWin->add_row(" hostname is " + hostname);

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
    server_addr.sin_port = htons(5164);
    
    // Bind socket to address and port
    if (bind(server_fd,
             (struct sockaddr*)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        return;
    }
    std::cout << "Server bound to port 5164" << std::endl;

    // Start listening for connections
    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        close(server_fd);
        return;
    }
    
    std::cout << "Server listening on port 5164..." << std::endl;
    
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
            std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nHello, World!";
            
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

/////////
// eof //
/////////
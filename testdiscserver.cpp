////////////////////////////////////////////////////////////////////
// ~/public_html/fw/testdiscserver.cpp 2025-07-15 18:16 dwg -     //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     5164
#define MAXLINE 1024

/**
 * @brief Entry point for the UDP server application.
 *
 * The main function initializes and sets up a UDP server that binds to a specified port.
 * It waits for a message from a client, prints the received message, and responds with
 * a predefined message "Hello from server".
 *
 * The server creates a socket, binds it to an address and port, and uses the socket for
 * communication with the client.
 *
 * @return Returns 0 upon successful execution.
 *         Exits the program with an error code if socket creation or binding fails.
 */
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    const char* hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr*)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    socklen_t len;
    int n;

    len = sizeof(cliaddr); //len is value/result

    n = recvfrom(sockfd, (char*)buffer, MAXLINE,
                 MSG_WAITALL, (struct sockaddr*)&cliaddr,
                 &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(sockfd, (const char*)hello, strlen(hello),
           MSG_CONFIRM, (const struct sockaddr*)&cliaddr,
           len);
    std::cout << "Hello message sent." << std::endl;

    return 0;
}


#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT    5164
#define MAXLINE 1024

/**
 * @brief Entry point of the Datagram-based client program.
 *
 * This function initializes and sets up a UDP socket, constructs the server
 * address and communicates with the server by sending a message and awaiting
 * a response. It handles socket creation, message transmission, and reception.
 *
 * @details
 * 1. Creates a UDP socket using `socket()` API.
 * 2. Configures server details including IP address and port.
 * 3. Sends a predefined message to the server using `sendto()`.
 * 4. Waits for a response from the server using `recvfrom()` and displays
 *    the received message in the console.
 * 5. Closes the socket before exiting the program.
 *
 * @return 0 on successful execution.
 *
 * @note In case of an error during socket creation, the program outputs
 *       an error message and terminates with `EXIT_FAILURE`.
 */
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    const char* hello = "Hello from client";
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n;
    socklen_t len;

    sendto(sockfd, (const char*)hello, strlen(hello),
           MSG_CONFIRM, (const struct sockaddr*)&servaddr,
           sizeof(servaddr));
    std::cout << "Hello message sent." << std::endl;

    n = recvfrom(sockfd, (char*)buffer, MAXLINE,
                 MSG_WAITALL, (struct sockaddr*)&servaddr,
                 &len);
    buffer[n] = '\0';
    std::cout << "Server :" << buffer << std::endl;

    close(sockfd);
    return 0;
}

//
// Created by doug on 2/17/25.
//
#include "mwfw2.h"
#include "xinetdctl.h"

/**
 * @brief Default constructor for the xinetdctl class.
 *
 * This constructor initializes an object of the xinetdctl class.
 */
xinetdctl::xinetdctl() {
}

/**
 * @brief Sends a wake-up message to the xinetd service at the specified port.
 *
 * This function establishes a TCP connection to a local server at the specified
 * port, sends a predefined message ("Wake up, sleepyhead!!"), and then closes
 * the connection. The function is used to trigger the xinetd service.
 *
 * @param iPort The port number to which the connection will be established.
 *
 * @pre The specified port should be available and reachable on the localhost.
 * @pre xinetd should be configured to listen to the specified port, if applicable.
 * @post A message is sent to the specified port, and the connection is closed.
 *
 * @exception SocketError Thrown if socket creation fails.
 * @exception ConnectError Thrown if the connection to the server fails.
 * @exception SendError Thrown if sending the message fails.
 *
 * @note Uses a stream socket (SOCK_STREAM) for communication.
 * @note The function terminates the program on error by calling exit with an
 *       appropriate error code.
 */
void xinetdctl::trigger(int iPort) {

  #define USE_STREAM_SOCKET
//#define USE_DGRAM_SOCKET

    // The attempt to use the DGRAM  to start the vpad didn't work

    unsigned short port;            /* port client will connect to         */
    char buf[BUFSIZ];               /* data buffer for sending & receiving */
    struct hostent *hostnm;         /* server host name information        */
    struct sockaddr_in server;      /* server address                      */
    int s;                          /* client socket                       */
    socklen_t server_address_length = sizeof(server);
    hostnm = gethostbyname("localhost");

    /*
     * Put the server information into the server structure.
     * The port must be put into network byte order.
     */
    server.sin_family = AF_INET;    /* Address Family: Internet           */

    /*
     * Convert the port number from host to network byte order
     */
    server.sin_port = htons(iPort);

    /*
     * Set the IP address of the target
     */
    server.sin_addr.s_addr = *((unsigned long *) hostnm->h_addr);

    /*
     * Get a socket.
     */
    if ((s = socket(AF_INET,
                    SOCK_STREAM
                    , 0)) < 0) {
        printf("%s", "socket error");
        exit(3);
    }

    /*
     * Connect to the server.
     */
    if (connect(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("%s", "connect error");
        exit(4);
    }

    /*
     * Send a message to the destination to wake up xinetd
     */
    char szBuffer[] = {"Wake up, sleepyhead!!"};
    if (send(s, // socket descriptor
             szBuffer, // output buffer
             sizeof(szBuffer), // size of output buffer
             0) < 0) // flags (none required)
    {
        printf("%s", "Send error");
        exit(5);
    }

    /*
     * Close the session and socket
     */
    close(s);
}


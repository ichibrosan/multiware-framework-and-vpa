/////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/vpadiscclient.cpp.h 2025-05-02 18:20        //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////

#include "mwfw2.h"
#define MAX_BUFFER 128
#define VPA_SERVER_PORT_LIT "5164"
#define VPA_SERVER_PORT      5164

vpadiscclient::vpadiscclient() {

    int connectionFd;
    int in;
    struct sockaddr_in servaddr;
    char timebuffer[MAX_BUFFER];

    connectionFd = socket(AF_INET,SOCK_DGRAM,0);
    if(connectionFd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr,0,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(VPA_SERVER_PORT);
    servaddr.sin_addr.s_addr = inet_addr(VPA_SERVER_PORT_LIT);
    sendto(connectionFd,
        timebuffer,
        1,
        0,
        (const struct sockaddr *)&servaddr,
        sizeof(servaddr)
        );
    in = recv(connectionFd,
        timebuffer,MAX_BUFFER,0);
    timebuffer[in] = 0;
    printf("\n%s",timebuffer);
    close(connectionFd);

}

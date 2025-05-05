/////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/vpadiscserver.cpp.h 2025-05-02 18:20        //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

#define MAX_BUFFER 128
#define VPA_SERVER_PORT 5164

vpadiscserver::vpadiscserver() {
int serverFd, msglen;
    ssize_t fromlen;
    struct sockaddr_in servaddr, from;
    char timebuffer[MAX_BUFFER+1];
    time_t currentTime;

    serverFd = socket(AF_INET,SOCK_DGRAM,0);
    if(serverFd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(VPA_SERVER_PORT);
    if(bind(serverFd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1) {
        perror("bind failed");
    }
    while (1) {
        fromlen = sizeof(from);

        // extern ssize_t recvfrom (
        // 1     int __fd,
        // 2     void *__restrict __buf,
        // 3     size_t __n,
        // 4     int __flags,
        // 5     __SOCKADDR_ARG __addr,
        // 6     socklen_t *__restrict __addr_len);


        msglen = recvfrom(
            serverFd,&timebuffer,MAX_BUFFER,0,
                                                // Added Casts Here
            (__SOCKADDR_ARG)&from,              // (__SOCKADDR_ARG)
            (socklen_t * __restrict) &fromlen); // (socklen_t * __restrict)
        if (msglen == 0) {
            currentTime = time(NULL);
            snprintf(timebuffer,MAX_BUFFER,"%s\n",ctime(&currentTime));
        }
    }

}

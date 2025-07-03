//////////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/vparpc_inetd_server.cpp 2025/05/01 16:54 dwg - //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.       //
//////////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"
//
// #include <iostream>
// #include <unistd.h>

const int BUFFER_SIZE = BUFSIZ;

int main() {
    auto * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    char szString[BUFFER_SIZE];
    memset(szString,0,BUFFER_SIZE);
    while ((bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {

        memcpy(szString,buffer,bytesRead);
        szString[strlen(szString)-1] = 0;
        gpSysLog->loginfo(szString);
        if (0 == strncmp("bye",buffer,3))
        {
            exit(0);
        }
        // Echo back the received data
        write(STDOUT_FILENO, buffer, bytesRead);
    }


    return 0;
}

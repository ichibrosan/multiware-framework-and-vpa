////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/config.h 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#ifndef CONFIG_H
#define CONFIG_H

#define HANDLE_NA            0
#define MAX_USERS            6
#define NUM_PASSWDS          2
/*
 * See /etc/services for assigned and dynamic port definitions
 */
#define VPA_PORT          5164    // services: vpa/tcp vpa-disc/udp
#define VPAD_START_PORT  65353    // services: vpad-start
#define VPA_NETSTAT_PORT 65354    // services: vpa-netstat
#define VPA_IP_PORT      65355    // services: vpa-ip

#define OCULAR_FQDN   "ocularstation.goodall.com"
#define OCULAR_INADDR "47-143-222-184.vng01.snbb.ca.frontiernet.net"

class config {
public:
    config();
};



#endif //CONFIG_H

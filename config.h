////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/config.h 2025/02/19                      //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#ifndef CONFIG_H
#define CONFIG_H

// NOLINT (misra-check)

#define HANDLE_NA            0
#define FORK_CHILD           0
#define MAX_USERS            6
#define NUM_PASSWDS          2
#define NO_HANDLE            0
#define PRE_STARTING_HANDLE  2
#define STARTING_HANDLE      3

#define OCULAR_FQDN   "ocularstation.goodall.com"
#define OCULAR_INADDR "47-143-222-184.vng01.snbb.ca.frontiernet.net"

// Generated with: head -c 4096 /dev/urandom | sha256sum | cut -b1-32
#define VPA_RPC_PSK    "348bcdbe62fead7028c8010490b27332"

#define here gpSysLog->here(__FILE__,__FUNCTION__,__LINE__);

class config {
public:
    config();
};



#endif //CONFIG_H

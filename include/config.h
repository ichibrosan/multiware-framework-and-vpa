////////////////////////////////////////////////////////////////////
// ~/public_html/fw/config.h 2025-07-16 08:08 dwg -               //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

// NOLINT (misra-check)

//#define DEBUG_CLI_LOGIN

#define CFG_HANDLE_NA                0
#define CFG_FORK_CHILD               0
#define CFG_MAX_USERS                6
//#define CFG_NUM_PASSWDS              2
#define CFG_NO_HANDLE                0
#define CFG_PRE_STARTING_HANDLE  ROW_DATA_HDR
#define CFG_USERNAME                 "doug"
#define CFG_PASSWORD                 "melange"
#define CFG_META_VERSION             "1"
#define CFG_MUTEX_NAME           "/fw_shmem_mutex"
#define CFG_MUTEX_MAX_SIZE           64
// Generated with: head -c 4096 /dev/urandom | sha256sum | cut -b1-32
#define CFG_VPA_RPC_PSK    "348bcdbe62fead7028c8010490b27332"

//#define DANTE_LOCAL_IP_ADDR "192.168.4.194"
//#define DANTE_PUBLIC_IP_ADDR "12.74.98.86"
//#define DANTE_PUBLIC_IP_ADDR "12.74.98.86"

#define here gpSysLog->herefunc(__FILE__,__FUNCTION__,__LINE__);

class config
{
public:
    config();
};

////////////////////
// eof - config.h //
////////////////////

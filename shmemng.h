/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/shmemng.h 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_SHMEMNG_H
#define MULTIWARE_SHMEMNG_H
#include "config.h"
#include "fw-limits.h"
#include <net/if.h>

/**
 * If you change the MFW_SHMEM_T schema, you need to reboot to assure
 * that you don't use a stale shared memory segment that is mis-aligned.
 * 2024/12/30 08:33 This is the shmemng structure for the HTML project.
 */
struct MFW_SHMEMNG_T {

    // Shared Environmental Value, set by environment::environment()
    int iSignature;
    char szHostname[DNS_FQDN_SIZE_MAX];
    char szIP[DNS_FQDN_SIZE_MAX];
    char szPublicIP[DNS_FQDN_SIZE_MAX];
    char szIface[IFNAMSIZ];
    char szProtocol[INET_PROT_NAME_MAX];
    char szImgRoot[INET_URL_SIZE_MAX];
    char szCgiRoot[INET_URL_SIZE_MAX];
    char szStylesRoot[INET_URL_SIZE_MAX];
    char szJournalRoot[INET_URL_SIZE_MAX];
    char szUser[UT_NAMESIZE];
    char szRpcUuid[UUID_SIZE];             // 37

    /*************************************************************************
     * creds is a vector of structures. it needs to be indexed using         *
     * the (int)handle returned by the password::lookup_username_password()  *
     * function. valid authenticated handles span from 3-5 so we need to     *
     * allow for three unused structures at the beginning of the vector      *
     * where we would find ROW_META_HEADER, ROW_META_DATA & ROW_DATA_HEADER. *
     * In return for wasting the space, we get to use the raw handle as the  *
     * without trying to calculate the index around the meta data. This will *
     * make the code more straightforward and readable. 2025/01/23 19:18 dwg *
     ************************************************************************/
    struct {

        int  iAuthHandle;                       // 8

        char szAuthUserName[UT_NAMESIZE];       // 32
        char szAuthFirstName[UT_NAMESIZE];      // 32
        char szAuthLastName[UT_NAMESIZE];       // 32
        char szAuthUUID[UUID_SIZE];             // 37
        char szAuthLevel[UT_NAMESIZE];          // 32

        char szRemoteHost[DNS_FQDN_SIZE_MAX];   // 253   // from Apache2
        char szRemoteAddr[DNS_FQDN_SIZE_MAX];   // 253   // from Apache2
        char szHttpUserAgent[128];              // 128   // from Apache2

    } creds[ROW_DATA+MAX_USERS];    // sizeof(creds) = 7236

    bool  vpad_running;           // control vpad while loop
    pid_t vpad_pid;               // process id of VPA Daemon
    int   vpad_exit_status;
    int   vpad_uptime_seconds;
    char sz_vpad_start_time[24];                                                                                                                                                                                                                                                                               //
    int vpad_req_bits;               // functional request bits
    int vpad_resp_bits;              // functional response bits
    int vpad_errno[VPAD_REQ_COUNT];
    char szVpad_date[80];            // date stamp of vpad.cpp
    char szVpad_time[80];            // time stamp of vpad.cpp

    bool tests_started;
    time_t time_started;
    char szTimeStarted[UT_TIMESIZE];
    int tests_processed_bits;
    int tests_passed_bits;
    int tests_failed_bits;
    int tests_skipped_bits;
    int num_tests_processed;
    int num_tests_skipped;
    int num_tests_passed;
    int num_tests_failed;
    bool tests_completed;
    bool overall_test_results;
    time_t time_completed;
    char szTimeCompleted[UT_TIMESIZE];

    bool bDisplayShmVars;
    bool bDisplayEnvVars;
    bool bDisplaySchema;

} *m_pShMemng;

#endif //MULTIWARE_SHMEMNG_H

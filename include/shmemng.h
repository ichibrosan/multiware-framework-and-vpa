/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/shmemng.h 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_SHMEMNG_H
#define MULTIWARE_SHMEMNG_H
#include "config.h"
#include "fw-limits.h"
#include <net/if.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <system_error>
#include <memory>

/**
 * If you change the MFW_SHMEM_T schema, you need to reboot to assure
 * that you don't use a stale shared memory segment that is mis-aligned.
 * 2024/12/30 08:33 This is the shmemng structure for the HTML project.
 */
struct MFW_SHMEMNG_T {

    //shmvar_t shmvar[SHMVAR_COUNT];

    // Shared Environmental Value, set by environment::environment()
    int iSignature;
    size_t stShMemSize;
    char szHostname[DNS_FQDN_SIZE_MAX];
    char szIP[DNS_FQDN_SIZE_MAX];
    char szPublicIP[DNS_FQDN_SIZE_MAX];
    char szIface[IFNAMSIZ];
    char szProtocol[INET_PROT_NAME_MAX];
    char szCgiRoot[INET_URL_SIZE_MAX];
    char szImgRoot[INET_URL_SIZE_MAX];
    char szJournalRoot[INET_URL_SIZE_MAX];
    char szStylesRoot[INET_URL_SIZE_MAX];
    char szStylesFileRoot[INET_URL_SIZE_MAX];
    char szTmpRoot[FILENAME_MAX];
    char szConfigRoot[FILENAME_MAX];
    char szUser[UT_NAMESIZE];
    char szRpcUuid[UUID_SIZE];             // 37

    char szRemoteHost[DNS_FQDN_SIZE_MAX];
    char szRemoteAddr[IPV4_ADDR_SIZE_MAX];
    char szRemoteAuth[UUID_SIZE];
    char szRemoteVersion[RVERSION_SIZE_MAX];

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

    } creds[ROW_DATA+MAX_USERS];     // sizeof(creds) = 7236

    struct {
        char szBodyFGcolor[COLOR_SIZE_MAX];
        char szBodyBGcolor[COLOR_SIZE_MAX];
        char szTableFGcolor[COLOR_SIZE_MAX];
        char szTableBGcolor[COLOR_SIZE_MAX];
        char szTrFGcolor[COLOR_SIZE_MAX];
        char szTrBGcolor[COLOR_SIZE_MAX];
        char szThFGcolor[COLOR_SIZE_MAX];
        char szThBGcolor[COLOR_SIZE_MAX];
        char szTdFGcolor[COLOR_SIZE_MAX];
        char szTdBGcolor[COLOR_SIZE_MAX];
        char szDbFGcolor[COLOR_SIZE_MAX];
        char szDbBGcolor[COLOR_SIZE_MAX];
    } prefs[ROW_DATA+MAX_USERS];

    bool   vpad_running;              // control vpad while loop
    pid_t  vpad_parent_pid;           // process id of VPA Daemon Parent
    pid_t  vpad_child_pid;            // process id of VPA Daemon Child
    int    vpad_exit_status;
    int    vpad_uptime_seconds;
    char   sz_vpad_start_time[24];                                                                                                                                                                                                                                                                               //
    int    vpad_req_bits;               // functional request bits
    int    vpad_resp_bits;              // functional response bits
    int    vpad_errno[DIAGNOSE_REQ_COUNT];
    char   szVpad_date[80];            // date stamp of vpad.cpp
    char   szVpad_time[80];            // time stamp of vpad.cpp

    bool   tests_started;
    time_t time_started;
    char   szTimeStarted[UT_TIMESIZE];
    int    tests_processed_bits;
    int    tests_passed_bits;
    int    tests_failed_bits;
    int    tests_skipped_bits;
    int    num_tests_processed;
    int    num_tests_skipped;
    int    num_tests_passed;
    int    num_tests_failed;
    bool   tests_completed;
    bool   overall_test_results;
    time_t time_completed;
    char   szTimeCompleted[UT_TIMESIZE];

    bool   bDisplayShmVars;
    bool   bDisplayEnvVars;
    bool   bDisplaySchema;

} *m_pShMemng;

class SharedMemoryMutex {
public:
    SharedMemoryMutex(const char* name) {
        // Create or open a named semaphore
        mutex_ = sem_open(name, O_CREAT, 0644, 1);
        if (mutex_ == SEM_FAILED) {
            throw std::system_error(errno, std::system_category(), "sem_open failed");
        }
    }

    ~SharedMemoryMutex() {
        if (mutex_ != SEM_FAILED) {
            sem_close(mutex_);
        }
    }

    void lock() {
        if (sem_wait(mutex_) != 0) {
            throw std::system_error(errno, std::system_category(), "sem_wait failed");
        }
    }

    void unlock() {
        if (sem_post(mutex_) != 0) {
            throw std::system_error(errno, std::system_category(), "sem_post failed");
        }
    }

private:
    sem_t* mutex_;
};

class SharedMemoryManager {
public:
    SharedMemoryManager() 
        : mutex_("/fw_shmem_mutex") { // Create mutex with unique name
    }

    void lockSharedMemory() {
        std::lock_guard<SharedMemoryMutex> lock(mutex_);
    }

    void accessSharedMemory() {
        // RAII-style locking
        std::lock_guard<SharedMemoryMutex> lock(mutex_);
        
        // Now you can safely access m_pShMemng
        //m_pShMemng->iSignature++;
        // ... other operations ...
    }

    void releaseSharedMemory() {
        // RAII-style unlocking
        std::lock_guard<SharedMemoryMutex> unlock(mutex_);
    }

private:
    SharedMemoryMutex mutex_;
};



#endif //MULTIWARE_SHMEMNG_H
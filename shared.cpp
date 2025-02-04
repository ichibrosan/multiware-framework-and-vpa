//////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/shared.cpp 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.   //
//////////////////////////////////////////////////////////////////////////
#include "shared.h"

#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

extern CLog *gpLog;

shared::shared() {
    m_pSysLog = new CSysLog();

    bool bJustCreated = false;

    // Set key to hex version of my VPA port number (recognizable)
    key_t key = 0x5164;

    // Set size to the size of my shared data structure (member data)
    size_t size = sizeof(MFW_SHMEMNG_T);

    // Set shmFlg with read/write permissions, so I can access
    // the shared region once created. See shared.h
    int shmflg = OBJ_PERMS;

    m_smsi = shmget(key, size, shmflg);
    if (-1 == m_smsi) {
        //decode_shmget_errno(errno);
        if (ENOENT == errno) {
            // ENOENT means no segment exists and create not specified
            shmflg = IPC_CREAT | OBJ_PERMS;

            // Create the memory segment and save the identifier
            m_smsi = shmget(key, size, shmflg);
            if (-1 == m_smsi) {
                decode_shmget_errno(errno);
                std::cout << "ERROR: unable to open shared segment"
                          << std::endl;
            }
            bJustCreated = true;
        }
    }

    // Prepare to attach shared segment using shmat
    shmflg = 0;
    // Establish addressability to shared segment
    m_pShMemng = (MFW_SHMEMNG_T *) shmat(m_smsi, nullptr, shmflg);

    if ((void *) -1 == m_pShMemng) {
        printf("Error calling shmat\n");
        decode_shmat_errno(errno);
    }

    if (bJustCreated) {
        m_pShMemng->iSignature = UNIVERSAL_ANSWER;
        size_t credsSize = sizeof(MFW_SHMEMNG_T::creds);

        //********************************************************************
        // Initialize shared credential data after creation 2025/01/24 dwg - *
        //********************************************************************
        memset(m_pShMemng->creds, 0, credsSize);

        /*
         * By default, CGI scripts don't do these displays
         */
        m_pShMemng->bDisplaySchema = false;
        m_pShMemng->bDisplayEnvVars = false;
        m_pShMemng->bDisplayShmVars = false;
    }

}

/**
 * Make a new shared region using the specified key
 * @param keyparm
 * @param sizeparm
 * @return
 */
void * shared::mkshared(key_t keyparm,size_t sizeparm) {
    bool bJustCreated = false;

    // Set key to hex version of my VPA port number (recognizable)
    key_t key = keyparm;
    // Set size to the size of my shared data structure (member data)
    size_t size = sizeparm;
    // Set shmFlg with read/write permissions, so I can access
    // the shared region once created. See shared.h
    int shmflg = OBJ_PERMS;
    m_smsi = shmget(key, size, shmflg);
    // Test to see if we open the segment successfully
    if (-1 == m_smsi) {
        //decode_shmget_errno(errno);
        if (ENOENT == errno) {
            // ENOENT means no segment exists and create not specified
            shmflg = IPC_CREAT | OBJ_PERMS;

            // Create the memory segment and save the identifier
            m_smsi = shmget(key, size, shmflg);
            if (-1 == m_smsi) {
                decode_shmget_errno(errno);
                m_pSysLog->loginfo("ERROR: unable to open shared segment");
            }
            bJustCreated = true;
        }
    }

    // Prepare to attach shared segment using shmat
    shmflg = 0;

    // Establish addressability to shared segment
    return shmat(m_smsi, nullptr, shmflg);

}


void shared::decode_shmget_errno(int shm_errno)
{
    char szTemp[128];
    switch (shm_errno) {
        case EACCES: m_pSysLog->loginfo("errno was EACCESS");     break;
        case EEXIST: m_pSysLog->loginfo("errno was EEXIST");      break;
        case EINVAL: m_pSysLog->loginfo("errno was EINVALO");     break;
        case ENFILE: m_pSysLog->loginfo("errno was ENFILE");      break;
        case ENOENT: m_pSysLog->loginfo("errno was ENOENT");      break;
        case ENOMEM: m_pSysLog->loginfo("errno was ENOMEM");      break;
        case ENOSPC: m_pSysLog->loginfo("errno was ENOSPC");      break;
        case EPERM:  m_pSysLog->loginfo("errno was EPERM");       break;
        default:
            sprintf(szTemp, "errno was %d", shm_errno);
            m_pSysLog->loginfo(szTemp);                           break;
    }
}

void shared::decode_shmat_errno(int shm_errno)
{
    char szTemp[128];
    switch (shm_errno) {
        case EACCES: m_pSysLog->loginfo("errno was EACCESS");   break;
        case EIDRM:  m_pSysLog->loginfo("errno was EIDRM");     break;
        case EEXIST: m_pSysLog->loginfo("errno was EEXIST");    break;
        case EINVAL: m_pSysLog->loginfo("errno was EINVAL");    break;
        default:
            sprintf(szTemp,"errno was %d", errno);
            m_pSysLog->loginfo(szTemp);                         break;
    }
}

int shared::get_smsi() const {
    return m_smsi;
}


shared::~shared() {
    shmdt(m_pShMemng);
}

//////////////////////
// eof - shared.cpp //
//////////////////////
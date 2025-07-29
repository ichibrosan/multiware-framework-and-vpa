////////////////////////////////////////////////////////////////////
// ~/public_html/fw/shared.cpp 2025-07-15 18:16 dwg -             //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

/**
 * @brief The function of the shared class constructor is to open the region
 * if it already exists, and to create it and open it if not. It also is
 * responsible for creating a new szRpcUUID each time the memory region is
 * created. All other shared region initialization is performed in the
 * environment class constructor.
 *
 * @return True if the resource is shared; false otherwise.
 */
shared::shared()
{
    bool bJustCreated = false;

    // Set key to hex version of my VPA port number (recognizable)
    key_t key = 0x5164;

    // Set size to the size of my shared data structure (member data)
    size_t size = sizeof(MFW_SHMEMNG_T);

    // Set shmFlg with read/write permissions, so I can access
    // the shared region once created. See shared.h
    int shmflg = OBJ_PERMS;

    m_smsi = shmget(key, size, shmflg);
    if (-1 == m_smsi)
    {
        if (ENOENT == errno)
        {
            shmflg = IPC_CREAT | OBJ_PERMS;
            m_smsi = shmget(key, size, shmflg);
            bJustCreated = true;
        }
    }

    shmflg = 0;
    m_pShMemng = (MFW_SHMEMNG_T*)shmat(m_smsi, nullptr, shmflg);

    if (bJustCreated)
    {
        m_pShMemng->iSignature = UNIVERSAL_ANSWER;
        m_pShMemng->stShMemSize = size;


        uuid_t uuid;
        char szUUID[37];
        uuid_generate(uuid);
        uuid_unparse(uuid, szUUID);
        strcpy(m_pShMemng->szRpcUuid, szUUID);

        size_t credsSize = sizeof(MFW_SHMEMNG_T::creds);
        memset(m_pShMemng->creds, 0, credsSize);

        /*
         * By default, CGI scripts don't do these displays
         */
        m_pShMemng->bDisplaySchema = false;
        m_pShMemng->bDisplayEnvVars = false;
        m_pShMemng->bDisplayShmVars = false;
    }
}


//////////////////////
// eof - shared.cpp //
//////////////////////

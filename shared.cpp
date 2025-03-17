//////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/shared.cpp 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.   //
//////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

/**
 * @brief Global pointer to the CLog object.
 *
 * The `gpLog` global pointer is utilized as a logging mechanism across
 * the application. It provides methods for truncating the log file,
 * writing strings, and handling formatted output for logging purposes.
 *
 * - `journal.cpp` utilizes `gpLog` for truncating and initializing logs
 *    during program execution.
 * - `notesave.cpp` uses it to log information related to the note-saving
 *    process.
 *
 * It is initialized with the current file name and function name where it
 * is created. The log file allows appending of data or clearing of content
 * depending on the operations invoked.
 *
 * Note: Ensure that `gpLog` is properly initialized before use and deleted
 * to release allocated resources.
 */
extern CLog *gpLog;

/**
 * @brief Checks if a resource is shared among multiple entities or threads.
 *
 * This method determines if the resource it is called upon is being shared,
 * allowing for synchronization, conditional logic, or optimization based on the
 * shared state.
 *
 * @return True if the resource is shared; false otherwise.
 */
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
        m_pShMemng->stShMemSize = size;
        size_t credsSize = sizeof(MFW_SHMEMNG_T::creds);

        /* each time the shared region is created, a new and unique
         * RpcUuid is set to authenticate RPC calls
         */
        uuid_t uuid;
        char szUUID[37 ];
        uuid_generate(uuid);
        uuid_unparse(uuid,szUUID);
        strcpy(m_pShMemng->szRpcUuid,szUUID);

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
 * Establishes access to a shared memory segment, either by retrieving the
 * identifier of an existing segment or by creating a new segment if it does
 * not already exist.
 *
 * The method attempts to attach the shared segment using `shmat`. If the
 * segment specified by the key doesn't exist, it will attempt to create it.
 *
 * @param keyparm The key that uniquely identifies the shared memory segment.
 * @param sizeparm The size of the shared memory segment in bytes.
 * @return A void pointer to the attached shared memory segment.
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


/**
 * Decodes the errno value returned from the shmget system call and logs
 * an appropriate message explaining the error via the CSysLog instance.
 *
 * @param shm_errno The errno value to decode, indicating the error that
 * occurred during the shmget system call.
 *
 * The function maps specific errno values to descriptive messages and logs
 * them. If the error code is not recognized, it logs the numeric errno value.
 *
 * - EACCES: Indicates a permission denied error.
 * - EEXIST: Indicates that the shared memory segment already exists.
 * - EINVAL: Indicates an invalid parameter error.
 * - ENFILE: Indicates that the system-wide limit for total number of open files
 *   has been reached.
 * - ENOENT: Indicates that the specified shared memory segment does not exist.
 * - ENOMEM: Indicates that there is not enough memory available.
 * - ENOSPC: Indicates that there is no space available.
 * - EPERM: Indicates an operation not permitted error.
 */
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

/**
 * Decodes the given error number resulting from the `shmat` system call
 * into a human-readable explanation of the error.
 *
 * @param errnum The error number produced by `shmat`.
 * @return A string describing the error corresponding to the provided error number.
 */
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

/**
 * Retrieves the shared memory segment identifier (SMSI).
 *
 * @return The shared memory segment identifier as an integer.
 */
int shared::get_smsi() const {
    return m_smsi;
}


/**
 * Destructor for the shared class.
 *
 * This method detaches the shared memory segment associated with the object
 * to ensure that the program no longer maintains a connection to the shared
 * memory. This is done by calling `shmdt` with the shared memory pointer
 * `m_pShMemng`.
 */
shared::~shared() {
    shmdt(m_pShMemng);
}

//////////////////////
// eof - shared.cpp //
//////////////////////

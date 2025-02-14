////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/vpad.cpp 2025/01/11 05:21 //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.               //
////////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"
#include "look.h"

/**
 * @struct MFW_SHMEMUSER_T
 * @brief Represents a structure for shared memory user information.
 *
 * The structure stores metadata related to a user including authentication and personal details.
 */
struct MFW_SHMEMUSER_T {
    /**
     * @brief Represents a signature identifier for a shared memory user.
     *
     * This variable is used to uniquely define or identify a specific
     * shared memory user within the MFW_SHMEMUSER_T struct.
     */
    int  iSignature;
    /**
     * @brief Stores the authenticated user's username.
     *
     * This character array holds the username of a user who has been authenticated.
     * It is defined with a maximum size of UT_NAMESIZE to ensure enough space for typical usernames.
     */
    char szAuthUserName[UT_NAMESIZE];
    /**
     * @brief Stores the first name of an authenticated user.
     *
     * This variable is intended to hold a string representing the
     * user's first name as part of their authentication details.
     * It is typically used in structures or systems that manage
     * user information and authentication.
     *
     * @note The size of this array is defined by the constant UT_NAMESIZE.
     */
    char szAuthFirstName[UT_NAMESIZE];
    /**
     * @brief Stores the authenticated user's last name.
     *
     * This character array is used to store the last name of an authenticated
     * user. The size of the array is defined by the constant UT_NAMESIZE, which
     * ensures that the allocated memory is sufficient to accommodate the last
     * name along with a null-terminator.
     */
    char szAuthLastName[UT_NAMESIZE];
    /**
     * @brief Stores the unique identifier (UUID) for authentication purposes.
     *
     * This variable is used to represent the Authentication UUID, which is a unique
     * string assigned for identifying a specific authenticated entity.
     *
     * @note The size of this array is determined by the predefined constant `UUID_SIZE`.
     */
    char szAuthUUID[UUID_SIZE];
    /**
     * @brief Identifier for the authentication handle.
     *
     * This variable serves as a unique handle or reference to the current
     * authentication context within the system. It is utilized to manage
     * and track authentication-related processes.
     */
    int  iAuthHandle;
};

/**
 * @brief Global pointer to a shared memory user structure.
 *
 * This variable is a global pointer that references a structure of type
 * MFW_SHMEMUSER_T, used to manage shared memory-related user data. It is
 * initialized to nullptr, and its value is expected to be set during runtime
 * as per the application requirements.
 *
 * The MFW_SHMEMUSER_T structure stores user-related information like
 * signatures, user names, UUIDs, and authorization handles.
 *
 * @note The initialization and handling of this pointer must be done carefully
 * to prevent dereferencing null or uninitialized memory.
 */
struct MFW_SHMEMUSER_T * gpShUser = nullptr;

/**
 * @brief Main function that initializes core components, logs system
 * information, and outputs processed statistical data and authenticated user
 * credentials.
 *
 * This function initializes the logging mechanism, shared memory, environment
 * services, and operating system interface modules. It retrieves and displays
 * statistics related to processed, passed, failed, and skipped tests along with
 * their respective binary representations. Additionally, it outputs the details
 * of authenticated users, including their usernames, names, UUIDs, and handles.
 *
 * @return int Returns 0 upon successful execution.
 */
int main() {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    printf("vpad Copyright (c) 2025 Douglas Wade Goodall. "
           "All Rights Reserved.\n");
    // gpLog    = new CLog(__FILE__, __FUNCTION__);
    // gpSh     = new shared();
    // gpEnv    = new environment();
    // gpOS     = new osIface();

    printf("num_tests_processed is %d\n",
        gpSh->m_pShMemng->num_tests_processed);
    printf("num_tests_skipped is %d\n",
            gpSh->m_pShMemng->num_tests_skipped);
    printf("num_tests_passed is %d\n",
            gpSh->m_pShMemng->num_tests_passed);
    printf("num_tests_failed is %d\n\n",
            gpSh->m_pShMemng->num_tests_failed);

    printf("tests_processed_bits are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_processed_bits,7);
    printf("\ntests_passed_bits    are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_passed_bits,7);
    printf("\ntests_failed_bits    are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_failed_bits,7);
    printf("\ntests_skipped_bits   are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_skipped_bits,7);

    printf("\n\nCredentials of Authenticated Users:");
    for (int iRow=3;iRow<MAX_USERS+ROW_DATA;iRow++) {
        if (0 < gpSh->m_pShMemng->creds[iRow].iAuthHandle) {
            printf("\n-------------------------------------------\n");
            printf(    "szAuthUserName  is %s\n",
                gpSh->m_pShMemng->creds[iRow].szAuthUserName);
            printf(    "szAuthFirstname is %s\n",
                gpSh->m_pShMemng->creds[iRow].szAuthFirstName);
            printf(    "szAuthLastName  is %s\n",
                gpSh->m_pShMemng->creds[iRow].szAuthLastName);
            printf(    "szAuthUUID      is %s\n",
                gpSh->m_pShMemng->creds[iRow].szAuthUUID);
            printf(    "iAuthHandle     is %d\n",
                gpSh->m_pShMemng->creds[iRow].iAuthHandle);
            printf(    "iHttpUserAgent  is %s\n",
         gpSh->m_pShMemng->creds[iRow].szHttpUserAgent);
        }
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/mutations.cpp 2025-05-02 18:20        //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * @class mutations
 * @brief Default constructor for the mutations class.
 *
 * The mutations constructor is responsible for initializing an instance of
 * the mutations class. This may involve setting up default values or
 * configurations required by the class.
 */
mutations::mutations() = default;

/**
 * @brief Constructs a muteInt object.
 *
 * This constructor initializes the muteInt object with a specified mutex
 * name and an integer pointer. It creates or opens a named semaphore for
 * synchronization using the given mutex name.
 *
 * @param pszName A C-style string representing the name of the semaphore to
 * create or open.
 * @param pInt A pointer to an integer that will be protected using the
 * semaphore.
 *
 * @throws std::system_error If the semaphore creation/opening fails, a
 * system_error is thrown with the appropriate error code and message.
 */
muteInt::muteInt(const char * pszName,int * pInt) {
    strcpy(m_szMutexName,pszName);
    m_pInt = pInt;
    m_mutex_ = sem_open(pszName,O_CREAT, 0644, 1);
    if (m_mutex_ == SEM_FAILED) {
        throw std::system_error(errno, std::system_category(),
            "sem_open failed");
    }
}

/**
 * Retrieves the value of the integer with thread-safe access.
 *
 * This method provides synchronized access to the integer
 * value it manages by acquiring a mutex before reading the value
 * and releasing the mutex afterward.
 *
 * @return The integer value managed by the muteInt instance.
 */
int muteInt::get() {
    sem_wait(m_mutex_);
    int iValue = *m_pInt;
    sem_post(m_mutex_);
    return iValue;
}

/**
 * Updates the value of the shared integer variable in a thread-safe manner.
 *
 * Uses a semaphore to ensure exclusive access to the shared integer
 * during the update operation. After the operation, the semaphore is
 * released to signal completion.
 *
 * @param value The new value to assign to the shared integer.
 */
void muteInt::put(int value) {
    sem_wait(m_mutex_);
    *m_pInt = value;
    sem_post(m_mutex_);
}


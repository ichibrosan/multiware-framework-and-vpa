////////////////////////////////////////////////////////////////////
// ~/public_html/fw/shMemMutex.cpp 2025-07-15 18:16 dwg -         //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * Constructs a SharedMemoryMutex object by creating or opening a named
 * semaphore.
 *
 * This constructor initializes a POSIX named semaphore with the given name.
 * If the semaphore cannot be created or opened, it throws a
 * `std::system_error` exception with the specific error code and message.
 *
 * @param name A pointer to a null-terminated string representing the name of
 *             the semaphore. The name should start with a forward slash ('/')
 *             and be followed by one or more characters.
 * @return A new instance of SharedMemoryMutex with the semaphore initialized.
 *         Throws a `std::system_error` if semaphore initialization fails.
 */
SharedMemoryMutex::SharedMemoryMutex(const char* name)
{
    // Create or open a named semaphore
    mutex_ = sem_open(name, O_CREAT, 0644, 1);
    if (mutex_ == SEM_FAILED)
    {
        throw std::system_error(errno, std::system_category(),
                                "sem_open failed");
    }
}

/**
 * @brief Destructor for the SharedMemoryMutex class.
 *
 * This destructor is responsible for cleaning up the underlying semaphore
 * used by the SharedMemoryMutex instance. If the semaphore was successfully
 * initialized and is not in an invalid state (`SEM_FAILED`), it is closed
 * to release system resources. This ensures proper resource management and
 * avoids potential resource leaks.
 */
SharedMemoryMutex::~SharedMemoryMutex()
{
    if (mutex_ != SEM_FAILED)
    {
        sem_close(mutex_);
    }
}

/**
 * Acquires the lock for the shared memory mutex.
 *
 * The lock() method attempts to decrement (wait on) the semaphore associated
 * with the shared memory mutex. This operation blocks the calling thread
 * until the semaphore value is greater than zero, effectively acquiring the
 * lock.
 *
 * If the semaphore operation fails (e.g., due to an interruption or internal
 * error), a `std::system_error` exception is thrown with the appropriate
 * error code and description.
 *
 * @throws std::system_error Thrown if the semaphore operation (`sem_wait`)
 * fails.
 */
void SharedMemoryMutex::SharedMemoryMutex::lock()
{
    if (sem_wait(mutex_) != 0)
    {
        throw std::system_error(errno, std::system_category(),
                                "sem_wait failed");
    }
}

/**
 * Releases the lock held by the shared memory mutex.
 *
 * This method increments the value of the semaphore, allowing other processes
 * or threads waiting to acquire the lock to proceed. It indicates that the
 * critical section is no longer being accessed. If the semaphore operation
 * fails, a `std::system_error` exception is thrown, providing detailed
 * information about the error.
 *
 * @throws std::system_error if the semaphore operation (`sem_post`) fails,
 *         including the error code and a corresponding message.
 */
void SharedMemoryMutex::unlock()
{
    if (sem_post(mutex_) != 0)
    {
        throw std::system_error(errno, std::system_category(),
                                "sem_post failed");
    }
}

/////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/shMemMutex.h 2025/04/21                   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @class SharedMemoryMutex
 * @brief A mutex implementation for synchronizing access to shared memory
 *        using named semaphores.
 *
 * This class provides a mechanism to synchronize access to shared resources
 * across multiple processes using named semaphores. It ensures thread safety
 * and proper resource handling. The mutex is created or opened using a
 * specified name.
 */
class SharedMemoryMutex
{
    /**
     * Constructs a SharedMemoryMutex object and initializes a named
     * semaphore. The constructor creates or opens a POSIX named semaphore
     * associated with the provided name. If the semaphore cannot be created
     * or opened, it throws a system_error exception.
     *
     * @param name A pointer to a null-terminated string that represents the
     *             name of the semaphore. The name must begin with a slash
     *             ('/') and be followed by one or more characters.
     * @return A new instance of SharedMemoryMutex with the semaphore
     *         initialized. Throws a system_error on failure to create or
     *         open the semaphore.
     */
public:
    SharedMemoryMutex(const char* name);

    /**
     * Destructor for the SharedMemoryMutex class.
     *
     * Cleans up resources associated with the shared memory mutex.
     * Closes the semaphore if it was successfully opened, ensuring no
     * resource leaks.
     */
    ~SharedMemoryMutex();

    /**
     * Acquires the lock for the shared memory mutex.
     *
     * This method blocks the calling thread until the lock is successfully
     * acquired. If the semaphore operation fails, a `std::system_error`
     * exception is thrown.
     *
     * @throws std::system_error if the semaphore operation fails, with the
     *         error code and a corresponding message.
     */
    void lock();

    /**
     * Unlocks the shared memory mutex, releasing the lock held by the
     * current process.
     *
     * This method signals the underlying semaphore to indicate that the
     * critical section is no longer held, allowing other processes or
     * threads waiting to acquire the lock to proceed. If the semaphore
     * operation fails, an exception of type std::system_error is thrown,
     * encapsulating the error code and a descriptive message.
     *
     * @throws std::system_error If the semaphore operation (sem_post) fails.
     */
    void unlock();

    /**
     * @brief Pointer to a named semaphore used for managing access to
     *        shared resources.
     *
     * This variable holds a pointer to a `sem_t` semaphore, which is used
     * for synchronizing access to shared resources between multiple
     * processes in a thread-safe manner. It is created or opened using the
     * `sem_open` system call and enables locking and unlocking mechanisms
     * for interprocess communication.
     *
     * The semaphore is initialized during the construction of the
     * `SharedMemoryMutex` object and released during its destruction.
     */
private:
    sem_t* mutex_;
};

////////////////////////
// eof - shMemMutex.h //
////////////////////////

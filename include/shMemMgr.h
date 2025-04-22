/////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/shMemMgr.h 2025/04/21                     //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////


#ifndef SHMEMMGR_H
#define SHMEMMGR_H

/**
 * @class SharedMemoryManager
 * @brief Manages synchronized access to a shared memory region using a mutex.
 *
 * This class provides a high-level interface for locking, accessing, and
 * releasing shared memory resources. It ensures thread-safe operations on
 * shared memory using RAII-based locking mechanisms.
 *
 * The operations use a shared memory mutex to prevent multiple entities
 * from accessing the shared memory region simultaneously. The locking and
 * unlocking are managed internally.
 */
class SharedMemoryManager {
    /**
     * Constructor for the SharedMemoryManager class.
     * Initializes a shared memory manager instance, creating and associating
     * a mutex with the provided name to manage access to shared memory
     * resources.
     *
     * @param name A C-string representing the unique name of the mutex to be
     *             created and used. This name ensures proper synchronization
     *             among multiple processes or threads accessing the shared
     *             memory.
     * @return An instance of the SharedMemoryManager class.
     */
public:
    SharedMemoryManager(const char * name);

    /**
     * Locks the shared memory to ensure safe and synchronized access across
     * multiple threads or processes. This function uses a mutex to provide
     * thread-safety and prevents race conditions during shared memory
     * operations.
     *
     * This method is designed to be called before performing any operations
     * on the shared memory. The lock remains active until it is explicitly
     * released by calling the corresponding `releaseSharedMemory` method.
     *
     * Note: Misuse of this function, such as failing to release the lock, may
     * lead to deadlocks or blocked access for other threads or processes.
     */
    void lockSharedMemory();

    /**
     * Safely accesses the shared memory under the protection of a mutex.
     *
     * This method ensures thread-safe access to the shared memory segment
     * by utilizing a RAII-style locking mechanism. The lock is automatically
     * released when the scope of the method ends, ensuring safe concurrent
     * operations on the shared memory resource.
     *
     * Note:
     * - Be sure to properly initialize the mutex before calling this method.
     * - This function assumes that the shared memory has been previously
     *   allocated or initialized for safe access.
     */
    void accessSharedMemory();

    /**
     * Releases the lock held on shared memory.
     *
     * This method is responsible for unlocking the shared memory
     * resource previously locked by the `lockSharedMemory()` method.
     * It utilizes a RAII-style lock management mechanism to safely
     * handle concurrency.
     *
     * Thread safety: Ensured through `SharedMemoryMutex`.
     *
     * This method should be called after performing all necessary
     * operations on the shared memory resource to avoid deadlocks
     * or resource contention.
     */
    void releaseSharedMemory();

    /**
     * A mutex object used to provide thread-safe access to shared memory.
     *
     * The `mutex_` variable represents an instance of the
     * `SharedMemoryMutex` class, which is responsible for handling mutual
     * exclusion when accessing shared resources in a multi-threaded
     * environment. It is used within the `SharedMemoryManager` class for
     * locking, unlocking, and ensuring safe operations on shared memory.
     *
     * The `mutex_` is initialized with a unique name and leverages
     * system-level semaphores to manage access contention.
     */
private:
    SharedMemoryMutex mutex_;
};


#endif //SHMEMMGR_H

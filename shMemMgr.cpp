//
// Created by doug on 4/21/25.
//

#include "mwfw2.h"

SharedMemoryManager::SharedMemoryManager(const char * name)
    : mutex_(name) {
    // Create mutex with unique name
}
// SharedMemoryManager::SharedMemoryManager()
//     : mutex_("/fw_shmem_mutex") {
//     // Create mutex with unique name
// }

void SharedMemoryManager::lockSharedMemory() {
    std::lock_guard<SharedMemoryMutex> lock(mutex_);
}

void SharedMemoryManager::accessSharedMemory() {
    // RAII-style locking
    std::lock_guard<SharedMemoryMutex> lock(mutex_);

    // Now you can safely access m_pShMemng
    //m_pShMemng->iSignature++;
    // ... other operations ...
}

void SharedMemoryManager::releaseSharedMemory() {
    // RAII-style unlocking
    std::lock_guard<SharedMemoryMutex> unlock(mutex_);
}

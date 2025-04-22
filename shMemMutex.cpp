//
// Created by doug on 4/21/25.
//

#include "mwfw2.h"

SharedMemoryMutex::SharedMemoryMutex(const char* name) {
    // Create or open a named semaphore
    mutex_ = sem_open(name, O_CREAT, 0644, 1);
    if (mutex_ == SEM_FAILED) {
        throw std::system_error(errno, std::system_category(), "sem_open failed");
    }
}

SharedMemoryMutex::~SharedMemoryMutex() {
    if (mutex_ != SEM_FAILED) {
        sem_close(mutex_);
    }
}

void SharedMemoryMutex::SharedMemoryMutex::lock() {
    if (sem_wait(mutex_) != 0) {
        throw std::system_error(errno, std::system_category(), "sem_wait failed");
    }
}

void SharedMemoryMutex::unlock() {
    if (sem_post(mutex_) != 0) {
        throw std::system_error(errno, std::system_category(), "sem_post failed");
    }
}

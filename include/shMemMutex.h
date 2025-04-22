//
// Created by doug on 4/21/25.
//

#ifndef SHMEMMUTEX_H
#define SHMEMMUTEX_H

class SharedMemoryMutex {
public:
    SharedMemoryMutex(const char* name);

    ~SharedMemoryMutex();

    void lock();

    void unlock();

private:
    sem_t* mutex_;
};



#endif //SHMEMMUTEX_H

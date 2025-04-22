//
// Created by doug on 4/21/25.
//

#ifndef SHMEMMGR_H
#define SHMEMMGR_H

class SharedMemoryManager {
public:
    SharedMemoryManager(const char * name);

    void lockSharedMemory();

    void accessSharedMemory();

    void releaseSharedMemory();

private:
    SharedMemoryMutex mutex_;
};


#endif //SHMEMMGR_H

//
// Created by doug on 5/2/25.
//

#ifndef MUTATIONS_H
#define MUTATIONS_H

#define CFG_MUTEX_NAME           "/fw_shmem_mutex"

class mutations {
public:
    mutations();

};

class muteInt {
    int * m_pInt;
    char m_szMutexName[CFG_MUTEX_MAX_SIZE];
    sem_t* m_mutex_;

public:
    muteInt(const char *,int *);
    int get();
    void put(int);
};

#endif //MUTATIONS_H

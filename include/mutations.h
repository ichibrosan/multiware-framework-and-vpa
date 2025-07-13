/////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/mutations.h   2025-05-02 18:20        //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////

#pragma

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

///////////////////////
// eof - mutations.h //
///////////////////////
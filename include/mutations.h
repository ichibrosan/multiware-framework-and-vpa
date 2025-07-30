////////////////////////////////////////////////////////////////////
// ~/public_html/fw/mutations.h 2025-07-16 08:08 dwg -            //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

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
//
// Created by doug on 5/2/25.
//

#include "mwfw2.h"

#include <mutex>

mutations::mutations() {

}

muteInt::muteInt(const char * pszName,int * pInt) {
    strcpy(m_szMutexName,pszName);
    m_pInt = pInt;
    m_mutex_ = sem_open(pszName,O_CREAT, 0644, 1);
    if (m_mutex_ == SEM_FAILED) {
        throw std::system_error(errno, std::system_category(),
            "sem_open failed");
    }
}

int muteInt::get() {
    sem_wait(m_mutex_);
    int iValue = *m_pInt;
    sem_post(m_mutex_);
    return iValue;
}

void muteInt::put(int value) {
    sem_wait(m_mutex_);
    *m_pInt = value;
    sem_post(m_mutex_);
}
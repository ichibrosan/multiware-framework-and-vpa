//
// Created by doug on 3/23/25.
//

#include "std.h"
#include "mwfw2.h"

shmvars::shmvars() {

}

std::string shmvars::get_string(int index) {
    char szBuffer[1024];
    switch(gpSh->m_pShMemng->shmvar[index].svar_type) {
        case SVAR_TYPE_CHAR:
            return gpSh->m_pShMemng->shmvar[index].svar_value.uChar.data;
        case SVAR_TYPE_INT:
            sprintf(szBuffer,"%d",
                gpSh->m_pShMemng->shmvar[index].svar_value.uInt.data);
            return szBuffer;
        case SVAR_TYPE_DOUBLE:
            sprintf(szBuffer,"%f",
                gpSh->m_pShMemng->shmvar[index].svar_value.uDouble.data);
            return szBuffer;
        default:
            return "ERROR";
    }
}

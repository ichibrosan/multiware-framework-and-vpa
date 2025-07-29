////////////////////////////////////////////////////////////////////
// ~/public_html/fw/shmvars.cpp 2025-07-15 18:16 dwg -            //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////


#include "mwfw2.h"

shmvars::shmvars()
{
}

void shmvars::set(shmvar_index_t index,
                  std::string ssName,
                  std::string ssValue)
{
    std::cout << "set: " << ssName << " " << ssValue << std::endl;
    gpSh->m_pShMemng->shmvar[index].svar_type = SVAR_TYPE_CHAR;
    strcpy(gpSh->m_pShMemng->shmvar[index].svar_name, ssName.c_str());
    strcpy(gpSh->m_pShMemng->shmvar[index].svar_value.uChar.data,
           ssValue.c_str());
    gpSh->m_pShMemng->shmvar[index].svar_status = SVAR_STATUS_OK;
}

void shmvars::set(shmvar_index_t index,
                  std::string ssName,
                  int iValue)
{
    std::cout << "set: " << ssName << " " << iValue << std::endl;
    gpSh->m_pShMemng->shmvar[index].svar_type = SVAR_TYPE_INT;
    strcpy(gpSh->m_pShMemng->shmvar[index].svar_name, ssName.c_str());
    gpSh->m_pShMemng->shmvar[index].svar_value.uInt.data = iValue;
    gpSh->m_pShMemng->shmvar[index].svar_status = SVAR_STATUS_OK;
}

std::string shmvars::get_string(int index)
{
    char szBuffer[1024];
    switch (gpSh->m_pShMemng->shmvar[index].svar_type)
    {
    case SVAR_TYPE_CHAR:
        return gpSh->m_pShMemng->shmvar[index].svar_value.uChar.data;
    case SVAR_TYPE_INT:
        sprintf(szBuffer, "%d",
                gpSh->m_pShMemng->shmvar[index].svar_value.uInt.data);
        return szBuffer;
    case SVAR_TYPE_DOUBLE:
        sprintf(szBuffer, "%f",
                gpSh->m_pShMemng->shmvar[index].svar_value.uDouble.data);
        return szBuffer;
    default:
        return "ERROR";
    }
}

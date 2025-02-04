/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/shared.h 2025/01/18    //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////
// 2025-01-18 04:19 added mkshared function for aux shared segments    //
/////////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_CGISHARED_H
#define MULTIWARE_CGISHARED_H

#include <CSysLog.hpp>

#include "std.h"
#include "fw-limits.h"
#include "CLog.hpp"
extern CLog *gpLog;
#include "osIface.h"
extern osIface * gpOS;
#include "schema.h"
#include "CSysLog.hpp"
#include "vpadDefs.h"

// Used for shared segment signature
// See Douglas Adam, Hitchhiker's Guide et al.
#define UNIVERSAL_ANSWER 42
#define SHARED_ROOT_KEY 0x5164

// See Beginning C++23-Page 97 for usage of enum class
enum class forkproc_control_t {
//    ControlQuiescent,   // uninitialized state
    ControlIdle,
    ControlStep,
    ControlRun,
    ControlTerm
};

/************************************************************
 * A class to provide function and data for handling a shared
 * memory segment.
 ***********************************************************/
class shared {
    int m_smsi;     // shared memory segment identifier
    CSysLog * m_pSysLog;
public:
    /**
     * The default CTOR establishes addressability to the ShMemNG
     */
    shared();

    /**
     * mkshared is for establishing addressability to other shared segments
     * @param keyparm The shared segment key
     * @param sizeparm The size of the shared segment
     * @return Returns a void * pointer to the shared segment
     */
    void * mkshared(key_t keyparm,size_t sizeparm);

    int get_smsi() const;

    void decode_shmget_errno(int);

    void decode_shmat_errno(int);

    ~shared();

#include "shmemng.h"
//MFW_SHMEMNG_T * pShMemNG;
};

#endif //MULTIWARE_CGISHARED_H

///////////////////////
// eof - shared.h //
///////////////////////

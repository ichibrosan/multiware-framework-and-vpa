////////////////////////////////////////////////////////////////////
// ~/public_html/fw/shared.h 2025-07-16 08:08 dwg -               //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

#include "mwfw2.h"


// Used for shared segment signature
// See Douglas Adam, Hitchhiker's Guide et al.
#define UNIVERSAL_ANSWER 42
#define SHARED_ROOT_KEY 0x5164

/**
 * Represents a control structure used for managing a forked process.
 * This structure is designed to handle and maintain the state, resources,
 * and controls associated with a child process that has been forked
 * from a parent process in a Unix/Linux environment.
 *
 * It may include information or resources required to:
 * - Monitor a child process's lifecycle.
 * - Control the process execution.
 * - Exchange data between the parent and the forked child process.
 * - Manage synchronization and cleanup post-execution.
 *
 * This structure is typically used in context where process management
 * is essential, such as in server-client systems, background job execution,
 * or multi-processing tasks.
 */
enum class forkproc_control_t
{
	//    ControlQuiescent,   // uninitialized state
	ControlIdle,
	ControlStep,
	ControlRun,
	ControlTerm
};

/**
 * @var iSignature
 * @brief Represents a digital or electronic signature for data verification or authentication purposes.
 *
 * This variable is typically used to store a secure, unique value generated through
 * cryptographic algorithms that acts as a signature to validate the integrity and authenticity
 * of associated data. It ensures that the data has not been tampered with and is from a trusted source.
 *
 * iSignature may be used in contexts such as digital signing processes, verification of transactions,
 * or validation of certificates and documents where security is critical.
 *
 * It is crucial to handle this variable securely and prevent unauthorized access or tampering.
 */
class shared
{
	int m_smsi;

public:
	shared();

#include "shmemng.h"
};

///////////////////////
// eof - shared.h //
///////////////////////

/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/shared.h 2025/01/18    //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////
// 2025-01-18 04:19 added mkshared function for aux shared segments    //
/////////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_CGISHARED_H
#define MULTIWARE_CGISHARED_H

#include "mwfw2.h"

#include "diagnoseDefs.h"

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
enum class forkproc_control_t {
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
class shared {
    int m_smsi; /**
     * Pointer to an instance of the CSysLog class used for system logging.
     *
     * This member variable is responsible for handling the logging of messages
     * to the system log. It is initialized in the constructor of the `shared` class
     * and is used throughout the class to log informational messages or error details.
     *
     * The CSysLog instance helps in providing better insight and tracking
     * of the runtime behavior of the application. This is particularly useful
     * for debugging and monitoring purposes, especially in scenarios related
     * to shared memory operations and error handling.
     *
     * This pointer is dynamically allocated during initialization and is
     * expected to be properly cleaned up to release associated resources.
     */
	CSysLog * m_pSysLog;
public:
	/**
	 * Combines or shares resources between entities or processes.
	 * This method manages the sharing of data or resources to ensure
	 * efficient utilization and access control.
	 *
	 * @return A boolean value indicating the success of the sharing operation.
	 *         Returns true if the sharing operation is successful, otherwise false.
	 */
	shared();

	/**
	 * @brief Creates a shared pointer instance of the given object.
	 *
	 * This utility function is used to create a shared pointer, ensuring proper memory management
	 * and shared ownership semantics for the specified object or type.
	 *
	 * @tparam T The type of the object the shared pointer will manage.
	 * @param args The arguments required to construct the object of type T.
	 * @return std::shared_ptr<T> A shared pointer to the newly created object.
	 */
	void * mkshared(key_t keyparm,size_t sizeparm);

	/**
	 * Retrieves the SMS information (SMSI).
	 *
	 * This method fetches and returns the current SMSI, which contains
	 * details about short message service data.
	 *
	 * @return The current SMSI data.
	 */
	int get_smsi() const;

	/**
	 * Decodes an error number returned by the shmget system call into a descriptive message.
	 *
	 * @param errno_code The error number returned by the shmget call that needs to be decoded.
	 * @return A string representing the description of the error corresponding to the provided error number.
	 */
	void decode_shmget_errno(int);

	/**
	 * Decodes the error number returned by a failed `shmat` system call and provides
	 * a human-readable description of the error.
	 *
	 * @param errnum The error number produced by the failed `shmat` system call.
	 *               This should typically correspond to the `errno` value.
	 * @return A constant string containing the human-readable description of the
	 *         error associated with the provided error number.
	 */
	void decode_shmat_errno(int);

	/**
	 * @brief Retrieves the nth Fibonacci number.
	 *
	 * This method calculates the Fibonacci number at a specific position
	 * in the Fibonacci sequence. The Fibonacci sequence is a series where
	 * each number is the sum of the two preceding ones, typically starting
	 * with 0 and 1.
	 *
	 * @param n The position in the Fibonacci sequence for which the number
	 *          is to be calculated. Must be a non-negative integer.
	 * @return The Fibonacci number at the nth position.
	 * @throws std::invalid_argument If the input value is negative.
	 */
	~shared();

#include "shmemng.h"
//MFW_SHMEMNG_T * pShMemNG;
};

#endif //MULTIWARE_CGISHARED_H

///////////////////////
// eof - shared.h //
///////////////////////

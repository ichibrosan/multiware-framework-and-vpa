////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/diagnose.cpp  2025/03/23                 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#include "std.h"
#include "include/diagnose.h"


/**
 * @brief An array containing the names of the diagnostic request functions.
 *
 * The array maps diagnostic request function identifiers to their respective
 * string representations. The identifiers correspond to the constants defined
 * in the DIAGNOSE_REQ_FUNCS_T enum in diagnoseDefs.h. This array allows
 * diagnostic systems to interpret and log request function types in a
 * human-readable manner.
 *
 * Values:
 * - "NONE": Represents no diagnostic request.
 * - "VERSION": Retrieves version information.
 * - "AUTH": Handles authentication requests.
 * - "PARMS": Retrieves or sets parameters.
 * - "STATUS": Provides status information.
 * - "TERM": Terminates diagnostic requests.
 * - "GETSHM": Retrieves shared memory information.
 */
const char * diagnose_req_names[] =
    { "NONE","VERSION", "AUTH", "PARMS", "STATUS", "TERM", "GETSHM" };

/**
 * @brief Array of string representations for the diagnose type enum values.
 *
 * This array provides human-readable names for the values defined in the
 * DIAGNOSE_TYPES_T enumeration. It is intended to map each diagnosis type
 * to its corresponding string name.
 *
 * @note The order of the strings in this array must match the order of the
 *       enumeration values defined in DIAGNOSE_TYPES_T to ensure correctness.
 *
 * @see DIAGNOSE_TYPES_T
 */
const char * diagnose_type_names[] =
    { "None","Int","String","Float","Bool" };

/**
 * @brief Constructor for the `diagnose` class.
 *
 * This function initializes the `diagnose` object by setting up the necessary
 * parameters for performing a remote procedure call (RPC) to diagnose a node
 * identified by its IP address. It configures the RPC URL, port, method, and
 * format, and attempts to retrieve an authentication token from the remote server.
 *
 * @param ssNodeIP A string containing the IP address of the target node for diagnosis.
 *
 * The function accomplishes the following tasks:
 * - Logs information about the RPC client and method using the system logger.
 * - Constructs the RPC URL using the protocol, IP, and port.
 * - Executes the RPC call using the configured method, format, and parameters.
 * - Retrieves and stores the authentication token for further communication.
 *
 * @throws std::exception If the RPC client encounters an error during execution.
 * @throws unknown exception If an unexpected error occurs.
 */
diagnose::diagnose(std::string ssNodeIP) {
    std::string ssValueRetcode;

    m_ssNodeIP = ssNodeIP;
    m_ssFormat = "iiisiss";
    m_ssMethod = "diagnose";
    sprintf(m_szPort,"%d",VPA_PORT);

    char szLog[256];
    sprintf(szLog,
    "vpa: Client RPC: Addr=%s Func=%s,P2=%s,P3Type=%s,"
          "P3=%s,P4Type=%s,P4=%s,Auth=%s",
            m_ssNodeIP.c_str(),
            diagnose_req_names[DIAGNOSE_REQ_AUTH],
            diagnose_req_names[DIAGNOSE_REQ_NONE],
            diagnose_type_names[DIAGNOSE_TYPE_NONE],"",
            diagnose_type_names[DIAGNOSE_TYPE_NONE],"",VPA_RPC_PSK);
    gpSysLog->loginfo(szLog);
    //std::cout << szLog << std::endl;

    m_ssUrl = gpSh->m_pShMemng->szProtocol;
    m_ssUrl.append(m_ssNodeIP);
    m_ssUrl.append(":");
    m_ssUrl.append(m_szPort);
    m_ssUrl.append("/RPC2");

    try {
        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;
        myClient.call(  m_ssUrl,m_ssMethod,m_ssFormat,&result,
                         DIAGNOSE_REQ_AUTH, DIAGNOSE_REQ_NONE,
                         DIAGNOSE_TYPE_NONE,"",DIAGNOSE_TYPE_NONE,"",
                         VPA_RPC_PSK);

        ssValueRetcode = xmlrpc_c::value_string(result);
        //std::cout << "Auth Token: " << ssValueRetcode << std::endl;
        m_ssAuth = ssValueRetcode;
    } catch (std::exception const& e) {
        std::cerr << "Client threw error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Client threw unexpected error." << std::endl;
    }
}

/**
 * @brief Executes a diagnostic call using the given request parameters.
 *
 * This method performs a remote procedure call (RPC) using the data provided
 * in the `diagnose_request_t` structure. It constructs a log entry with the
 * details of the request, sends the RPC query via an XML-RPC client, and
 * captures the remote response. In case of an exception during the RPC
 * execution, error details are logged.
 *
 * @param request The diagnostic request containing the parameters for the
 *                RPC operation.
 *        - `request.eReqFunc`: Specifies the diagnostic request function
 *                              to be called.
 *        - `request.iParm2`: An integer parameter passed to the remote
 *                            function.
 *        - `request.eParm3Type`: The type of the third parameter.
 *        - `request.szParm3`: The third parameter value.
 *        - `request.eParm4Type`: The type of the fourth parameter.
 *        - `request.szParm4`: The fourth parameter value.
 *        - `request.szAuth`: Authentication information.
 *
 * @return A string representing the result from the remote procedure call.
 *         If an exception occurs, an error is logged, and the return
 *         value may be undefined.
 */
std::string diagnose::call(diagnose_request_t request) {
    std::string ssValueRetcode;

    char szLog[256];
    sprintf(szLog,
    "vpa: Client RPC: Addr=%s Func=%s,P2=%d,P3Type=%s,"
          "P3=%s,P4Type=%s,P4=%s,Auth=%s",
            m_ssNodeIP.c_str(),
            diagnose_req_names[request.eReqFunc],  request.iParm2,
            diagnose_type_names[request.eParm3Type],request.szParm3,
            diagnose_type_names[request.eParm4Type],request.szParm4,
            m_ssAuth.c_str());

    try {
        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;
        myClient.call(  m_ssUrl,m_ssMethod,
                        m_ssFormat,
                        &result,
                         request.eReqFunc,  request.iParm2,
                         request.eParm3Type,request.szParm3,
                         request.eParm4Type,request.szParm4,
                         m_ssAuth.c_str());
        ssValueRetcode = xmlrpc_c::value_string(result);
    } catch (std::exception const& e) {
        std::cerr << "Client threw error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Client threw unexpected error." << std::endl;
    }
    return ssValueRetcode;
}
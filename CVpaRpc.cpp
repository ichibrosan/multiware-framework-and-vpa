////////////////////////////////////////////////////////////////////
// ~/public_html/fw/CVpaRpc.cpp 2025-07-15 18:16 dwg -            //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * @brief Constructor for the CVpaRpc class.
 *
 * Initializes an instance of the CVpaRpc class and sets up the initial authentication request
 * for the VPA RPC client. The function populates the authentication request structure with the
 * specified version, size, function type, and pre-shared key (PSK). It then initializes the client
 * communication with the VPA RPC service using the provided host and service parameters.
 *
 * @param ssHost A string representing the host name or IP address for the VPA RPC client.
 * @param ssService A string representing the service name or identifier for the VPA RPC client.
 */
CVpaRpc::CVpaRpc(std::string ssServer, std::string ssService)
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    m_ssSvr = ssServer;
    m_ssSvc = ssService;

    m_vparpc_request_auth.eVersion = VPARPC_VERSION_1;
    m_vparpc_request_auth.nSize = sizeof(m_vparpc_request_auth);
    m_vparpc_request_auth.eFunc = VPARPC_FUNC_GET_AUTH;
    strcpy((char*)m_vparpc_request_auth.szPSK,CFG_VPA_RPC_PSK);
    gpVpaRpc->client(m_ssSvr, m_ssSvc,
                     &m_vparpc_request_auth,
                     sizeof(vparpc_request_auth_t)); // Use struct size
}

/**
 * Retrieves the authentication string stored in the m_vparpc_request_auth structure.
 *
 * @return A std::string containing the authentication data.
 */
std::string CVpaRpc::get_auth()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    std::string ssReturn = m_vparpc_request_auth.szAuth;
    return (ssReturn);
}

/**
 * Retrieves the version information for the VpaRpc system.
 *
 * This function initializes the version request structure, including
 * setting the version, size, and function identifier, and copies the
 * authentication data. It then sends the version request to the VpaRpc
 * system using the `client` method and retrieves the version.
 *
 * @return A string containing the version information of the VpaRpc system.
 */
std::string CVpaRpc::get_version()
{
    gpSysLog->loginfo("CVpaRpc::get_version (CVpaRpc.cpp#58)");

    m_vparpc_request_version.eVersion = VPARPC_VERSION_1;
    m_vparpc_request_version.nSize = sizeof(m_vparpc_request_version);
    m_vparpc_request_version.eFunc = VPARPC_FUNC_VERSION;
    strcpy((char*)m_vparpc_request_version.szAuth,
           m_vparpc_request_auth.szAuth);
    gpVpaRpc->client(m_ssSvr, m_ssSvc,
                     &m_vparpc_request_version,
                     sizeof(vparpc_request_version_t)); // Use struct size
    return (m_vparpc_request_version.szVersion);
}

std::string CVpaRpc::get_version_version()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    std::string ssReturn = m_vparpc_request_version.szVersion;
    return (ssReturn);
}


/**
 * Executes a lookup request using the CVpaRpc interface.
 *
 * This function prepares a `vparpc_request_lookup_t` structure, populates it with
 * necessary lookup request data such as authorization, username, and password, and
 * sends the request using the client method. The initial handle value is set to -999
 * for debugging purposes. The response from the client call updates the request
 * object with the handle and status of the operation.
 *
 * Logging is done at key stages of the operation, such as before sending the request
 * and after receiving a response. This includes logging the username, password,
 * initial handle value, final handle value, and status.
 *
 * @return The handle value from the `vparpc_request_lookup_t` structure after the
 *         client call completes.
 */
int CVpaRpc::get_lookup()
{
    here;
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    m_vparpc_request_lookup.eVersion = VPARPC_VERSION_1;
    m_vparpc_request_lookup.nSize = sizeof(m_vparpc_request_lookup);
    m_vparpc_request_lookup.eFunc = VPARPC_FUNC_LOOKUP;
    strcpy((char*)m_vparpc_request_lookup.szAuth, m_vparpc_request_auth.szAuth);
    strcpy(m_vparpc_request_lookup.szUsername, "doug");
    strcpy(m_vparpc_request_lookup.szPassword, "melange");

    // Initialize iHandle to a known value for debugging
    m_vparpc_request_lookup.iHandle = -999;

    // Log the request details
    char szLogger[128];
    sprintf(szLogger,
            "Sending lookup request - Username: %s, Password: %s, Initial Handle: %d",
            m_vparpc_request_lookup.szUsername,
            m_vparpc_request_lookup.szPassword,
            m_vparpc_request_lookup.iHandle);
    gpSysLog->loginfo(szLogger);

    gpVpaRpc->client(m_ssSvr, m_ssSvc,
                     &m_vparpc_request_lookup,
                     sizeof(vparpc_request_lookup_t)
    );

    // Log the response
    sprintf(szLogger, "Received lookup response - Handle: %d, Status: %d",
            m_vparpc_request_lookup.iHandle,
            m_vparpc_request_lookup.eStatus);

    //std::cout << "handle: " << m_vparpc_request_lookup.iHandle << std::endl;

    return (m_vparpc_request_lookup.iHandle);
}

/**
 * Populates the `m_vparpc_request_creds` structure with required credential details
 * and sends a client RPC request.
 *
 * The function sets the version, size, and function type for the `m_vparpc_request_creds`
 * structure. It also copies authentication data and a handle from existing member variables.
 * These values are then used as part of an RPC request.
 *
 * This method sends the request to the RPC client with the service name "daphne" and module
 * name "vpa". The request payload is specified using the `vparpc_request_creds_t` structure.
 *
 * Note: The structure size is calculated dynamically using `sizeof` to ensure the correct
 * size of the data block being transferred.
 */
void CVpaRpc::get_creds()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    m_vparpc_request_creds.eVersion = VPARPC_VERSION_1;
    m_vparpc_request_creds.nSize = sizeof(m_vparpc_request_creds);
    m_vparpc_request_creds.eFunc = VPARPC_FUNC_CREDS;
    strcpy((char*)m_vparpc_request_creds.szAuth, m_vparpc_request_auth.szAuth);
    m_vparpc_request_creds.iHandle = m_vparpc_request_lookup.iHandle;
    gpVpaRpc->client(m_ssSvr, m_ssSvc,
                     &m_vparpc_request_creds,
                     sizeof(vparpc_request_creds_t)); // Use struct size
}

/**
 * Returns the username associated with the credentials for the current RPC request.
 *
 * This method retrieves the stored authentication username from the internal
 * structure `m_vparpc_request_creds` and returns it as a string.
 *
 * @return A string representing the username used for authentication.
 */
std::string CVpaRpc::get_creds_username()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    std::string ssReturn = m_vparpc_request_creds.szAuthUserName;
    return (ssReturn);
}

/**
 * @brief Retrieves the first name from the authentication credentials.
 *
 * This function accesses the member variable containing the authentication
 * credentials and extracts the first name. The extracted value is returned
 * as a string.
 *
 * @return A std::string containing the first name from the authentication
 * credentials.
 */
std::string CVpaRpc::get_creds_firstname()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    std::string ssReturn = m_vparpc_request_creds.szAuthFirstName;
    return (ssReturn);
}

/**
 * Retrieves the last name credentials stored in the internal request structure.
 *
 * @return A string containing the last name from the credentials.
 */
std::string CVpaRpc::get_creds_lastname()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    std::string ssReturn = m_vparpc_request_creds.szAuthLastName;
    return (ssReturn);
}

/**
 * Retrieves the authentication UUID from the current VPA RPC request credentials.
 *
 * @return A string containing the authentication UUID.
 */
std::string CVpaRpc::get_creds_auth()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    std::string ssReturn = m_vparpc_request_creds.szAuthUUID;
    return (ssReturn);
}

/**
 * @brief Retrieves the credential authorization level.
 *
 * This function retrieves the authorization level provided in the
 * `m_vparpc_request_creds` member variable and returns it as a string.
 *
 * @return A string containing the credential authorization level.
 */
std::string CVpaRpc::get_creds_level()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    std::string ssReturn = m_vparpc_request_creds.szAuthLevel;
    return (ssReturn);
}

void CVpaRpc::get_urls()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    m_vparpc_request_urls.eVersion = VPARPC_VERSION_1;
    m_vparpc_request_urls.nSize = sizeof(m_vparpc_request_urls);
    m_vparpc_request_urls.eFunc = VPARPC_FUNC_URLS;
    strcpy((char*)m_vparpc_request_urls.szAuth, m_vparpc_request_auth.szAuth);
    gpVpaRpc->client(m_ssSvr, m_ssSvc,
                     &m_vparpc_request_urls,
                     sizeof(vparpc_request_urls_t)); // Use struct size
}

std::string CVpaRpc::get_urls_ip()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    std::string ssReturn = m_vparpc_request_urls.szIP;
    return (ssReturn);
}

std::string CVpaRpc::get_urls_cgiroot()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    std::string ssReturn = m_vparpc_request_urls.szCgiRoot;
    return (ssReturn);
}

std::string CVpaRpc::get_urls_stylesroot()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    std::string ssReturn = m_vparpc_request_urls.szStylesRoot;
    return (ssReturn);
}

///////////////////////
// eof - CVpaRpc.cpp //
///////////////////////

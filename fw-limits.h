//////////////////////////////////////////////////////////////////////////
// daphme.goodall.com:/home/doug/public_html/fw/limits.h 2025/01/10     //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.   //
//////////////////////////////////////////////////////////////////////////

#ifndef HTML_LIMITS_H
#define HTML_LIMITS_H

/**
 * I was unable to locate system determined limits for these items
 * so I set them to the most conservative values I could, according
 * to best practices.
 */

#define DNS_FQDN_SIZE_MAX  253
#define HTML_TAG_NAME_SIZE_MAX 1024
#define INET_PROT_NAME_MAX 32
#define INET_URL_SIZE_MAX  2083
#define INET_URL_PROT_SIZE_MAX 32
#define IPV4_ADDR_SIZE_MAX (sizeof("255.255.255.255")+1)
#define UT_NAMESIZE 32
#define  UT_TIMESIZE 32
#define UUID_SIZE   (36+1)
#define NUM_PASSWDS 2
#define USERNAME_SIZE_MAX UT_NAMESIZE
#define MAX_USERS 6
#define VPA_PORT 5164
#define HANDLE_NA 0
#define ZERO_TERMINATOR_SIZE 1
#endif //HTML_LIMITS_H

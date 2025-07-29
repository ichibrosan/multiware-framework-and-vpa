////////////////////////////////////////////////////////////////////
// ~/public_html/fw/fw-limits.h 2025-07-16 08:08 dwg -            //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

/**
 * I was unable to locate system determined limits for these items
 * so I set them to the most conservative values I could, according
 * to best practices.
 */

#define VPA_VERSION_SIZE_MAX 32
#define DNS_FQDN_SIZE_MAX  253
#define HTML_TAG_NAME_SIZE_MAX 1024
#define INET_PROT_NAME_MAX 32
#define INET_URL_SIZE_MAX  2083
#define INET_URL_PROT_SIZE_MAX 32
#define IPV4_ADDR_SIZE_MAX (sizeof("255.255.255.255")+1)
#define USERNAME_SIZE_MAX UT_NAMESIZE
#define UT_NAMESIZE 32
#define UT_TIMESIZE 32
#define UUID_SIZE   (36+1)
#define DATE_LENGTH 14
#define COLOR_SIZE_MAX 24
#define ZERO_TERMINATOR_SIZE 1
#define VERSION_SIZE_MAX (sizeof("YYYY.MM.DD.HH")+1)
#define PASSWORD_SIZE_MAX 512  // Based on PAM_MAX_RESP_SIZE

#define FQFS_SIZE_MAX 128
#define SECONDS_PER_MIN 60
#define SECONDS_PER_HOUR (SECONDS_PER_MIN * 60)
#define SECONDS_PER_DAY (SECONDS_PER_HOUR * 24)
#define SECONDS_PER_WEEK (SECONDS_PER_DAY * 7)

#define LOGIN_TIMEOUT_SECONDS SECONDS_PER_HOUR


///////////////////////
// eof - fw-limits.h //
///////////////////////

////////////////////////////////////////////////////////////////////
// ~/public_html/fw/shmvars.h 2025-07-16 08:08 dwg -              //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

#define CHARDATA_SIZE_MAX 2083
#define SHMVAR_NAME_SIZE_MAX 32
#define SHMVAR_VALUE_SIZE_MAX 2083

enum svar_type_t
{
    SVAR_TYPE_INT,
    SVAR_TYPE_DOUBLE,
    SVAR_TYPE_LONG,
    SVAR_TYPE_CHAR
};

enum svar_status_t
{
    SVAR_STATUS_OK,
    SVAR_STATUS_ERROR
};

enum shmvar_index_t
{
    SV_RMAJ,
    SV_RMIN,
    SV_RREV,
    SV_RBLD,
    SV_RSTRING,
    SV_RSHORT,
    SV_RLONG,
    SV_RDATE,
    SV_RTIME,
    SV_RBUILD,
    SV_RTYPE,
    SV_RARCH,
    SV_ROS,
    SV_RHOST,
    SV_RUSER,
    SV_RDOMAIN,
    SV_RIP,
    SV_RMAC,
    SV_RCPU,
    SV_RCOMMENT,
    SHMVAR_COUNT
};

typedef struct shmvar_t
{
    char svar_name[SHMVAR_NAME_SIZE_MAX];
    int svar_type;
    int svar_status;

    union
    {
        struct
        {
            int data;
        } uInt;

        struct
        {
            double data;
        } uDouble;

        struct
        {
            long data;
        } uLong;

        struct
        {
            char data[CHARDATA_SIZE_MAX];
        } uChar;
    } svar_value;
};


class shmvars
{
public:
    shmvars();
    void set(
        shmvar_index_t index, std::string ssName, std::string ssValue);
    void set(
        shmvar_index_t index, std::string ssName, int iValue);

    std::string get_string(int index);
};


/////////////////////
// eof - shmvars.h //
/////////////////////

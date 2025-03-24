//
// Created by doug on 3/23/25.
//

#ifndef SHMVARS_H
#define SHMVARS_H

#define CHARDATA_SIZE_MAX 2083
#define SHMVAR_NAME_SIZE_MAX 32
#define SHMVAR_VALUE_SIZE_MAX 2083

enum svar_type_t {
    SVAR_TYPE_INT,
    SVAR_TYPE_DOUBLE,
    SVAR_TYPE_LONG,
    SVAR_TYPE_CHAR
};

enum svar_status_t {
    SVAR_STATUS_OK,
    SVAR_STATUS_ERROR
};

enum shmvar_index_t {
    KAWABUNGA,
    KAWABUCHA
};

typedef struct shmvar_t {
    char               svar_name[SHMVAR_NAME_SIZE_MAX];
    enum svar_type_t   svar_type;
    enum svar_status_t svar_status;
    union {
        struct {
            int data;
        } uInt;
        struct {
            double data;
        } uDouble;
        struct {
            long data;
        } uLong;
        struct {
            char data[CHARDATA_SIZE_MAX];
        } uChar;
    }                 svar_value;
};


class shmvars {
public:
    shmvars();
    std::string get_string(int index);
};



#endif //SHMVARS_H

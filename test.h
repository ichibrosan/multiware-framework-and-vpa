/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/test.h 2025/01/10      //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#ifndef FW_TEST_H
#define FW_TEST_H

#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
using namespace cgicc;
#include "osIface.h"
extern osIface *gpOS;
#include "test.h"
#include "CLog.hpp"
#include "shared.h"
extern shared  *gpSh;


enum {
    TEST0 = 1<<0,
    TEST1 = 1 << 1,
    TEST2 = 1 << 2,
    TEST2_1 = 1 << 3,
    TEST3 = 1 << 4,
    TEST4 = 1 << 5,
    TEST5 = 1 << 6,
    NUM_TESTS = 7
};

class test {
    char m_szLogFQFS[FILENAME_MAX];
    CSysLog * m_pSysLog;
    bool m_bDebug;
    
public:

    // int m_tests_processed_bits;
    // int m_tests_passed_bits;
    // int m_tests_failed_bits;
    // int m_tests_skipped_bits;
    // int m_num_tests_processed;
    // int m_num_tests_skipped;
    // int m_num_tests_passed;
    // int m_num_tests_failed;

    test(bool bDebug, bool bCGI);

    bool runMandatoryTests(bool bCGI);

    bool runAllTests(bool bCGI);

    void logHistograms();

    bool test0();                           // verify shared env values

    bool test1();

    bool test2();

    bool test2_1(bool);

    bool test3(bool bDebug, bool bCGI);

    bool test4(bool bDebug);

    bool test5(const char *, const char *, bool bDebug);

    ~test();
};


//system("curl http://daphne.goodall.com/~doug/fw/html/fw-test1.html "
//"> /tmp/fw-test1.stdout 2> /tmp/fw-test1.stderr");

#endif //FW_TEST_H

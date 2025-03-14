////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/fw-test4.cpp 2025/02/19                  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"


/**
 * @brief Entry point of the program.
 *
 * This function initializes the program, outputs HTTP content type
 * and a simple "Hello World!!" message to the console.
 *
 * @return An integer value of 0 indicating successful program execution.
 */
int main() {
    //mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    std::cout << "Content-type:\ttext/html\n\n" << std::endl;
    // Cgicc *pCgi = new Cgicc();
    //std::string ssServerSoftware;
    //ssServerSoftware = gpCgi->getEnvironment().getServerSoftware();
    std::cout << "Hello World!!" << std::endl;
    return 0;
}

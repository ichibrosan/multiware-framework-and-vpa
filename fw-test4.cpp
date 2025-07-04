////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/fw-test4.cpp 2025/02/19                  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"

/* The purpose of the fw-test4 program is to test the ability of the
 * framework  to execute a CGI script and verify the output to assure
 * the apache server is present, configured and running.
 */

/**
 * @brief Entry point of the program.
 *
 * This function initializes the program, outputs HTTP content type
 * and a simple "Hello World!!" message to the console.
 *
 * @return An integer value of 0 indicating successful program execution.
 */
int main() {
    std::cout << "Content-type:\ttext/html\n\n" << std::endl;
    std::cout << "Hello World!!" << std::endl;
    return 0;
}

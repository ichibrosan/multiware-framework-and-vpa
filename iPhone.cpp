//
// Created by doug on 7/18/25.
//

#include "mwfw2.h"
#include "include/iPhone.h"
#include <cstdlib>

int main()
{
    auto pMwFw = std::make_unique<mwfw2>(__FILE__, __FUNCTION__);
    std::cout << "Content-type: text/html\n\n" << std::endl;
    
    // Set the DISPLAY environment variable
    setenv("DISPLAY", ":0", 1);  // or ":0.0" depending on your setup
    
    //std::string command = "celluloid /var/www/html/2025-07-18-182734.webm";
    //std::string command = "/usr/bin/firefox ";
    std::string command = "/usr/bin/opera ";

    //command.append("http://daphne/2025-07-18-182734.webm");

    command.append("http://daphne/diane-needs-help.html");
    //std::cout << command << std::endl;
    
    int result = system(command.c_str());
    // if (result != 0) {
    //     std::cerr << "Firefox failed to launch, exit code: " << result << std::endl;
    // }
    std::cout << "Message sent";

    return 0;
}
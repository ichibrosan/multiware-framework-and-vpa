////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/login.cpp 2025/02/219                    //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

// Function to read password without echoing to terminal
std::string getPassword()
{
    std::string password;
    char ch;

    // Read characters one by one
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (ch == '\b' || ch == 127)
        {
            // Handle backspace
            if (!password.empty())
            {
                password.pop_back();
                std::cout << "\b \b";
                // Move cursor back, print space, move back again
                std::cout.flush();
            }
        }
        else
        {
            password += ch;
            std::cout << '*'; // Show asterisk for each character
            std::cout.flush();
        }
    }

    return password;
}

/**************************************************************
 * Display Retro Header Information IBM 5150 Monochrome style *
 **************************************************************/
void sine()
{
    auto* pWin = new window();
    gpSemiGr->cosmetics(
        SRUL, SRUR, SRLL, // Corner characters: ┌ ┐ └ ┘
        SRLR, SVSR, SVSL, // Right corner and separators
        SH, SV); // Horizontal ─ and vertical │ lines
    char szVersion[64];
    sprintf(szVersion, "Virtual Protocol Adapter vpalogin Utility "
            "Ver %d.%d.%d.%d",RMAJ,RMIN,RREV,RBLD);
    pWin->set_title(szVersion);
    std::string ssCopr = "  Copyright ";
    ssCopr.append("(c)"); // Append copyright symbol for compatibility
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");
    pWin->add_row(ssCopr);
    pWin->render();
}

int main()
{
    auto gpMwFw = new mwfw2(__FILE__, __FUNCTION__);
    sine();
    std::string username;
    std::string password;

    // Prompt for username
    std::cout << "Username: ";
    std::getline(std::cin, username);

    // Prompt for password (hidden input)
    std::cout << "Password: ";

    // Disable buffering and echo for password input
    struct termios oldTermios, newTermios;
    tcgetattr(STDIN_FILENO, &oldTermios);
    newTermios = oldTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);

    password = getPassword();

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);

    std::cout << std::endl; // Add newline since password input doesn't echo

    // Validate that both fields are not empty
    if (username.empty() || password.empty())
    {
        std::cerr << "Error: Username and password cannot be empty." <<
            std::endl;
        return 1;
    }

    // Display confirmation (don't show the actual password)
    std::cout << "Login attempt for user: " << username << std::endl;

    /**
      * @brief Initialize and parse the password database
      *
      * Creates a CSV reader instance for the passwd.csv file and parses
      * the user credential data into memory for authentication processing.
      */
    gpCsv = new readCsv("passwd.csv");
    gpCsv->parseData();

    /**
     * @brief Authenticate user credentials
     *
     * Performs username/password lookup against the parsed CSV data.
     * Returns a handle (index) to the user record if authentication succeeds,
     * or RETURN_FAILURE if authentication fails.
     */
    int handle =
        gpPassword->lookup_username_password(username, password);

    // Here you would typically authenticate the user
    // For demonstration, just show success message
    std::cout << "Authentication data received successfully." << std::endl;

    std::cout << "User handle: " << handle << std::endl;

    if (handle < 4)
    {
        std::cout << "User is not a valid member of the VPA." << std::endl;
    }
    else
    {
        std::cout << "User is a valid member of the VPA." << std::endl;
    }
    return 0;
}

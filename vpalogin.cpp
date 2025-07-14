////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/login.cpp 2025/02/219                    //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <cstdio>

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

int main()
{
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

    // Here you would typically authenticate the user
    // For demonstration, just show success message
    std::cout << "Authentication data received successfully." << std::endl;

    return 0;
}

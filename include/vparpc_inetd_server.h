#include <iostream>
#include <unistd.h>

const int BUFFER_SIZE = 4096;

int main() {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    // Since xinetd handles the connection, we can directly use
    // standard input/output for communication
    while ((bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        // Echo back the received data
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    return 0;
}
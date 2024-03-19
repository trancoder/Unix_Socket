#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

int main() {
    // Create a local socket
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Error creating socket\n";
        return 1;
    }

    // Set up the address
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/mysocket");  // Use the same socket file path as the server

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        std::cerr << "Error connecting to server\n";
        close(sockfd);
        return 1;
    }

    // Receive data
    char buffer[1024];
    int bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        std::cerr << "Error receiving data\n";
        close(sockfd);
        return 1;
    }

    // Print received data
    std::cout << "Received: " << buffer << std::endl;

    // Close socket
    close(sockfd);

    return 0;
}

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
    strcpy(addr.sun_path, "/tmp/mysocket");  // Use a unique socket file path

    // Bind the socket to the address
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        std::cerr << "Error binding socket\n";
        close(sockfd);
        return 1;
    }

    // Listen for incoming connections
    listen(sockfd, 1);

    // Accept a connection
    int client_sockfd = accept(sockfd, nullptr, nullptr);
    if (client_sockfd == -1) {
        std::cerr << "Error accepting connection\n";
        close(sockfd);
        return 1;
    }

    // Create a MyStruct instance
    MyStruct myData = {1, 3.14, "Struct Example"};

    // Serialize the struct into a byte array
    char serializedData[sizeof(MyStruct)];
    std::memcpy(serializedData, &myData, sizeof(MyStruct));

    // Send the serialized data
    send(client_sockfd, serializedData, sizeof(serializedData), 0);

    // Close sockets
    close(client_sockfd);
    close(sockfd);

    return 0;
}

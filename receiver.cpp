#include <iostream>
#include <boost/interprocess/ipc/message_queue.hpp>

// Define your struct
struct MyStruct {
    int value1;
    float value2;
    char message[100];
};

int main() {
    using namespace boost::interprocess;

    // Open the message queue
    message_queue mq(open_only, "my_message_queue");

    // Receive data from the message queue into the struct
    MyStruct receivedData;
    size_t recvSize;
    unsigned int priority;
    mq.receive(&receivedData, sizeof(MyStruct), recvSize, priority);

    // Print received data
    std::cout << "Received data in the second app:\n";
    std::cout << "Value 1: " << receivedData.value1 << '\n';
    std::cout << "Value 2: " << receivedData.value2 << '\n';
    std::cout << "Message: " << receivedData.message << '\n';

    return 0;
}


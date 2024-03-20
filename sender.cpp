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

    // Create or open the message queue
    message_queue mq(open_or_create, "my_message_queue", 100, sizeof(MyStruct));

    // Create an instance of your struct
    MyStruct data;
    data.value1 = 42;
    data.value2 = 3.14f;
    std::strcpy(data.message, "Hello from the first app!");

    // Send the struct data to the message queue
    mq.send(&data, sizeof(MyStruct), 0);

    return 0;
}


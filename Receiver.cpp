#include <boost/archive/binary_iarchive.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

void receiveStruct() {
    // Receive the serialized data using Boost Interprocess Message Queue
    boost::interprocess::message_queue mq(
        boost::interprocess::open_or_create,
        "my_message_queue",
        100,
        sizeof(char) * sizeof(MyStruct)
    );

    std::string receivedData;
    size_t receivedSize;
    unsigned int priority;
    mq.receive(&receivedData[0], receivedData.size(), receivedSize, priority);

    // Deserialize the received data into a MyStruct instance
    MyStruct receivedStruct;
    std::istringstream iss(receivedData);
    boost::archive::binary_iarchive archive(iss);
    archive >> receivedStruct;

    // Use the received struct
    std::cout << "Received ID: " << receivedStruct.id << std::endl;
    std::cout << "Received Value: " << receivedStruct.value << std::endl;
    std::cout << "Received Name: " << receivedStruct.name << std::endl;
}

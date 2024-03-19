#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

void sendStruct() {
    MyStruct myData = {1, 3.14, "Struct Example"};

    // Serialize the struct into a string
    std::ostringstream oss;
    boost::archive::binary_oarchive archive(oss);
    archive << myData;
    std::string serializedData = oss.str();

    // Send the serialized data using Boost Interprocess Message Queue
    boost::interprocess::message_queue mq(
        boost::interprocess::open_or_create,
        "my_message_queue",
        100,
        sizeof(char) * serializedData.size()
    );
    mq.send(serializedData.c_str(), serializedData.size(), 0);
}

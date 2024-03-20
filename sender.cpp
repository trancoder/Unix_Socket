#include <iostream>
#include <cstring>
#include <atomic> // For atomic
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

struct MyStruct {
    std::atomic<bool> newDataFlag;
    int value1;
    float value2;
    char message[100];
};

int main() {
    using namespace boost::interprocess;

    // Create or open the shared memory object
    shared_memory_object shm(open_or_create, "my_shared_memory", read_write);

    // Set the size of the shared memory segment
    shm.truncate(sizeof(MyStruct));

    // Map the shared memory into the process's address space
    mapped_region region(shm, read_write);

    // Get a pointer to the mapped region
    MyStruct* data = static_cast<MyStruct*>(region.get_address());

    // Clear the shared memory data
    std::memset(data, 0, sizeof(MyStruct));

    // Set the new data flag to false initially
    data->newDataFlag.store(false);

    // Generate new data
    data->value1 = 42;
    data->value2 = 3.14f;
    std::strcpy(data->message, "Hello from the sender!");

    // Set the new data flag to true to indicate presence of new data
    data->newDataFlag.store(true);

    return 0;
}


#include <iostream>
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
    try {
        // Open the shared memory object
        shared_memory_object shm(open_only, "my_shared_memory", read_write); // Change read_only to read_write

        // Map the shared memory into the process's address space with read_write permissions
        mapped_region region(shm, read_write); // Change read_only to read_write

        // Get a pointer to the mapped region
        MyStruct* data = static_cast<MyStruct*>(region.get_address());

        // Clear the shared memory data
        std::memset(data, 0, sizeof(MyStruct));

        // Monitor the new data flag in shared memory
        while (true) {
            if (data->newDataFlag.load()) {
                // New data flag is set, indicating presence of new data
                std::cout << "New data detected in shared memory:\n";
                std::cout << "Value 1: " << data->value1 << '\n';
                std::cout << "Value 2: " << data->value2 << '\n';
                std::cout << "Message: " << data->message << '\n';

                // Reset the new data flag to false for future use
                data->newDataFlag.store(false);
            }

            // Add a sleep or wait mechanism to avoid busy waiting
            // For example, std::this_thread::sleep_for(std::chrono::milliseconds(100));

            // Add additional processing or logic as needed
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return 1;
    }
    return 0;
}


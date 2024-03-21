#include <iostream>
#include <boost/asio.hpp>

struct Message {
    int id;
    char content[1024]; // Fixed-size char array for content
};

int main() {
    try {
        boost::asio::io_context io_context;

        // UDP socket for receiving
        boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 12345));

        // Receive buffer
        Message received_msg;

        // Endpoint for sender's response
        boost::asio::ip::udp::endpoint sender_endpoint;

        // Receive the struct
        size_t len = socket.receive_from(boost::asio::buffer(&received_msg, sizeof(received_msg)), sender_endpoint);

        // Check if received data matches the expected struct size
        if (len == sizeof(received_msg)) {
            std::cout << "Received message: ID = " << received_msg.id << ", Content = " << received_msg.content << std::endl;
        } else {
            std::cerr << "Received message with invalid size" << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}


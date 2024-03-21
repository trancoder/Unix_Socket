#include <iostream>
#include <boost/asio.hpp>

struct Message {
    int id;
    char content[1024]; // Fixed-size char array for content
};

int main() {
    try {
        boost::asio::io_context io_context;

        // UDP socket for sending
        boost::asio::ip::udp::socket socket(io_context);

        // Set up the remote endpoint (receiver's endpoint)
        boost::asio::ip::udp::endpoint remote_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12345);

        // Struct to send
        Message msg_to_send{42, "Hello from sender!"};

        // Send the struct
        socket.open(boost::asio::ip::udp::v4());
        socket.send_to(boost::asio::buffer(&msg_to_send, sizeof(msg_to_send)), remote_endpoint);

        std::cout << "Message sent successfully" << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}


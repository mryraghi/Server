#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

enum { max_length = 1024 };

int main(int argc, const char** argv ) {

	if (argc != 3) {

      std::cout << "Usage: client <server ip> <port>\n";
      std::cout << "Example:\n";
      std::cout << "  client 127.0.0.1 8080\n";

      return -1;

    }

    boost::asio::io_service io_service;

    boost::asio::ip::tcp::socket socket(io_service);

    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(argv[1], argv[2]);
    boost::asio::ip::tcp::resolver::iterator server_endpoint = resolver.resolve(query);

    boost::asio::connect( socket, server_endpoint );

    std::cout << "Enter message: ";
    char request[max_length];
    std::cin.getline(request, max_length);
    size_t request_length = std::strlen(request);
    boost::asio::write( socket, boost::asio::buffer( request, request_length ) );

    //char reply[max_length];
    //size_t reply_length = boost::asio::read( socket, boost::asio::buffer( reply, request_length ) );
    //std::cout << "Reply is: ";
    //std::cout.write(reply, reply_length);
    //std::cout << "\n";

    return 0;

}
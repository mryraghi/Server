#include <iostream>
#include <string>
#include <boost/array.hpp>
#include "session.h"
#include "server.h"

#define ERROR -1
#define OK 0

using boost::asio::ip::tcp;

int main(int argc, const char** argv ) {

	if (argc != 2) {

      std::cout << "Usage: server <port>\n";
      std::cout << "Example:\n";
      std::cout << "  server 8080\n";

      return ERROR;

    }

    int port = atoi( argv[1] );

    boost::asio::io_service io_service;

    server tcp_echo_server( io_service, port );

    std::cout<<"[running] tcp echo server listening on port "<<port<< std::endl;

    io_service.run();

    return OK;

} // end main function


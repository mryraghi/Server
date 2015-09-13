#include <iostream>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "session.h"
#include "server.h"

#define ERROR -1
#define OK 0

using boost::asio::ip::tcp;

boost::asio::io_service io_service;
int port_global;

void non_persistent_connection(const boost::system::error_code & /*e*/) {
    server tcp_echo_server(io_service, port_global);
}

int main(int argc, const char** argv ) {

	if (argc != 2) {

      std::cout << "Usage: server <port>\n";
      std::cout << "Example:\n";
      std::cout << "  server 8080\n";

      return ERROR;

    }

    int port = atoi( argv[1] );
    port_global = port;


    std::cout<<"[running] tcp echo server listening on port "<<port<< std::endl;

    boost::asio::deadline_timer t(io_service, boost::posix_time::seconds(60));
    t.async_wait(&non_persistent_connection);

    io_service.run();

    return OK;

} // end main function
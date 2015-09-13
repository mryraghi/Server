#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "session.h"

using boost::asio::ip::tcp;

#ifndef SERVER_H
#define SERVER_H

#define DEBUG 0

class server {
  
  public: 

    server( boost::asio::io_service& io_service, short port );

  private:

    void start_accept();
    void handle_accept( session* new_session, const boost::system::error_code& error );

    void delete_session(session *session1);

    boost::asio::io_service& _io_service;
    tcp::acceptor _acceptor;
    
};

#endif


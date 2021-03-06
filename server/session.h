#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

#ifndef SESSION_H
#define SESSION_H

#define DEBUG 0

class session {
  
  public: 

    session( boost::asio::io_service& io_service );
    ~session();
    
    tcp::socket& socket();

    void start();

  private:

    void handle_write( const boost::system::error_code& error );
    void handle_read( const boost::system::error_code& error, size_t bytes_transferred );


    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
    
};

#endif


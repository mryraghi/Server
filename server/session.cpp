#include "session.h"
#include <iostream>
std::array<char, 10> data_received;

/**

  Constructor:

  session( boost::asio::io_service& io_service )

*/
session::session( boost::asio::io_service& io_service ) : socket_(io_service) {

  std::cout<<"-----------------[New session created!]------------------"<<std::endl;

} // end constructor


/**
  
  Destructor:

  ~session()


*/
session::~session() {

  std::cout<<"Session terminated!"<<std::endl;

} // end destructor


/**

  Method signature:

  tcp::socket& socket()

  Access modifier: public

*/
tcp::socket& session::socket() {

  return socket_;

} // return socket method


/**

  Method signature:

  void start()

  Access modifier: public

*/
void session::start() {

  socket_.async_read_some( boost::asio::buffer(data_, max_length), boost::bind(  &session::handle_read,
                           this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred ) );

} // end start() method


/**

  Method signature:

  void handle_read( const boost::system::error_code& error, size_t bytes_transferred )

  Access modifier: private

*/
void session::handle_read( const boost::system::error_code& error, size_t bytes_transferred ) {





  if (!error) {

      std::ostringstream ss;
      char response_buffer[1024];

      std::string request(data_);
      std::cout<<"Request Message: "<<request<<"\n"<<std::endl;
      std::string entity_body = "<html><body><p>Hello\n\n\n" + request + "</p></body></html>";

      long len = entity_body.length();

      ss << len;
      std::string content_length = ss.str();
      std::string header = "HTTP/1.1 200 OK\r\nContent-length: " + content_length + "\r\n\r\n";
      std::string response = header + entity_body;

      std::cout<<"Response message:\n"<<std::endl;
      strcpy(response_buffer, response.c_str());
      std::cout<<response_buffer<<std::endl;


    boost::asio::async_write( socket_,
                              boost::asio::buffer( response_buffer, response.length() ),
                              boost::bind(  &session::handle_write, this,
                                            boost::asio::placeholders::error ) );

  } else delete this;

} // end handle_read() method


/**

  Method signature:

  void handle_write( const boost::system::error_code& error )

  Access modifier: private

*/
void session::handle_write( const boost::system::error_code& error ) {

  if (!error) {

    socket_.async_read_some(  boost::asio::buffer( data_, max_length ),
                              boost::bind(  &session::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred ) );

  } else delete this;

} // end handle_write() method

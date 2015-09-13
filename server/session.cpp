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

      std::istringstream iss(request);
      std::string method;
      std::string query;
      std::string protocol;

      if(!std::getline(std::getline(std::getline(iss, method, ' '), query, ' '), protocol))
      {
          std::cout << "ERROR: parsing request\n";
      }

      iss.clear();
      iss.str(query);

      std::string url;

      if(!std::getline(iss, url, '?')) // remove the URL part
      {
          std::cout << "ERROR: parsing request url\n";
      }

      // store query key/value pairs in a map
      std::map<std::string, std::string> params;

      std::string keyval, key, val;

      while(std::getline(iss, keyval, '&')) // split each term
      {
          std::istringstream iss(keyval);

          if(std::getline(std::getline(iss, key, '='), val))
              params[key] = val;
      }

      std::cout << "protocol: " << protocol << '\n';
      std::cout << "method  : " << method << '\n';
      std::cout << "url     : " << url << '\n';

      std::map<std::string, std::string>::iterator i;

      for(i = params.begin(); i != params.end(); ++i)
          std::cout << "param   : " << i->first << " = " << i->second << '\n';


      //std::cout<<"\n\n\n\nRequest Message: "<<request<<"\n"<<std::endl;
      std::string entity_body = "<html><body><p>Hello\n\n\n" + url + "</p></body></html>";

      long len = entity_body.length();

      ss << len;
      std::string content_length = ss.str();
      std::string header = "HTTP/1.1 200 OK\r\nContent-length: " + content_length + "\r\n\r\n";
      std::string response = header + entity_body;

      //std::cout<<"Response message:\n"<<std::endl;
      strcpy(response_buffer, response.c_str());
      //std::cout<<response_buffer<<std::endl;
      std::cout<<"------------------------------------------------------------"<<std::endl;


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

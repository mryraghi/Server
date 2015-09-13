#include "session.h"
#include <iostream>
#include <fstream>
#include <chrono>

std::chrono::steady_clock::time_point timer_end_session = std::chrono::steady_clock::now()
                                                          + std::chrono::minutes(1);
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

      while (std::chrono::steady_clock::now() < timer_end_session) {
          std::ostringstream ss;
          char response_buffer[1024];

          std::string request(data_);

          std::istringstream iss(request);
          std::string method;
          std::string query;
          std::string protocol;
          int error_code = 200;

          if (!std::getline(std::getline(std::getline(iss, method, ' '), query, ' '), protocol)) {
              std::cout << "ERROR: parsing request\n";
          }

          iss.clear();
          iss.str(query);

          std::string url;

          if (!std::getline(iss, url, '?')) // remove the URL part
          {
              std::cout << "ERROR: parsing request url\n";
          }

          // store query key/value pairs in a map
          std::map<std::string, std::string> params;

          std::string keyval, key, val;

          while (std::getline(iss, keyval, '&')) // split each term
          {
              std::istringstream iss(keyval);

              if (std::getline(std::getline(iss, key, '='), val))
                  params[key] = val;
          }

          std::cout << "protocol: " << protocol << '\n';
          std::cout << "method  : " << method << '\n';
          std::cout << "url     : " << url << '\n';

          std::map<std::string, std::string>::iterator i;

          for (i = params.begin(); i != params.end(); ++i)
              std::cout << "param   : " << i->first << " = " << i->second << '\n';
          std::string entity_body;
          std::fstream f;     // file stream
          if (url != "/SimplePost.html" && params.empty()) {
              url = "/error.html";
              error_code = 404;
          }
          std::string complete_path = "/home/romeo/Documents/Server" + url;
          try {
              f.open(complete_path.c_str(), std::ios_base::in);     // open file for reading
              std::string temp;     // temp variable we will use for getting chunked data
              while (!f.eof()) {     // read data until the end of file is reached
                  f >> temp;     // get first chunk of data
                  entity_body.append(temp);
              }
          } catch (std::ios_base::failure e) {
              if (!params.empty()) {
                  entity_body.clear();
                  for (i = params.begin(); i != params.end(); ++i) {
                      entity_body.append("\nparam: ");
                      entity_body.append(i->first);
                      entity_body.append(" = ");
                      entity_body.append(i->second);
                  }
              }
          }


          long len = entity_body.length();

          ss << len;

          std::string content_length = ss.str();
          std::string header =
                  "HTTP/1.1 " + std::to_string(error_code) + " OK\r\nContent-length: " + content_length + "\r\n\r\n";
          std::string response = header + entity_body;

          //std::cout<<"Response message:\n"<<std::endl;
          strcpy(response_buffer, response.c_str());
          //std::cout<<response_buffer<<std::endl;
          std::cout << "------------------------------------------------------------" << std::endl;


          boost::asio::async_write(socket_,
                                   boost::asio::buffer(response_buffer, response.length()),
                                   boost::bind(&session::handle_write, this,
                                               boost::asio::placeholders::error));
      }
      delete this;
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

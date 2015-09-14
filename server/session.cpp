#include "session.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <boost/thread/thread.hpp>


/**

  Constructor:

  session( boost::asio::io_service& io_service )

*/
session::session( boost::asio::io_service& io_service ) : socket_(io_service) {

    std::cout << "-------------------[New session created]-----------------" << std::endl;

} // end constructor


/**
  
  Destructor:

  ~session()


*/
session::~session() {

    std::cout << "-------------------[Session terminated]------------------" << std::endl;

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
          try {
              if (url != "/SimplePost.html" && params.empty()) {
                  entity_body = "<!DOCTYPE html>\n"
                          "<html lang=\"en\">\n"
                          "<head>\n"
                          "    <meta charset=\"UTF-8\">\n"
                          "    <title>Page not found!</title>\n"
                          "</head>\n"
                          "<body>\n"
                          "<h3>404 Page not found ;)</h3>\n"
                          "\n"
                          "<p>For more information please read the README.md file.<br><br>Romeo Bellon</p>\n"
                          "</body>\n"
                          "</html>";
              } else {
                  entity_body = "<!DOCTYPE html>\n"
                          "<html lang=\"en\">\n"
                          "<head>\n"
                          "    <meta charset=\"UTF-8\">\n"
                          "    <title>SimplePost</title>\n"
                          "    <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css\">\n"
                          "    <link href='https://fonts.googleapis.com/css?family=Open+Sans:300,600' rel='stylesheet' type='text/css'>\n"
                          "</head>\n"
                          "<body>\n"
                          "<h1 style=\"margin-left:10px; font-family:'Open Sans',sans-serif; font-weight:600;\">\n"
                          "    <span class=\"glyphicon glyphicon-console\" aria-hidden=\"true\"></span>Simple POST</h1>\n"
                          "\n"
                          "<form style=\"margin-left: 10px; width: auto; font-family:'Open Sans',sans-serif; font-weight:300;\" method=\"post\"\n"
                          "      action=\"104.131.100.250\">\n"
                          "    <div class=\"form-group\">\n"
                          "        <label>First variable</label>\n"
                          "        <input type=\"text\" class=\"form-control\" name=\"first\" placeholder=\"e.g. Romeo\">\n"
                          "    </div>\n"
                          "    <div class=\"form-group\">\n"
                          "        <label>Second variable</label>\n"
                          "        <input type=\"text\" class=\"form-control\" name=\"second\" placeholder=\"e.g. Bellon\">\n"
                          "    </div>\n"
                          "    <div class=\"form-group\">\n"
                          "        <label>Third variable</label>\n"
                          "        <input type=\"text\" class=\"form-control\" name=\"third\" placeholder=\"e.g. CSCI 440\">\n"
                          "    </div>\n"
                          "    <button type=\"submit\" class=\"btn btn-default\">Submit</button>\n"
                          "</form>\n"
                          "</body>\n"
                          "</html>";
              }
          } catch (std::ios_base::failure e) {
              if (!params.empty()) {
                  entity_body = "<!DOCTYPE html>\n"
                          "<html lang=\"en\">\n"
                          "<head>\n"
                          "    <title>HTTP GET Request</title>\n"
                          "    <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap3.3.5/css/bootstrap.min.css\\\">\n"
                          "    <link href='https://fonts.googleapis.com/css?family=Open+Sans:300,600' rel='stylesheet' type='text/css'>\n"
                          "</head>\n"
                          "<body>\n"
                          "    <h1 style=\"margin-left:10px; font-family:'Open Sans',sans-serif; font-weight:600;\">GET Operation</h1>\n"
                          "    <table style=\"margin-left:10px; width:auto; font-family:'Open Sans',sans-serif; font-weight:300;\" class=\"table\">\n"
                          "        <thead>\n"
                          "            <th><b>Parameter</b></th>\n"
                          "            <th><b>Value</b></th>\n"
                          "        </thead>";
                  for (i = params.begin(); i != params.end(); ++i) {
                      entity_body.append("<tr><td>");
                      entity_body.append(i->first);
                      entity_body.append("</td><td>");
                      entity_body.append(i->second);
                      entity_body.append("</td></tr>");
                  }
                  entity_body.append("</table></body></html>");
              }
          }


          long len = entity_body.length();

          ss << len;

          std::string content_length = ss.str();
          std::string header =
                  "HTTP/1.1 " + std::to_string(error_code) + " OK\r\nContent-length: " + content_length + "\r\n\r\n";
          std::string response = header + entity_body;

          strcpy(response_buffer, response.c_str());
          std::cout << "------------------------------------------------------------" << std::endl;


          boost::asio::async_write(socket_,
                                   boost::asio::buffer(response_buffer, response.length()),
                                   boost::bind(&session::handle_write, this,
                                               boost::asio::placeholders::error));


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
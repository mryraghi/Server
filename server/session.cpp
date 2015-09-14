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
        char response_buffer[100000];

        std::string request(data_);

        std::istringstream iss(request);
        std::string method;
        std::string query;
        std::string protocol;
        std::string url;
        std::string operation;
        // store query key/value pairs in a map
        std::map<std::string, std::string> params;

        std::string keyval, key, val;
        int error_code = 200;

        if (!std::getline(std::getline(std::getline(iss, method, ' '), query, ' '), protocol)) {
            std::cout << "ERROR: parsing request\n";
        }

        if (method == "GET") {
            iss.clear();
            iss.str(query);
            operation = "GET Request";

            if (!std::getline(iss, url, '?')) // remove the URL part
            {
                std::cout << "ERROR: parsing request url\n";
            }
        } else {
            operation = "POST";
            std::istringstream f(request);
            std::string line;
            std::string string_content;
            while (std::getline(f, line)) {
                string_content = line;
            }
            iss.clear();
            iss.str(string_content);
        }

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
        if (url != "/SimplePost.html" && params.empty()) {
            entity_body = "<!DOCTYPE html>\n"
                    "<html lang=\"en\">\n"
                    "<head>\n"
                    "    <meta charset=\"UTF-8\">\n"
                    "    <title>Page not found!</title>\n"
                    "    <link href='https://fonts.googleapis.com/css?family=Open+Sans:300,600' rel='stylesheet' type='text/css'>\n"
                    "</head>\n"
                    "<body>\n"
                    "<h1 style=\"margin-left:10px; font-family:'Open Sans',sans-serif; font-weight:600;\">Page not found!d</h1>\n"
                    "\n"
                    "<p style=\"margin-left:10px; font-family:'Open Sans',sans-serif; font-weight:300;\">For more information please read the README.md file.<br><br>Romeo Bellon</p>\n"
                    "</body>\n"
                    "</html>";
        } else if (url == "/SimplePost.html") {
            entity_body = "<!DOCTYPE html>\n"
                    "<html lang=\"en\">\n"
                    "<head>\n"
                    "    <meta charset=\"UTF-8\">\n"
                    "    <title>SimplePost</title>\n"
                    "    <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css\">\n"
                    "    <link href='https://fonts.googleapis.com/css?family=Open+Sans:300,600' rel='stylesheet' type='text/css'>\n"
                    "</head>\n"
                    "<body>\n"
                    "\n"
                    "<h1 style=\"margin-left:10px; font-family:'Open Sans',sans-serif; font-weight:600;\">Simple POST</h1>\n"
                    "\n"
                    "<form style=\"margin-left: 10px; width: auto; font-family:'Open Sans',sans-serif; font-weight:300;\" method=\"post\"\n"
                    "      action=\"104.131.100.250\">\n"
                    "    <div class=\"form-group\">\n"
                    "        <label>First variable</label>\n"
                    "        <input style=\"width: auto\" type=\"text\" class=\"form-control\" name=\"first\" placeholder=\"e.g. Romeo\">\n"
                    "    </div>\n"
                    "    <div class=\"form-group\">\n"
                    "        <label>Second variable</label>\n"
                    "        <input style=\"width: auto\" type=\"text\" class=\"form-control\" name=\"second\" placeholder=\"e.g. Bellon\">\n"
                    "    </div>\n"
                    "    <div class=\"form-group\">\n"
                    "        <label>Third variable</label>\n"
                    "        <input style=\"width: auto\" type=\"text\" class=\"form-control\" name=\"third\" placeholder=\"e.g. CSCI 440\">\n"
                    "    </div>\n"
                    "    <button type=\"submit\" class=\"btn btn-default\">Submit</button>\n"
                    "</form>\n"
                    "</body>\n"
                    "</html>";

        } else if (!params.empty()) {
            entity_body = "<!DOCTYPE html>\n"
                    "<html lang=\"en\">\n"
                    "<head>\n"
                    "    <title>HTTP ";
            entity_body.append(operation);
            entity_body.append(" Request</title>\n"
                    "    <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap3.3.5/css/bootstrap.min.css\">\n"
                    "    <link href='https://fonts.googleapis.com/css?family=Open+Sans:300,600' rel='stylesheet' type='text/css'>\n"
                    "</head>\n"
                    "<body>\n"
                                       "    <h1 style=\"margin-left:10px; font-family:'Open Sans',sans-serif; font-weight:600;\">");
            entity_body.append(operation);
            entity_body.append("</h1>\n"
                    "    <table style=\"margin-left:10px; width:auto; font-family:'Open Sans',sans-serif; font-weight:300;\" class=\"table\">\n"
                    "        <thead>\n"
                    "            <th><b>Parameter</b></th>\n"
                    "            <th><b>Value</b></th>\n"
                                       "        </thead>");
            for (i = params.begin(); i != params.end(); ++i) {
                entity_body.append("<tr><td>");
                entity_body.append(i->first);
                entity_body.append("</td><td>");
                entity_body.append(i->second);
                entity_body.append("</td></tr>\n");
            }
            entity_body.append("</table></body></html>");
        } else if (url == "/index.html") {
            entity_body = "<h1><a href=\"#csci-440-http-server\" name=\"csci-440-http-server\" id=\"csci-440-http-server\" class=\"anchor\"></a>CSCI 440: HTTP Server</h1>\n"
                    "<p>by Romeo Bellon</p>\n"
                    "<ul>\n"
                    "  <li>this little project/assignment can be easily tested here:\n"
                    "    <ul>\n"
                    "      <li><a href=\"http://104.131.100.250:8080/index.html\">http://104.131.100.250:8080/index.html</a> // INDEX page</li>\n"
                    "      <li><a href=\"http://104.131.100.250:8080/?name=Romeo&surname=Bellon&class=CSCI440\">http://104.131.100.250:8080/?name=Romeo&surname=Bellon&class=CSCI440</a> // GET Operation</li>\n"
                    "      <li><a href=\"http://104.131.100.250:8080/SimplePost.html\">http://104.131.100.250:8080/SimplePost.html</a> // POST Operation</li>\n"
                    "      <li><a href=\"http://104.131.100.250:8080/asdafasfsdf\">http://104.131.100.250:8080/asdafasfsdf</a> // ERROR handling</li>\n"
                    "    </ul>\n"
                    "  </li>\n"
                    "  <li>the GitHub page for this project/assignment is <a href=\"https://github.com/mryraghi/Server\">https://github.com/mryraghi/Server</a></li>\n"
                    "  <li>this is project made with Clion 1.1.1 but is executable even from the terminal, of course</li>\n"
                    "  <li>I've create a script <strong>autoscript.sh</strong> that helped me to automate the process of updating my local repository from github. It's not necessary to use it, but it is useful.</li>\n"
                    "  <li>\n"
                    "  <p>This is the best I can do for now :)</p></li>\n"
                    "</ul>";
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
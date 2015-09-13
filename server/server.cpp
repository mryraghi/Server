#include "server.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

/**

  Constructor

  server( boost::asio::io_service& io_service, short port )

*/
server::server(boost::asio::io_service &io_service, short port)
  : _io_service( io_service ), _acceptor( io_service, tcp::endpoint( tcp::v4(), port ) ) {

  start_accept();

} // end constructor


/**

  Method signature:

  void start_accept()

  Access modifier: Private

*/
void server::start_accept() {

  session* new_session = new session(_io_service);

  boost::asio::deadline_timer t(_io_service, boost::posix_time::seconds(20));
  t.async_wait(delete new_session);
  _io_service.run();

  _acceptor.async_accept(new_session->socket(), boost::bind(&server::handle_accept,
                                                              this, new_session,
                                                              boost::asio::placeholders::error ) );

} // end start_accept() method


/**

  Method signature:

  void handle_accept( session* new_session, const boost::system::error_code& error )

  Access modifier: Private

*/
void server::handle_accept( session* new_session, const boost::system::error_code& error ) {

  ( !error ) ? new_session->start() : delete new_session;

  start_accept();

} // end handle_accept() method

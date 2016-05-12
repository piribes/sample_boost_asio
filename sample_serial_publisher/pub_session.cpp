//
//  Copyright 2016 Giuseppe Roberti
//
//  This file is part of sample_boost_asio.
//
//  sample_boost_asio is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  sample_boost_asio is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with sample_boost_asio.  If not, see <http://www.gnu.org/licenses/>.

#include <boost/bind.hpp>
#include <sstream>
#include <chrono>
#include <cassert>

#include "pub_session.hpp"
#include "pub_service.hpp"

using namespace silenti::asio::pub;
using namespace boost::asio::ip;
using boost::system::error_code;

session::session(
  service &srv_,
  tcp::socket socket_
): srv(srv_), timer{srv.get_io_service()}, socket(std::move(socket_)) {}

session::~session() {
  srv.decrease_num_connections();
}

void session::start() {
  setup_async_write_stats();
  
  setup_async_read();
}

void session::setup_async_write_stats() {
  timer.expires_from_now(std::chrono::milliseconds{1000});

  timer.async_wait([this, self = shared_from_this()](error_code ec) {
    if (ec)
      return;

    assert(socket.is_open());

    std::ostringstream os;

    os << "Stats: ("
    << "connections=" << srv.get_num_connections()
    << ",self_count=" << self.use_count()
    << ",last_read_line=" << srv.get_last_line()
    << ")\r\n";

    boost::asio::write(socket, boost::asio::buffer(os.str()));

    if (closing) {
      socket.close();
      
      return;
    }

    setup_async_write_stats();
  });
}

void session::setup_async_read() {
  socket.async_read_some(
    boost::asio::buffer(data, max_length),
    boost::bind(
      &session::process_read,
      shared_from_this(),
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred
    )
  );
}

void session::process_read(error_code ec, std::size_t length) {
  if (ec)
    return;
  
  if (strncmp(data, "QUIT\r\n", 6) == 0) {
    boost::asio::async_write(
      socket,
      boost::asio::buffer("Exiting ...\r\n"),
      [this, self = shared_from_this()](error_code ec, std::size_t length) {
        closing = true;
      }
    );
  } else {
    setup_async_write(length);
  }
}

void session::setup_async_write(std::size_t length) {
  boost::asio::async_write(
    socket,
    boost::asio::buffer(data, length),
    boost::bind(
      &session::process_write,
      shared_from_this(),
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred
    )
  );
}

void session::process_write(error_code ec, std::size_t length) {
  if (ec)
    return;

  setup_async_read();
}

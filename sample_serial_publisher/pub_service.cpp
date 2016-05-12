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
#include <memory>

#include "pub_service.hpp"

using namespace silenti::asio::pub;
using namespace boost::asio::ip;
using boost::system::error_code;

service::service(
  boost::asio::io_service &io_service_,
  short port_
): acceptor(io_service_, tcp::endpoint(tcp::v4(), port_)), socket(io_service_)
{
  setup_async_accept();
}

boost::asio::io_service& service::get_io_service() {
  return acceptor.get_io_service();
}

void service::setup_async_accept() {
  acceptor.async_accept(
    socket,
    boost::bind(&service::process_accept, this, _1)
  );
}

void service::process_accept(error_code ec) {
  ++num_connections;
  
  if (!ec) {
    std::make_shared<session>(
      *this,
      std::move(socket)
    )->start();
  }

  setup_async_accept();
}

const int service::get_num_connections() {
  return num_connections;
}

void service::decrease_num_connections() {
  --num_connections;
}

const std::string& service::get_last_line() {
  return last_line;
}

void service::set_last_line(std::string line) {
  last_line = line;
}

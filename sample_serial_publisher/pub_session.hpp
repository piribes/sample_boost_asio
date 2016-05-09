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
//  Foobar is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with sample_boost_asio.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <memory>

#include "pub_service.hpp"

namespace silenti {
namespace asio {
namespace pub {

class service;

class session: public std::enable_shared_from_this<session> {
public:
  session(service &srv, boost::asio::ip::tcp::socket socket);

  ~session();
  
  void start();

private:
  void setup_async_write_stats();
  
  void setup_async_read();
  
  void process_read(boost::system::error_code ec, std::size_t length);

  void setup_async_write(std::size_t length);
  
  void process_write(boost::system::error_code ec, std::size_t length);

  service &srv;
  
  boost::asio::steady_timer timer;

  boost::asio::ip::tcp::socket socket;
  
  enum { max_length = 1024 };

  char data[max_length];
  
  bool closing;
};

}
}
}

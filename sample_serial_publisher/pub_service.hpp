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
#include <string>

#include "pub_session.hpp"

namespace silenti {
namespace asio {
namespace pub {

class service {

public:
  service(boost::asio::io_service &io_service, short port);
  
  boost::asio::io_service& get_io_service();
  
  const int get_num_connections();
  
  void decrease_num_connections();
  
  const std::string& get_last_line();
  
  void set_last_line(std::string line);

private:
  void setup_async_accept();

  void process_accept(boost::system::error_code ec);
  
  boost::asio::ip::tcp::acceptor acceptor;

  boost::asio::ip::tcp::socket socket;
  
  std::string last_line;
  
  int num_connections;
};

}
}
}

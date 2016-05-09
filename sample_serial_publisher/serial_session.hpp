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
#include <sys/termios.h>
#include <memory>

#include "serial_service.hpp"

#define BOUD_RATE      B115200
#define CHARACTER_SIZE 8
#define FLOW_CONTROL   serial_port_base::flow_control::hardware
#define PARITY         serial_port_base::parity::even
#define STOP_BITS 		 serial_port_base::stop_bits::two

namespace silenti {
namespace asio {
namespace serial {

class service;

struct options;

class session: public std::enable_shared_from_this<session> {
public:
  session(service &service, options &opts);
  
  void start();
  
private:
  void setup_serial_port();
  
  void setup_async_read();
  
  void process_read(boost::system::error_code ec);

  service &srv;
  
  boost::asio::serial_port serial_port;

  boost::asio::streambuf b;
  
  options &opts;
};

}
}
}

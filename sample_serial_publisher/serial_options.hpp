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

#pragma once

#include <sys/termios.h>
#include <string>

#define BOUD_RATE      B115200
#define CHARACTER_SIZE 8
#define FLOW_CONTROL   serial_port_base::flow_control::hardware
#define PARITY         serial_port_base::parity::even
#define STOP_BITS 		 serial_port_base::stop_bits::two

namespace silenti {
namespace asio {
namespace serial {

struct options {
  std::string  tty;
  unsigned int baud_rate = B115200;
  unsigned int character_size = 8;
  std::string  parity = "none";
  double       stop_bits = 1;
};

}
}
}

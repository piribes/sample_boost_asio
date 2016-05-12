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

#include <boost/asio.hpp>
#include <string>
#include <functional>
#include <memory>

#include "serial_options.hpp"
#include "serial_session.hpp"

namespace silenti {
namespace asio {
namespace serial {

struct options;

class service: public std::enable_shared_from_this<service> {
public:
  service(boost::asio::io_service &io_service, options &opts);
  
  boost::asio::io_service& get_io_service();
  
  std::function<void(std::string)> on_read;

private:
  boost::asio::io_service &io_service;
};

}
}
}

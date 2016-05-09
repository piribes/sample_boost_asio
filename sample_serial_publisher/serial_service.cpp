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

#include "serial_service.hpp"

using namespace silenti::asio::serial;

service::service(boost::asio::io_service &io_service_, options &opts_):
  io_service(io_service_)
{
  std::make_shared<silenti::asio::serial::session>(*this, opts_)->start();
}

boost::asio::io_service& service::get_io_service() {
  return io_service;
}

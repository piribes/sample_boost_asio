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

#include "serial_session.hpp"

using namespace silenti::asio::serial;
using boost::asio::serial_port_base;
using boost::system::error_code;

session::session(service &srv_, options &opts_):
  srv(srv_),
  serial_port(srv.get_io_service()),
  opts(opts_)
{}

void session::start() {
  setup_serial_port();
  
  setup_async_read();
}

void session::setup_serial_port() {
  serial_port.open(opts.tty);

  serial_port.set_option(serial_port_base::baud_rate{
    opts.baud_rate
  });
  
  serial_port.set_option(serial_port_base::character_size{
    opts.character_size
  });

  if (opts.parity == "none") {
    serial_port.set_option(serial_port_base::parity{
      boost::asio::serial_port_base::parity::none
    });
  } else if (opts.parity == "odd") {
    serial_port.set_option(serial_port_base::parity{
      boost::asio::serial_port_base::parity::odd
    });
  } else if (opts.parity == "even") {
    serial_port.set_option(serial_port_base::parity{
      boost::asio::serial_port_base::parity::even
    });
  } else {
    throw new std::logic_error("Unknown parity");
  }

  if (opts.stop_bits == 1) {
    serial_port.set_option(serial_port_base::stop_bits{
      boost::asio::serial_port_base::stop_bits::one
    });
  } else if (opts.stop_bits == 1.5) {
    serial_port.set_option(serial_port_base::stop_bits{
      boost::asio::serial_port_base::stop_bits::onepointfive
    });
  } else if (opts.stop_bits == 2) {
    serial_port.set_option(serial_port_base::stop_bits{
      boost::asio::serial_port_base::stop_bits::two
    });
  } else {
    throw new std::logic_error("Unknown stop bits");
  }
}

void session::setup_async_read() {
  boost::asio::async_read_until(
    serial_port,
    b,
    '\r',
    boost::bind(
      &session::process_read,
      shared_from_this(),
      boost::asio::placeholders::error
    )
  );
}

void session::process_read(error_code ec) {
  if (ec)
    return;

  std::istream is(&b);

  std::string line;

  std::getline(is, line);

  if (line[line.length()-1] == '\r')
    line.erase(line.length()-1);

  if (srv.on_read)
    srv.on_read(line);

  setup_async_read();
}

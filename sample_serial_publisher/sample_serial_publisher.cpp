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

#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>

#include "pub_service.hpp"
#include "serial_options.hpp"
#include "serial_service.hpp"

namespace po = boost::program_options;
using namespace silenti::asio;

void usage(po::options_description &desc) {
  std::cerr
    << "Usage: sample_serial_publisher [options] <publisher-port> <serial-tty>\n"
    << desc
    << std::endl;
}

int main(int argc, char **argv) {
  int publisher_port;

  struct serial::options serial_options;

  // Declare options.
  po::options_description desc("Allowed options");

  desc.add_options()
    ("help",           "message help")
    ("publisher-port", po::value(&publisher_port)->required(),     "publisher TCP listen port")
    ("serial-tty",     po::value(&serial_options.tty)->required(), "serial tty name")
    ("baud-rate",      po::value(&serial_options.baud_rate),       "serial baud rate")
    ("character-size", po::value(&serial_options.character_size),  "serial character size")
    ("parity",         po::value(&serial_options.parity),          "serial parity (none|odd|even)")
    ("stop-bits",      po::value(&serial_options.stop_bits),       "serial stop bits (1|1.5|2)")
  ;

  // Declare positional options
  po::positional_options_description p;

  p.add("publisher-port", 1);

  p.add("serial-tty", 1);
  
  try {
    {
      po::variables_map vm;

      po::store(po::command_line_parser(argc, argv).
                options(desc).positional(p).run(), vm);

      po::notify(vm);
      
      if (vm.count("help")) {
        usage(desc);
        
        return EXIT_SUCCESS;
      }
    }

    boost::asio::io_service io_service;

    serial::service serial(io_service, serial_options);

    pub::service pub(io_service, publisher_port);
    
    serial.on_read = [&pub](std::string line) {
      pub.set_last_line(line);
    };

    std::cout << "Running ..." << std::endl;
    
    io_service.run();
  } catch (po::error &e) {
    std::cerr << "Error: " << e.what() << "\n";

    usage(desc);
    
    return EXIT_FAILURE;
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

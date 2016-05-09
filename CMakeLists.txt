cmake_minimum_required(VERSION 2.8)
# Avoid warnings in higher versions
if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" GREATER 2.6)
 cmake_policy(VERSION 2.8)
endif()
message(STATUS "Running cmake version ${CMAKE_VERSION}")
project("sample_boost_asio")
add_subdirectory(sample_serial_publisher)


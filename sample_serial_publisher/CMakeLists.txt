set(PROJECT_SOURCE
  sample_serial_publisher.cpp
  pub_service.cpp
  pub_service.hpp
  pub_session.cpp
  pub_session.hpp
  serial_options.hpp
  serial_service.cpp
  serial_service.hpp
  serial_session.cpp
  serial_session.hpp
)
set(CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++")
set(PROJECT_TARGET sample_serial_publisher)
set(CMAKE_MODULE_PATH "/opt/local/cmake/;$/usr/local/cmake/;${CMAKE_MODULE_PATH}")
find_package(Boost 1.60 REQUIRED COMPONENTS program_options system regex)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(${PROJECT_TARGET} ${PROJECT_SOURCE})
  target_link_libraries(${PROJECT_TARGET} ${Boost_LIBRARIES})
else()
  message("Unable to continue: boost not found!")
endif()

cmake_minimum_required(VERSION 3.11.3)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
project(steam_helper)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED)

include_directories(${JSONCPP_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(steam_helper ${SOURCES})

set_property(TARGET steam_helper PROPERTY CXX_STANDARD 17)
target_link_libraries(steam_helper ${JSONCPP_LIBRARIES})
target_link_libraries(steam_helper ${CURL_LIBRARIES})


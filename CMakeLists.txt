cmake_minimum_required(VERSION 3.6)
project(vendMe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp chocolate.cpp main.h chocolate.h VendingMachine.cpp VendingMachine.h coin.cpp coin.h menu.cpp menu.h events.h simulation.cpp simulation.h events.cpp)
add_executable(vendMe ${SOURCE_FILES})
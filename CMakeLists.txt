cmake_minimum_required(VERSION 2.6)
project(bregextest)
set(CMAKE_AUTOMOC ON)

find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(BRegexTest/)
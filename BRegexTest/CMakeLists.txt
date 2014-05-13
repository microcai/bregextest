cmake_minimum_required(VERSION 2.6)
project(bregextest)

find_package(Qt4 REQUIRED)
find_package(Boost REQUIRED COMPONENTS regex)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})
set(bregextest_SRCS main.cpp mainwnd.cpp texteditor.cpp)

qt4_automoc(${bregextest_SRCS})


add_executable(bregextest ${bregextest_SRCS})
target_link_libraries(bregextest ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${Boost_LIBRARIES})

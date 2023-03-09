cmake_minimum_required(VERSION 3.24)
project(src)

set(CMAKE_CXX_STANDARD 23)

add_executable(src main.cpp Manager.cpp Manager.h Menu.cpp Menu.h Utility.cpp Utility.h Station.cpp Station.h Segment.cpp Segment.h)

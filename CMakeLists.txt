cmake_minimum_required(VERSION 3.13)
project(Data_Structures_Wet1)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DNDEBUG -Wall")
set(CMAKE_CXX_STANDARD 11)

add_executable(Data_Structures_Wet1
                main_test.cpp
        library1.cpp
                DataCenter.cpp
                DataServer.cpp
        )
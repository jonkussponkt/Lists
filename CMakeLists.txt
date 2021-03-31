cmake_minimum_required(VERSION 3.17)
project(Lists)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lists main.cpp List.cpp List.h Product.cpp Product.h Interaction.cpp Interaction.h)

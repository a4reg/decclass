cmake_minimum_required(VERSION 2.6)
project(decclass)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# set env
set(CLANG_PATH /home/nikitas/Progs/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-14.04)
include_directories(${CLANG_PATH}/include)

set(SOURCE_FILES main.cpp)

add_executable(decclass ${SOURCE_FILES})
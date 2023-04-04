cmake_minimum_required(VERSION 3.1)

project(amdaemon CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(amdaemon)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS amdaemon/src/*.cpp)

target_sources(amdaemon PRIVATE ${sources})
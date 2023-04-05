cmake_minimum_required(VERSION 3.1)
set(CMAKE_VERBOSE_MAKEFILE ON)

project(amdaemon CXX)
set(CMAKE_CXX_STANDARD 20)

add_definitions(-DUNICODE -D_UNICODE)
add_link_options(-municode)

add_executable(amdaemon WIN32)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS amdaemon/src/*.cpp)

target_sources(amdaemon PRIVATE ${sources})
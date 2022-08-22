cmake_minimum_required(VERSION 3.18)

project(
  CppDiep
  DESCRIPTION "Diep.io reimplemented in C++ with SFML and Box2D"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

find_package(
  SFML 2.5
  COMPONENTS graphics
  REQUIRED)
find_package(Box2D REQUIRED)

add_executable(cppdiep arena.cpp basic_tank.cpp bullet.cpp main.cpp tank.cpp)
target_link_libraries(cppdiep PRIVATE sfml-graphics Box2D)

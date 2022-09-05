cmake_minimum_required(VERSION 3.18)

project(
  CppDiep
  DESCRIPTION "Very simple 2D game based on Diep.io"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT HAVE_IPO)
if(HAVE_IPO)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL ON)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
endif()

find_package(
  SFML 2.5
  COMPONENTS graphics
  REQUIRED)
# Box2D 2.3 is required but its CMake config doesn't set the version properly.
find_package(Box2D REQUIRED)

add_executable(cppdiep arena.cpp basic_tank.cpp bullet.cpp main.cpp object.cpp
                       tank.cpp)
target_link_libraries(cppdiep PRIVATE sfml-graphics Box2D)

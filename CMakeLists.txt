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
find_package(box2d 2.4.1 REQUIRED)

add_executable(cppdiep
  src/arena.cpp
  src/arena.fwd.h
  src/arena.h
  src/basic_tank.cpp
  src/basic_tank.h
  src/box2d_categories.h
  src/bullet.cpp
  src/bullet.h
  src/external_control_tank.h
  src/main.cpp
  src/object.cpp
  src/object.h
  src/render_utils.h
  src/simple_ai_tank.h
  src/tank.cpp
  src/tank.fwd.h
  src/tank.h
  src/time.h)
target_link_libraries(cppdiep PRIVATE sfml-graphics box2d)

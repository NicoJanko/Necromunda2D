cmake_minimum_required(VERSION 3.16)
project(Necromunda2D LANGUAGES C CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# static build
set(BUILD_SHARED_LIBS OFF)

# src
set(SRCS
  src/main.cpp
  src/camera.cpp
  src/actions.cpp
  src/object.h
  src/world.cppd
)

# raylib
include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  # Pin to a known tag; you can update later.
  GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

# main exe
add_executable(necro2d
  ${SRCS}
)

target_include_directories(necro2d PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link raylib 
target_link_libraries(necro2d PRIVATE raylib)


# Binaries
set_target_properties(necro2d PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

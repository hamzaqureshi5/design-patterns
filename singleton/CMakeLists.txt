
cmake_minimum_required(VERSION 3.16)
project(pattern CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(pattern ${SOURCES})

target_compile_options(pattern PRIVATE 
    -Wall                  # Enable all common warnings
    -Wextra                # Extra warnings
    -Wno-unused-parameter  # Suppress unused parameter warnings
    -Wunused-variable      # Warn about unused variables
    -Wreturn-type          # Warn if a function might not return a value
    -Wno-redundant-move    # Suppress LLVM redundant move warning
    -g                     # Include debug information
)

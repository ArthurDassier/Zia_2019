cmake_minimum_required(VERSION 3.14.4)  # CMake version check
project(Zia)                            # Create project "Zia"
set(CMAKE_CXX_STANDARD 17)              # Enable c++17 standard


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(tests)
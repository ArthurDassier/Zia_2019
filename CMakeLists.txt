cmake_minimum_required(VERSION 3.14.4)  # CMake version check
project(zia)                            # Create project "zia"
set(CMAKE_CXX_STANDARD 17)              # Enable c++17 standard


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# execute_process(
#     COMMAND source profile.sh
# )

# set(ENV{CONFIG_PATH} "./config")     # Add config path as environment variable

# message("Environment variable CONFIG_PATH: $ENV{CONFIG_PATH}")

add_subdirectory(src)
# add_subdirectory(tests)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    config
    utils
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
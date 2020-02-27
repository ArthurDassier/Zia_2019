cmake_minimum_required(VERSION 3.11)    # CMake version check
set(CMAKE_CXX_STANDARD 14)              # Enable c++14 standard
set(CMAKE_CXX_FLAGS "-lboost_system -pthread -lpthread")
set(EXECUTABLE_NAME "zia")

add_definitions(-std=c++11 -fPIC -g3)

project(${EXECUTABLE_NAME})             # Create project "zia"

# # execute_process(
# #     COMMAND source profile.sh
# # )

# # set(ENV{CONFIG_PATH} "./config")     # Add config path as environment variable

# # message("Environment variable CONFIG_PATH: $ENV{CONFIG_PATH}")

#------------------------------------------------------------------------------#
#                                 CONAN BOOST                                  #
#------------------------------------------------------------------------------#

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

#-------------------------------------------------------------------------------

include(lib/openZia/openZia/openZia.cmake)

set(SOURCES "./src")

include_directories(${SOURCES})
add_subdirectory(${SOURCES})

set(SRC
    ${SOURCES}/main.cpp
)

add_executable(${EXECUTABLE_NAME} ${SRC})
target_link_libraries(${EXECUTABLE_NAME}
    ${openZiaLibs}
    utils
    server
    boost_system
)
target_include_directories(${EXECUTABLE_NAME} PRIVATE
    ${openZiaIncludes}
    ${UtilsIncludes}
)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
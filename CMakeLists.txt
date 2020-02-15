cmake_minimum_required(VERSION 3.14.4)  # CMake version check
project(zia)                            # Create project "zia"
set(CMAKE_CXX_STANDARD 17)              # Enable c++17 standard
add_definitions("-fPIC")
add_definitions("-g3")

set(LIB_PATH "./lib")

include(${LIB_PATH}/openZia/openZia/openZia.cmake)

#------------------------------------------------------------------------------#
#                                 CONAN BOOST                                  #
#------------------------------------------------------------------------------#

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

#-------------------------------------------------------------------------------

# execute_process(
#     COMMAND source profile.sh
# )

# set(ENV{CONFIG_PATH} "./config")     # Add config path as environment variable

# message("Environment variable CONFIG_PATH: $ENV{CONFIG_PATH}")

add_subdirectory(src)

get_filename_component(ZiaSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(MainSourceDir ${ZiaSourcesDir}/src)

set(ZiaSources
    ${MainSourceDir}/main.cpp
)

add_executable(zia ${ZiaSources})

target_link_libraries(zia
    config
    parser
    utils
)

set_target_properties(zia
    PROPERTIES LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
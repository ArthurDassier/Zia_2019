# cmake_minimum_required(VERSION 3.14.4)  # CMake version check
# set(EXECUTABLE_NAME "zia")
# project(${EXECUTABLE_NAME})             # Create project "zia"
# set(CMAKE_CXX_STANDARD 17)              # Enable c++17 standard
# add_definitions("-fPIC")
# add_definitions("-g3")

# # set(LIB_PATH "./lib")

# include(lib/openZia_old/openZia/openZia.cmake)
# include(src/modules/parser/ParserModule.cmake)

# #------------------------------------------------------------------------------#
# #                                 CONAN BOOST                                  #
# #------------------------------------------------------------------------------#

# # include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# # conan_basic_setup()

# #-------------------------------------------------------------------------------

# # execute_process(
# #     COMMAND source profile.sh
# # )

# # set(ENV{CONFIG_PATH} "./config")     # Add config path as environment variable

# # message("Environment variable CONFIG_PATH: $ENV{CONFIG_PATH}")

# add_subdirectory(src)

# get_filename_component(ZiaSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

# set(MainSourceDir ${ZiaSourcesDir}/src)

# set(ZiaSources
#     ${MainSourceDir}/main.cpp
# )

# add_executable(${EXECUTABLE_NAME} ${ZiaSources})

# target_link_libraries(${EXECUTABLE_NAME}
#     config
#     # parser
#     utils
# )

# set_target_properties(${EXECUTABLE_NAME}
#     PROPERTIES LINKER_LANGUAGE CXX
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
# )

#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_NAME "zia")

project(${EXECUTABLE_NAME})

add_definitions(-std=c++11 -fPIC -g3)

SET(CMAKE_CXX_FLAGS  "-lpthread -lboost_system")

set(SOURCES "./Sources")

include_directories("${SOURCES}")
include(lib/openZia_old/openZia/openZia.cmake)
include(Sources/Modules/ParserHTTP/ParserHTTP.cmake)

set(SRC
    ${SOURCES}/Main.cpp
    ${SOURCES}/Server.cpp
    ${SOURCES}/Log.cpp
    ${SOURCES}/Connection.cpp
    ${SOURCES}/ConnectionManager.cpp
)

add_executable(${EXECUTABLE_NAME} ${SRC})
target_link_libraries(${EXECUTABLE_NAME} ${openZiaLibs})
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${openZiaIncludes})

set_target_properties(${EXECUTABLE_NAME}
    PROPERTIES LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
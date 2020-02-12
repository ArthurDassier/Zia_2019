project(server)  # Create project "server"

set(LIB_NAME ${PROJECT_NAME})

set(LIB_PATH "../../lib")

message("Generating project ${PROJECT_NAME}...")

include(${LIB_PATH}/openZia/openZia/openZia.cmake)

get_filename_component(ServerSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

#------------------------------------------------------------------------------#
#                                 LOCAL BOOST                                  #
#------------------------------------------------------------------------------#

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.42.0 REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

set(USED_LIBS
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
)

#-------------------------------------------------------------------------------

set(ServerIncludes ${ServerSourcesDir})

set(ServerSources
    ${ServerSourcesDir}/connection_manager.cpp
    ${ServerSourcesDir}/connection.cpp
    ${ServerSourcesDir}/main.cpp
    ${ServerSourcesDir}/mime_types.cpp
    ${ServerSourcesDir}/reply.cpp
    ${ServerSourcesDir}/request_handler.cpp
    ${ServerSourcesDir}/request_parser.cpp
    ${ServerSourcesDir}/server.cpp
)

message("ZiaIncludes: ${openZiaIncludes}")

# Create server library
add_executable(${LIB_NAME} ${ServerSources})
target_link_libraries(${LIB_NAME}
    ${CMAKE_DL_LIBS}
    ${openZiaLibs}
    pthread
    stdc++fs
    ${USED_LIBS}
)
target_include_directories(${LIB_NAME} PRIVATE
    ${Boost_INCLUDE_DIR}
    ${openZiaIncludes}
    ${ServerIncludes}
)
target_compile_options(${LIB_NAME} PRIVATE -fPIC)

message("Generation of ${LIB_NAME} done.")

set_target_properties(server
    PROPERTIES LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
project(server)  # Create project "server"

set(LIB_NAME ${PROJECT_NAME})

set(LIB_PATH "../../lib")

message("Generating project ${PROJECT_NAME}...")

include(${LIB_PATH}/openZia/openZia/openZia.cmake)

get_filename_component(ServerSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

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
)
target_include_directories(${LIB_NAME} PRIVATE
    ${openZiaIncludes}
    ${ServerIncludes}
)
target_compile_options(${LIB_NAME} PRIVATE -fPIC)

message("Generation of ${LIB_NAME} done.")

set_target_properties(server
    PROPERTIES LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
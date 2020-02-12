project(server)  # Create project "server"

message("Generating project ${PROJECT_NAME}...")

get_filename_component(ServerSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(ServerIncludes ${ServerSourcesDir} ../../lib)

set(ServerSources
    ${ServerSourcesDir}/Server.cpp
)

# Create server library
add_executable(${PROJECT_NAME} ${ServerSources})
target_link_libraries(${PROJECT_NAME}
    ${CMAKE_DL_LIBS}
    ${openZiaLibs}
    pthread
    stdc++fs
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${openZiaIncludes}
    ${ServerIncludes}
)
target_compile_options(${PROJECT_NAME} PRIVATE -fPIC)

message("Generation of ${PROJECT_NAME} done.")
# find_package(nlohmann_json REQUIRED)

# include_directories(${NLOHMANN_JSON_INCLUDE_DIRS})
# include_directories(../lib)

# add_executable(server
#     server.cpp
# # ${NLOHMANN_JSON_INCLUDE_DIRS}
# )

# target_link_libraries(server
#     pthread)
# target_link_libraries(server
#     cpp-httplib
# )
set_target_properties(${PROJECT_NAME}
    PROPERTIES LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
project(server)  # Create project "server"

# find_package(nlohmann_json REQUIRED)

# include_directories(${NLOHMANN_JSON_INCLUDE_DIRS})
include_directories(../lib)


add_executable(server
./src/server.cpp
# ${NLOHMANN_JSON_INCLUDE_DIRS}
)

target_link_libraries(server
    pthread)
# target_link_libraries(server
#     cpp-httplib
# )
# set_target_properties(server 
#     PROPERTIES LINKER_LANGUAGE CXX
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
# )
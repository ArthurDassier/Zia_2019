project(tests)  # Create project "tests"

find_package(nlohmann_json REQUIRED)

include_directories(${NLOHMANN_JSON_INCLUDE_DIRS})

add_executable(foo
    ./srcs/test.cpp
    # ${NLOHMANN_JSON_INCLUDE_DIRS}
)

target_link_libraries(foo nlohmann_json)
set_target_properties(foo 
    PROPERTIES LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
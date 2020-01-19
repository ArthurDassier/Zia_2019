project(utils) # Create project "utils"

message("Create project ${PROJECT_NAME}")

add_library(${PROJECT_NAME}
    STATIC
    src/SharedMemory.cpp
)

include_directories(
    ${CMAKE_INCLUDE_PATH}
    ./include
)

target_include_directories(${PROJECT_NAME} INTERFACE
    ./include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CONAN_LIB}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
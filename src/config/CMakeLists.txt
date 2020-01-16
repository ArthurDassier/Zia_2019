project(config) # Create project "config"

find_package(spdlog CONFIG REQUIRED)
if (spdlog_FOUND)
    include_directories(${spdlog_INCLUDE_DIRS})
    link_directories(${spdlog_LIBRARY_DIRS})
endif(spdlog_FOUND)

add_library(${PROJECT_NAME}
    STATIC
    src/Config.cpp
    src/ConfigManager.cpp
    src/FileWatcher.cpp
)

include_directories(
    ${CMAKE_INCLUDE_PATH}
    ${spdlog_INCLUDE_DIR}
    ./include
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
    ./include
)

target_link_libraries(${PROJECT_NAME}
    ${CONAN_LIB}
    stdc++fs
    PRIVATE spdlog::spdlog
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
project(config) # Create project "config"

message("Create project ${PROJECT_NAME}")

find_package(spdlog CONFIG REQUIRED)
if (spdlog_FOUND)
    include_directories(${spdlog_INCLUDE_DIRS})
    link_directories(${spdlog_LIBRARY_DIRS})
endif(spdlog_FOUND)

find_package(nlohmann_json REQUIRED)

# include_directories(${NLOHMANN_JSON_INCLUDE_DIRS})

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

target_include_directories(${PROJECT_NAME} INTERFACE
    ./include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CONAN_LIB}
    nlohmann_json::nlohmann_json
    stdc++fs
    spdlog::spdlog
    utils
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
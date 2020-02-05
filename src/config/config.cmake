project(Config) # Create project "config"

message("Create project ${PROJECT_NAME}")

# Requires C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17 ON)

# Retreive where is located 'config.cmake'
get_filename_component(ConfigSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

# find_package(spdlog CONFIG REQUIRED)
# if (spdlog_FOUND)
#     include_directories(${spdlog_INCLUDE_DIRS})
#     link_directories(${spdlog_LIBRARY_DIRS})
# endif(spdlog_FOUND)

# find_package(nlohmann_json REQUIRED)

# include_directories(${NLOHMANN_JSON_INCLUDE_DIRS})

set(ConfigIncludes ${ConfigSourcesDir}/..)

set(ConfigSources
    ${ConfigSourcesDir}/Config.cpp
    ${ConfigSourcesDir}/Config.hpp
    ${ConfigSourcesDir}/ConfigManager.cpp
    ${ConfigSourcesDir}/ConfigManager.hpp
    ${ConfigSourcesDir}/FileWatcher.cpp
    ${ConfigSourcesDir}/FileWatcher.hpp
)

add_library(${PROJECT_NAME} STATIC ${ConfigSources})

# Create config library
add_library(${PROJECT_NAME} ${ConfigSources})
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} stdc++fs)
target_compile_options(${PROJECT_NAME} PRIVATE -fPIC)

# include_directories(
#     ${CMAKE_INCLUDE_PATH}
#     ${spdlog_INCLUDE_DIR}
#     ./include
# )

# target_include_directories(${PROJECT_NAME} INTERFACE
#     ./include
# )

# target_link_libraries(${PROJECT_NAME} PRIVATE
#     ${CONAN_LIB}
#     nlohmann_json::nlohmann_json
#     stdc++fs
#     spdlog::spdlog
#     utils
# )

# set_target_properties(${PROJECT_NAME}
#     PROPERTIES LINKER_LANGUAGE CXX
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
# )
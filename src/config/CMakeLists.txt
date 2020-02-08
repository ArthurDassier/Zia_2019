# find_package(spdlog CONFIG REQUIRED)
# if (spdlog_FOUND)
#     include_directories(${spdlog_INCLUDE_DIRS})
#     link_directories(${spdlog_LIBRARY_DIRS})
# endif(spdlog_FOUND)

# find_package(nlohmann_json REQUIRED)

# # include_directories(${NLOHMANN_JSON_INCLUDE_DIRS})

# target_link_libraries(${PROJECT_NAME} PRIVATE
#     ${CONAN_LIB}
#     nlohmann_json::nlohmann_json
#     stdc++fs
#     spdlog::spdlog
#     utils
# )

project(config) # Create project "config"

message("Generating project ${PROJECT_NAME}...")

# Retreive where is located 'config.cmake'
get_filename_component(ConfigSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(ConfigIncludes ${ConfigSourcesDir})

set(ConfigSources
    ${ConfigSourcesDir}/Config.cpp
    ${ConfigSourcesDir}/ConfigManager.cpp
    ${ConfigSourcesDir}/FileWatcher.cpp
)

# Create config library
add_library(${PROJECT_NAME} ${ConfigSources})
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} stdc++fs utils)
target_include_directories(${PROJECT_NAME} PUBLIC ${ConfigIncludes})
target_compile_options(${PROJECT_NAME} PRIVATE -fPIC)

message("Generation of ${PROJECT_NAME} done.")
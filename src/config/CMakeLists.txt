# find_package(spdlog CONFIG REQUIRED)
# if (spdlog_FOUND)
#     include_directories(${spdlog_INCLUDE_DIRS})
#     link_directories(${spdlog_LIBRARY_DIRS})
# endif(spdlog_FOUND)


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

get_filename_component(ConfigSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(ConfigIncludes ${ConfigSourcesDir})

set(ConfigSources
    ${ConfigSourcesDir}/Config.cpp
    ${ConfigSourcesDir}/ConfigManager.cpp
    ${ConfigSourcesDir}/FileWatcher.cpp
)

find_package(nlohmann_json 3.7.3 REQUIRED)

# Create config library
if(nlohmann_json_FOUND)
    add_library(${PROJECT_NAME} ${ConfigSources})

    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${CMAKE_DL_LIBS}
        ${CONAN_LIBS}
        nlohmann_json::nlohmann_json
        stdc++fs
        utils
    )
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${ConfigIncludes}
        ${NLOHMANN_JSON_INCLUDE_DIRS}
    )
    target_compile_options(${PROJECT_NAME} PRIVATE -fPIC)

    include_directories()

    message("Generation of ${PROJECT_NAME} done.")
else()
    message("Cannot find nlohmann_json")
endif()
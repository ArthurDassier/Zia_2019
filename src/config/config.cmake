project(config) # Create project "config"

message("Generating project ${PROJECT_NAME}...")

get_filename_component(ConfigSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(ConfigLibs ${PROJECT_NAME})
set(ConfigIncludes ${ConfigSourcesDir})

set(ConfigSources
    ${ConfigSourcesDir}/Config.cpp
    ${ConfigSourcesDir}/ConfigManager.cpp
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
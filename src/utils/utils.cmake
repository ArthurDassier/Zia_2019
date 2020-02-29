project(utils) # Create project "utils"

message("Generating project ${PROJECT_NAME}...")

get_filename_component(UtilsSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(UtilsLibs ${PROJECT_NAME})
set(UtilsIncludes ${UtilsSourcesDir})

set(UtilsSources
    ${UtilsSourcesDir}/EnvManager.cpp
    ${UtilsSourcesDir}/JsonLoader.cpp

)

find_package(nlohmann_json 3.7.3 REQUIRED)

# Create utils library
if(nlohmann_json_FOUND)
    add_library(${PROJECT_NAME} ${UtilsSources})

    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${CMAKE_DL_LIBS}
        ${CONAN_LIBS}
        nlohmann_json::nlohmann_json
        stdc++fs
    )
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${UtilsIncludes}
        ${NLOHMANN_JSON_INCLUDE_DIRS}
    )
    target_compile_options(${PROJECT_NAME} PRIVATE -fPIC)

    include_directories()

    message("Generation of ${PROJECT_NAME} done.")
else()
    message("Cannot find nlohmann_json")
endif()
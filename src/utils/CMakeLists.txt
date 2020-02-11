project(utils) # Create project "utils"

message("Generating project ${PROJECT_NAME}...")

get_filename_component(UtilsSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(UtilsIncludes ${UtilsSourcesDir})

set(UtilsSources
    ${UtilsSourcesDir}/SharedMemory.cpp
)

# Create utils library
add_library(${PROJECT_NAME} ${UtilsSources})
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} pthread stdc++fs)
target_include_directories(${PROJECT_NAME} PUBLIC ${UtilsIncludes})
target_compile_options(${PROJECT_NAME} PRIVATE -fPIC)

message("Generation of ${PROJECT_NAME} done.")
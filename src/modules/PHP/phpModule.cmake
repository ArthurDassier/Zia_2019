project(phpModule)

message("Generating project ${PROJECT_NAME}...")

get_filename_component(PHPModuleSourcesDir ${CMAKE_CURRENT_LIST_FILE}  PATH)

set(PHPModuleLibs ${PROJECT_NAME})
set(PHPModuleIncludes ${PHPModuleSourcesDir})

set(PHPModuleSources
	${PHPModuleSourcesDir}/PHPModule.cpp
)

# Create phpMobule library
add_library(${PROJECT_NAME} SHARED ${PHPModuleSources})
target_link_libraries(${PROJECT_NAME} ${openZiaLibs})
target_include_directories(${PROJECT_NAME} PRIVATE ${openZiaIncludes})

# Copy the library into the lib modules directory
set_target_properties(${PROJECT_NAME} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/lib/modules
)
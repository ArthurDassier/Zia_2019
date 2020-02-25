project(fillPageModule)

message("Generating project ${PROJECT_NAME}...")

get_filename_component(fillPageModuleSourcesDir ${CMAKE_CURRENT_LIST_FILE}  PATH)

set(fillPageModuleSources
	${fillPageModuleSourcesDir}/FillPage.cpp
	${fillPageModuleSourcesDir}/FillPage.hpp
)

# Create parserModule library
add_library(${PROJECT_NAME} SHARED ${fillPageModuleSources})
target_link_libraries(${PROJECT_NAME} ${openZiaLibs})
target_include_directories(${PROJECT_NAME} PRIVATE ${openZiaIncludes})

# Copy the library into the lib modules directory
set_target_properties(${PROJECT_NAME} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/lib/modules
)
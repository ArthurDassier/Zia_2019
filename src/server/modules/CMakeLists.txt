# Template.cmake
project(ParserModule)

# Save this directory as TemplateSourcesDir
get_filename_component(ParserHTTPSourcesDir ${CMAKE_CURRENT_LIST_FILE}  PATH)

set(ParserHTTPSources
	${ParserHTTPSourcesDir}/ParserModule.cpp
	${ParserHTTPSourcesDir}/ParserModule.hpp
)

# Compile the module, and link it to openZia
add_library(${PROJECT_NAME} SHARED ${ParserHTTPSources})
target_link_libraries(${PROJECT_NAME} ${openZiaLibs})
target_include_directories(${PROJECT_NAME} PRIVATE ${openZiaIncludes})

# Copy the library into the binary modules directory
set_target_properties(${PROJECT_NAME} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/server/modules
)
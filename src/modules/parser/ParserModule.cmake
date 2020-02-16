# Template.cmake
project(ParserModule)

# Save this directory as TemplateSourcesDir
get_filename_component(ParserModuleSourcesDir ${CMAKE_CURRENT_LIST_FILE}  PATH)

set(ParserModuleSources
	${ParserModuleSourcesDir}/ParserModule.cpp
	${ParserModuleSourcesDir}/ParserModule.hpp
)

# Compile the module, and link it to openZia
add_library(${PROJECT_NAME} SHARED ${ParserModuleSources})
target_link_libraries(${PROJECT_NAME} ${openZiaLibs})
target_include_directories(${PROJECT_NAME} PRIVATE ${openZiaIncludes})

# Copy the library into the binary modules directory
set_target_properties(${PROJECT_NAME} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}
)
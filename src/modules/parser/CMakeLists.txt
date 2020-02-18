project(parserModule)

message("Generating project ${PROJECT_NAME}...")

get_filename_component(ParserModuleSourcesDir ${CMAKE_CURRENT_LIST_FILE}  PATH)

set(ParserModuleSources
	${ParserModuleSourcesDir}/ParserModule.cpp
	${ParserModuleSourcesDir}/ParserModule.hpp
)

# Create parserModule library
add_library(${PROJECT_NAME} SHARED ${ParserModuleSources})
target_link_libraries(${PROJECT_NAME} ${openZiaLibs})
target_include_directories(${PROJECT_NAME} PRIVATE ${openZiaIncludes})

# Copy the library into the lib modules directory
set_target_properties(${PROJECT_NAME} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/lib/modules
)
# Template.cmake
project(ParserHTTP)

# Save this directory as TemplateSourcesDir
get_filename_component(ParserHTTPSourcesDir ${CMAKE_CURRENT_LIST_FILE}  PATH)

set(ParserHTTPSources
	${ParserHTTPSourcesDir}/ParserHTTP.cpp
	${ParserHTTPSourcesDir}/ParserHTTP.hpp
)

# Compile the module, and link it to openZia
add_library(${PROJECT_NAME} SHARED ${ParserHTTPSources})
target_link_libraries(${PROJECT_NAME} ${openZiaLibs})
target_include_directories(${PROJECT_NAME} PRIVATE ${openZiaIncludes})

# Copy the library into the binary modules directory
set_target_properties(${PROJECT_NAME} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/Modules
)

# install(TARGETS ${PROJECT_NAME} EXPORT ParserModule
#     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
project(parser)

message("Generating project ${PROJECT_NAME}...")

# Retreive where is located 'config.cmake'
get_filename_component(ParserSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(ParserIncludes ${ParserSourcesDir})

set(ParserSources
    ${ParserSourcesDir}/ParserModule.cpp
)

# Create parser library
add_library(${PROJECT_NAME} SHARED ${ParserSources})
target_link_libraries(${PROJECT_NAME} ${openZiaLibs})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${ParserIncludes}
    ${openZiaIncludes}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/server/modules
)

# set(LIB_PATH "${PROJECT_SOURCE_DIR")

install(TARGETS ${PROJECT_NAME} EXPORT ParserModule
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
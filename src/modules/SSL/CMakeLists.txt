# Template.cmake
project(SSLModule)

message("Generating project ${PROJECT_NAME}...")

# Save this directory as TemplateSourcesDir
get_filename_component(SSLModuleSourcesDir ${CMAKE_CURRENT_LIST_FILE}  PATH)

set(SSLModuleSources
	${SSLModuleSourcesDir}/SSLModule.cpp
	${SSLModuleSourcesDir}/SSLModule.hpp
)

# Compile the module, and link it to openZia
add_library(${PROJECT_NAME} SHARED ${SSLModuleSources})
target_link_libraries(${PROJECT_NAME} ${openZiaLibs} -lcrypto -lssl -g3)
target_include_directories(${PROJECT_NAME} PRIVATE ${openZiaIncludes})

# Copy the library into the binary modules directory
set_target_properties(${PROJECT_NAME} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib/modules
)

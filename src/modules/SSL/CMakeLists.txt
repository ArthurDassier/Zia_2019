project(SSLModule)

message("Generating project ${PROJECT_NAME}...")

get_filename_component(SSLModuleSourcesDir ${CMAKE_CURRENT_LIST_FILE}  PATH)

set(SSLModuleSources
	${SSLModuleSourcesDir}/SSLModule.cpp
	${SSLModuleSourcesDir}/SSLModule.hpp
)

# Create SSLmodules library
add_library(${PROJECT_NAME} SHARED ${SSLModuleSources})
target_link_libraries(${PROJECT_NAME} ${openZiaLibs} -lcrypto -lssl -g3)
target_include_directories(${PROJECT_NAME} PRIVATE ${openZiaIncludes})

# Copy the library into the modules directory
set_target_properties(${PROJECT_NAME} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/lib/modules
)

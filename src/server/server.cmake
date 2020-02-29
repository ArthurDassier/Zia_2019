project(server) # Create project "server"

add_definitions(-fPIC)

get_filename_component(ServerSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.42.0 REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

set(USED_LIBS
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
)

set(ServerLibs ${PROJECT_NAME})
set(ServerIncludes ${ServerSourcesDir})

set(ServerSources
	${ServerSourcesDir}/Connection.cpp
    ${ServerSourcesDir}/ConnectionManager.cpp
    ${ServerSourcesDir}/Log.cpp
    ${ServerSourcesDir}/Module.cpp
    ${ServerSourcesDir}/Server.cpp
    ${ServerSourcesDir}/ServerConfig.cpp
)

# Create server library
add_library(${PROJECT_NAME} ${ServerSources})
target_link_libraries(${PROJECT_NAME}
    ${openZiaLibs}
    ${ConfigLibs}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${Boost_INCLUDE_DIR}
    ${openZiaIncludes}
    ${ServerIncludes}
    ${ConfigIncludes}
)
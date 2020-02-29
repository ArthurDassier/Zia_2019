project(ziaTest)

# Retreive where is located 'test.cmake'
get_filename_component(ZiaSourcesTestDir ${CMAKE_CURRENT_LIST_FILE} PATH)

message("Compiling criterion unit-tests for zia project")

set(FillModuleTestDir ${ZiaSourcesTestDir}/testFillModule/modules)
set(ParserModuleTestDir ${ZiaSourcesTestDir}/testParserModule/modules)
set(PHPModuleTestDir ${ZiaSourcesTestDir}/testPHPModule/modules)

set(TestSources
    # ${ZiaSourcesTestDir}/{...}.cpp
    ${ZiaSourcesTestDir}/testParserModule/parserModuleTest.cpp
    ${ZiaSourcesTestDir}/testFillModule/fillModuleTest.cpp
)

set(TMP)

configure_file(${LibModulesDir}/libfillPageModule.so ${FillModuleTestDir} COPYONLY)
configure_file(${LibModulesDir}/libfillPageModule.so ${PHPModuleTestDir} COPYONLY)

configure_file(${LibModulesDir}/libparserModule.so ${FillModuleTestDir} COPYONLY)
configure_file(${LibModulesDir}/libparserModule.so ${ParserModuleTestDir} COPYONLY)
configure_file(${LibModulesDir}/libparserModule.so ${PHPModuleTestDir} COPYONLY)

configure_file(${LibModulesDir}/libphpModule.so ${PHPModuleTestDir} COPYONLY)

# Add a foo library for testing purposes
# set(FooSources
#     ${ZiaSourcesTestDir}/Medias/FooModule.hpp
#     ${ZiaSourcesTestDir}/Medias/FooModule.cpp
# )
# add_library(Foo SHARED ${FooSources})
# target_link_libraries(Foo zia)
# target_include_directories(Foo PRIVATE ${openZiaIncludes})

add_executable(${PROJECT_NAME} ${TestSources} ${ZiaSources})
target_link_libraries(${PROJECT_NAME} criterion ${CMAKE_DL_LIBS} ${openZiaLibs} stdc++fs)
target_include_directories(${PROJECT_NAME} PRIVATE ${ZiaIncludes} ${openZiaIncludes})

if(${ZIA_COVERAGE})
    target_link_libraries(${PROJECT_NAME} gcov)
    target_compile_options(${PROJECT_NAME} PUBLIC --coverage)
endif()
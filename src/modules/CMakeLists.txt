project(modules)    # Create project "modules"

message("Adding all modules subdirectory...")

include(fillPage/fillPageModule.cmake)
include(parser/parserModule.cmake)
include(PHP/phpModule.cmake)
include(SSL/sslModule.cmake)
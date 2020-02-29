project(src)    # Create project "src"

message("Adding all source subdirectory...")

include(config/config.cmake)
add_subdirectory(modules)
include(server/server.cmake)
include(utils/utils.cmake)
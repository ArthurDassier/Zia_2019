project(src)    # Create project "src"

message("Adding all source subdirectory...")

include(config/config.cmake)
add_subdirectory(modules)
add_subdirectory(server)
include(utils/utils.cmake)

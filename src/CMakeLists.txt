project(src)    # Create project "src"

message("Adding all source subdirectory...")

add_subdirectory(config)
add_subdirectory(server)
add_subdirectory(utils)
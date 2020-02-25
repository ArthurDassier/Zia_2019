project(modules)    # Create project "modules"

message("Adding all modules subdirectory...")

add_subdirectory(parser)
add_subdirectory(fillPage)
add_subdirectory(php_cgi)
add_subdirectory(SSL)
add_library(cli CLI.cpp CLIBase.cpp CLICommands.cpp CLIServer.cpp)

target_link_libraries(cli control)

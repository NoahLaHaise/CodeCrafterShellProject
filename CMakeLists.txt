cmake_minimum_required(VERSION 3.16)
project(MyProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Export compile commands for clangd (critical for Neovim LSP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(my_app
    src/main.cpp
)

target_include_directories(my_app PRIVATE include)

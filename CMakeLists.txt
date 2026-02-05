cmake_minimum_required(VERSION 3.15)
project(PankeyEngineApplicationSystem)

# Header-only library
add_library(PankeyEngineApplicationSystem INTERFACE)

# Expose the folder with headers
target_include_directories(PankeyEngineApplicationSystem INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}   # headers are in the root of ThePankeyEngine-ApplicationSystem
)


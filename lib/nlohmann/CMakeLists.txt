# cmake_minimum_required(VERSION 3.10)

# add_library(nlohmann INTERFACE)

# # Add the include directory
# target_include_directories(nlohmann INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
cmake_minimum_required(VERSION 3.10)

add_library(nlohmann STATIC)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(nlohmann)
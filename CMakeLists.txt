cmake_minimum_required(VERSION 3.11)
cmake_policy(SET CMP0072 NEW)

project(THE_TRAIN_SNCF_IMAC1)

# Set the folder where the executable will be created
set(OUTPUT_BIN_FOLDER ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Librairies

# ---Add GL---
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
set(ALL_LIBRARIES ${OPENGL_LIBRARIES})

# ---Add GLFW---
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glfw)

# ---Add glad---
add_library(glad lib/glad/src/glad.c)
include_directories(lib/glad/include)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glad)

# ---Add glbasimac---
add_subdirectory(lib/glbasimac)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glbasimac)
include_directories(lib/glbasimac/)
set(CMAKE_COLOR_MAKEFILE ON)

# ---Add json---
include_directories(lib/json)

add_subdirectory(src)

add_custom_target(src_custom
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target src_target
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# foreach(TD ${TD_DIRECTORIES})
#     add_subdirectory(SRC_DIRECTORY)
# 	get_filename_component(DIRN SRC_DIRECTORY NAME)
#     add_custom_target(${DIRN} COMMAND cd ${CMAKE_CURRENT_BINARY_DIR}/${DIRN} COMMAND make
#                 WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${DIRN})
# endforeach()

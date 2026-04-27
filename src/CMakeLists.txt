file(GLOB HEADER_FILES *.hpp)
file(GLOB SRC_FILES *.cpp)

get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(OUTPUT main)

add_executable(${OUTPUT} ${SRC_FILES} ${HEADER_FILES})
target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})
set_target_properties(${OUTPUT} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
set_target_properties(${OUTPUT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
if (MSVC)
    target_compile_options(${OUTPUT} PRIVATE /W3)
else()
    target_compile_options(${OUTPUT} PRIVATE -Wall -Wextra)
endif()
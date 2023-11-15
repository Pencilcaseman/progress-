cmake_minimum_required(VERSION 3.16)
project(progressive)

add_library(progressive INTERFACE)
target_include_directories(progressive INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(NOT TARGET fmt)
    add_subdirectory(vendor/fmt)
endif()

target_link_libraries(progressive INTERFACE fmt::fmt)

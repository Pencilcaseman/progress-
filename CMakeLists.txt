cmake_minimum_required(VERSION 3.16)
project(progressive)

add_library(progressive STATIC
        include/progressive/charset.hpp
        include/progressive/progress.hpp
        include/progressive/utils.hpp)
target_include_directories(progressive PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(vendor/fmt)
target_link_libraries(progressive PRIVATE fmt::fmt)

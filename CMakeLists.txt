cmake_minimum_required(VERSION 3.10)
set(MM2YUZUFRONTEND_VERSION "0.0.1")
project(mm2yuzufrontend VERSION ${MM2YUZUFRONTEND_VERSION})

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(mm2yuzufrontend)
add_subdirectory(main)
add_subdirectory(test)
add_custom_target(mm2yuzufrontend_all ALL DEPENDS main test)
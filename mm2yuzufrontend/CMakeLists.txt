cmake_minimum_required(VERSION 3.10)
project(mm2yuzufrontend)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wno-sign-compare)
add_compile_options(-Wno-deprecated-declarations)
add_compile_options(-Wno-unused-parameter)
add_compile_options(-Wno-extern-initializer)

if(CMAKE_BUILD_TYPE EQUAL "DEBUG")
	add_link_options(-g -O0)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/tiny_aes ${CMAKE_CURRENT_BINARY_DIR}/third_party/tiny_aes)

set(mm2yuzufrontend_SOURCES
	src/savedat.cpp
)

add_library(mm2yuzufrontend STATIC ${mm2yuzufrontend_SOURCES})
set_target_properties(mm2yuzufrontend PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_options(mm2yuzufrontend PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-missing-braces)

if(WIN32)
	target_link_libraries(mm2yuzufrontend PUBLIC tiny-aes gdi32 opengl32)
endif()
target_include_directories(mm2yuzufrontend PUBLIC include tiny-aes)
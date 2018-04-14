project(alarm)
cmake_minimum_required(VERSION 2.8)

file(MAKE_DIRECTORY bin)

file(GLOB HEADER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
file(GLOB SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
include_directories(LIB_PATH HEADER_PATH)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS     "-std=c99")
set(CMAKE_CXX_FLAGS   "-g")            
set(CMAKE_CXX_FLAGS   "-Wall")
set(EXECUTABLE_OUTPUT_PATH ./bin)

add_executable(${PROJECT_NAME} ${SOURCE_PATH})
target_link_libraries(${PROJECT_NAME} ev m)

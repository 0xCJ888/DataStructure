project(alarm)
cmake_minimum_required(VERSION 2.8)




file(GLOB HEADER_PATH ./src/*.h)
file(GLOB LIB_PATH ./lib/*.h)
file(GLOB SOURCE_PATH ./src/*.c)
include_directories(LIB_PATH HEADER_PATH)
link_directories(./lib)

set(CMAKE_CXX_FLAGS     "-std=c99")
set(CMAKE_CXX_FLAGS   "-g")            
set(CMAKE_CXX_FLAGS   "-Wall")
set(EXECUTABLE_OUTPUT_PATH ./bin)

add_executable(${PROJECT_NAME} ${SOURCE_PATH})
target_link_libraries(${PROJECT_NAME} ev m)

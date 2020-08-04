cmake_minimum_required(VERSION 2.8)
project(slamVisualization)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "Release")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_package(OpenCV 3.2 REQUIRED)
find_package(Pangolin 0.4 REQUIRED)
include_directories(
    ${Pangolin_INCLUDE_DIRS} 
    ${OpenCV_INCLUDE_LIBS}
    ${PROJECT_SOURCE_DIR}/include
    "/usr/include/eigen3"
)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
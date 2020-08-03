
find_package(Pangolin 0.4 REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(drawLine drawLine.cpp)
target_link_libraries(drawLine ${Pangolin_LIBRARIES})
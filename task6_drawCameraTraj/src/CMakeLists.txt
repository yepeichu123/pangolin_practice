
find_package(Pangolin 0.4 REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(drawCameraTraj drawCameraTraj.cpp)
target_link_libraries(drawCameraTraj ${Pangolin_LIBRARIES})
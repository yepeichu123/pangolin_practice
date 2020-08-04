

add_executable(slamVisualization slamVisualization.cpp main.cpp)
target_link_libraries(slamVisualization ${Pangolin_LIBRARIES} ${OpenCV_LIBS})

find_package(Pangolin  0.4 REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(pangolinControl pangolinControl.cpp)
target_link_libraries(pangolinControl ${Pangolin_LIBRARIES})


find_package(OpenCV 3.2 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRES})

add_executable(multiView multiView.cpp)
target_link_libraries(multiView ${OpenCV_LIBS} ${Pangolin_LIBRARIES})
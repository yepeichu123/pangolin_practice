
find_package(Threads)
find_package(Pangolin  0.4 REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})


add_executable(helloPangolin helloPangolin.cpp)
target_link_libraries(helloPangolin ${Pangolin_LIBRARIES})

add_executable(MultiThreadHelloPangolin MultiThreadHelloPangolin.cpp)
target_link_libraries(MultiThreadHelloPangolin ${Pangolin_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

cmake_minimum_required(VERSION 3.15)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(threadpool_quicksort
    lib/ThreadPool.cpp
    lib/QuickSort.cpp
)
add_executable(main_app
    app/main.cpp
)
target_link_libraries(main_app PRIVATE threadpool_quicksort)

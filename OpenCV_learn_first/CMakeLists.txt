cmake_minimum_required(VERSION 3.22)

project(OpenCV_learn_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR "/usr/local/lib/cmake/opencv5")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(app ./src/main.cpp)
target_link_libraries(app PRIVATE ${OpenCV_LIBS})
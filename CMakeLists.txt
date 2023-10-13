cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME Lolidance)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置变量，用于存储所有的 .cpp 文件
file(GLOB CPP_SOURCES "*.cpp")

# 打印所有的 .cpp 文件
foreach(source ${CPP_SOURCES})
    message("Found .cpp file: ${source}")
endforeach()

# 播放视频帧
set(EXE_NAME Lolidance)
add_executable(${EXE_NAME} main.cpp)

# 提取视频帧
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(OpenCV_DIR /opt/homebrew/Cellar/opencv/4.8.1_1)
add_executable(videoCapture videocapture.cpp)
target_include_directories(videoCapture PRIVATE ${OpenCV_DIR}/include)
target_link_libraries(videoCapture ${OpenCV_LIBRARIES})


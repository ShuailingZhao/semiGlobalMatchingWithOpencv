cmake_minimum_required(VERSION 2.8)
project(getDisFromHomograph)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE "Debug")
#set("OpenCV_DIR" "/usr/local/share/OpenCV")
set("OpenCV_DIR" "/home/zhaosl/dataDisk/zhaosl/local_install/opencv3.1.0/share/OpenCV/")
#set("OpenCV_DIR" "/home/zhaosl/local_install/opencv2.4.13/lib")
find_package( OpenCV REQUIRED )
MESSAGE("OpenCV vesion: ${OpenCV_VERSION}")
find_package( Ceres REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS})
include_directories( ${CERES_INCLUDE_DIRS})


set(PROJECT_ROOT ".")
include_directories(${PROJECT_ROOT}/include)
set(MODULE_SRC_ROOT ${PROJECT_ROOT}/src/)

file(GLOB src_testSgbm_files ${MODULE_SRC_ROOT}/testSgbm.cpp ${MODULE_SRC_ROOT}/sgbmWithOpencv.cpp)
add_executable(testSgbm ${src_testSgbm_files})
target_link_libraries(testSgbm ${OpenCV_LIBS})

SET(PROJECT_NAME SLAM)

PROJECT(${PROJECT_NAME})
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(BUILD_TYPE Release)

set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# required libraries
find_package(Eigen3 REQUIRED)
#find_package(LibZip REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system thread)

set(CMAKE_CXX_FLAGS
   "${CMAKE_CXX_FLAGS_RELEASE} ${SSE_FLAGS} -std=c++0x"
)


include_directories(
  ${PROJECT_SOURCE_DIR}/inc
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/thirdparty/tum_reader/src
  ${EIGEN3_INCLUDE_DIR}
  ${LIBZIP_INCLUDE_DIR_ZIP}
  ${LIBZIP_INCLUDE_DIR_ZIPCONF}
  ${OpenCV_INCLUDE_DIRS}
)


set(slam_SOURCE_FILES
  ${PROJECT_SOURCE_DIR}/src/frameProvider.cpp
  ${PROJECT_SOURCE_DIR}/src/landmarksManager.cpp
  ${PROJECT_SOURCE_DIR}/src/debugging.cpp
  ${PROJECT_SOURCE_DIR}/src/tracking.cpp
  ${PROJECT_SOURCE_DIR}/thirdparty/tum_reader/src/FOVUndistorter.cpp
  ${PROJECT_SOURCE_DIR}/thirdparty/tum_reader/src/PhotometricUndistorter.cpp
)
add_library(slam_libs ${slam_SOURCE_FILES})
set(BOOST_THREAD_LIBRARY boost_thread)

add_executable(SLAM ${PROJECT_SOURCE_DIR}/src/slam.cpp )
target_link_libraries(SLAM
                      slam_libs
                      boost_system
                      ${BOOST_THREAD_LIBRARY}
                      ${LIBZIP_LIBRARY}
                      ${OpenCV_LIBS})

SET(PROJECT_NAME SLAM)

PROJECT(${PROJECT_NAME})
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(BUILD_TYPE Release)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(EXECUTABLE_OUTPUT_PATH bin)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS
   "${CMAKE_CXX_FLAGS_RELEASE} ${SSE_FLAGS} -std=c++0x"
)



add_executable(SLAM src/slam.cpp)
target_link_libraries(SLAM ${OpenCV_LIBS})

SET(CMAKE_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/lib/cmake/ )
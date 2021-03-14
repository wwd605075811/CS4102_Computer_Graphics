cmake_minimum_required(VERSION 3.10)
project(BezierCurve)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(BezierCurve main.cpp bezier_curve.cpp bezier_curve.h convexHull.h)

target_link_libraries(BezierCurve ${OpenCV_LIBRARIES})

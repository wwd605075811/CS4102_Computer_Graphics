//
// Created by wendell on 07/03/2021.
//
#ifndef BEZIERCURVE_BEZIER_CURVE_H
#define BEZIERCURVE_BEZIER_CURVE_H
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;

class bezier_curve {
public:
    cv::Point2f draw_bezier(std::vector<cv::Point2f> control_points, int degree, int index, double t);
    cv::Point2f one_bezier_curve(cv::Point2f pointA, cv::Point2f pointB, double t);
    void test(std::vector<cv::Point2f> control_points);
};
#endif //BEZIERCURVE_BEZIER_CURVE_H
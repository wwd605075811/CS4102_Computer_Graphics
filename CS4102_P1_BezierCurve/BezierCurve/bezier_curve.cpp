//
// Created by wendell on 07/03/2021.
//
#include "bezier_curve.h"
//https://zhuanlan.zhihu.com/p/268031177 , Calculate points using recursive method
cv::Point2f bezier_curve::draw_bezier(std::vector<cv::Point2f> control_points, int degree, int index, double t) {
    if(degree == 1) {
        return one_bezier_curve(control_points[index], control_points[index], t);
    } else {
        return (1 - t) * draw_bezier(control_points, degree -1, index, t)
        + t * draw_bezier(control_points, degree -1, index + 1, t);
    }
}

//the end condition of recursive method
cv::Point2f bezier_curve::one_bezier_curve(cv::Point2f pointA, cv::Point2f pointB, double t) {
    return (1 - t) * pointA + t * pointB;
}

void bezier_curve::test(std::vector<cv::Point2f> control_points) {
    cout << "this is the test!" << endl;
    /*cv::Point2f p1(5,1);
    cv::Point2f p2(3,4);
    cv::Point2f p3 = 0.5 * p1 + 0.5 * p2;
    cout << p1 << "\n" << p2 << "\n" << p3 << endl;*/
    //cout << "size: " <<control_points.size() << endl;
    for (int i = 0; i < control_points.size(); ++i) {
        cout << control_points[i] << endl;
    }
    //cout << "^^^^^^^^^^" << endl;
    cv::Point2f result = draw_bezier(control_points, control_points.size(), 0, 0.5);
    //cout << "result :" << result << endl;
}
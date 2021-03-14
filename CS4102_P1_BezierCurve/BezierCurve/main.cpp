//
// Created by wendell on 07/03/2021.
//
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stack>
#include <stdlib.h>
#include "bezier_curve.h"
#include "convexHull.h"
using namespace cv;
using namespace std;

//control points set
std::vector<cv::Point2f> control_points;
//visual window
cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
//the flag that make sure user use the right click to select the point
int select_single = -1;
// the index of the points which be selected
int select_index = -1;

// draw bezier curve, call bezier_curve.h.
void bezier(const std::vector<cv::Point2f> &points, cv::Mat &window);
// draw convex hull, call convexHull.h
std::vector<cv::Point2f> calConvexHull (const std::vector<cv::Point2f> &control_points);
//the function to choose the point which user want to move
//the implementation scheme is to delete and add drag points in real time.
bool delete_point(std::vector<cv::Point2f> &control_points, cv::Point2f p0);
//mouse event function
void mouse(int event, int x, int y, int flags, void *userdata);


int main() {
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback("Bezier Curve", mouse, nullptr);

    int key = -1;
    while (key != 27) {
        Point2f p0(317,223);
        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }
    return 0;
}

bool delete_point(std::vector<cv::Point2f> &control_points, cv::Point2f p0) {
    int i = 0;
    for (std::vector<cv::Point2f>::iterator it=control_points.begin(); it!=control_points.end(); it++) {
        if(abs(it->x - p0.x) < 10 && abs(it->y - p0.y) < 10) {
            select_index = i;
            return true;
        }
        i++;
    }
    return false;
}

void mouse(int event, int x, int y, int flags, void *userdata) {
    //left click to add points to window
    if (event == EVENT_LBUTTONDOWN) {
        Point(x,y);
        cout << "Left button position (" << x << ", " << y << ")" << '\n';
        control_points.emplace_back(x, y);
        for (auto &point : control_points) {
            cv::circle(window, point, 3, {255, 0, 0}, 3);
        }
        if(control_points.size() > 2) {
            window.setTo(Scalar(0,0,0));
            for (auto &point : control_points) {
                cv::circle(window, point, 3, {255, 0, 0}, 3);
            }
            bezier(control_points, window);

            std::vector<cv::Point2f> result = calConvexHull(control_points);

            for (int i = 0; i < result.size() - 1; ++i) {
                line(window, result[i], result[i+1], Scalar(124, 255, 255), 2);
            }
            line(window, result[result.size() - 1], result[0], Scalar(124, 255, 255), 2);
        }
    }
    // right click to choose point, which user want to move
    if (event == EVENT_RBUTTONDOWN) {
        Point2f p0(x,y);
        cout << p0 << " Right" << endl;
        //control_points.emplace_back(x, y);
        if(delete_point(control_points,p0)) {
            select_single = 1;
            cout << "select correct!" << endl;
        } else {
            cerr << "select error!" << endl;
        }
    }
    // use mouse move event to drag one point in the control points
    // and show the bezier curve and convex hull in real-time
    if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_CTRLKEY)) {
        if (select_single == 1) {
            Point2f p0(x,y);
            //control_points.pop_back();
            control_points.erase(control_points.begin() + select_index);
            control_points.insert(control_points.begin() + select_index, p0);
            //clean the window
            window.setTo(Scalar(0,0,0));
            cout << "x: " << x << " y: " << y << " control_points size: " << control_points.size() <<endl;
            for (auto &point : control_points) {
                cv::circle(window, point, 3, {255, 0, 0}, 3);
            }
            bezier(control_points, window);

            std::vector<cv::Point2f> result = calConvexHull(control_points);

            for (int i = 0; i < result.size() - 1; ++i) {
                line(window, result[i], result[i+1], Scalar(124, 255, 255), 2);
            }
            line(window, result[result.size() - 1], result[0], Scalar(124, 255, 255), 2);
        }
    }
}

std::vector<cv::Point2f> calConvexHull (const std::vector<cv::Point2f> &control_points) {
    int size = control_points.size();
    Point_Q points[size];
    for (int i = 0; i < size; ++i) {
        points[i].x =  control_points[i].x;
        points[i].y =  control_points[i].y;
    }
    int n = sizeof(points)/sizeof(points[0]);
    stack<Point_Q> S = convexHull(points, n);
    std::vector<cv::Point2f> result;
    while (!S.empty())
    {
        Point_Q p = S.top();
        result.emplace_back(p.x,p.y);
        S.pop();
    }
    return result;
}

void bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) {
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];
    auto &p_4 = points[4];
    bezier_curve b1;
    for (double t = 0.0; t <= 1.0; t += 0.001) {
        auto point = b1.draw_bezier(control_points, control_points.size(), 0, t);
        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

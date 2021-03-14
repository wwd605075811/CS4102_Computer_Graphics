//
// Created by wendell on 10/03/2021.
//
#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;

struct Point_Q {
    int x, y;
};

// A global point needed for sorting points with reference
// to the first point Used in compare function of qsort()
Point_Q pCH;

// A utility function to find next to top in a stack
Point_Q nextToTop(stack<Point_Q> &S) {
    Point_Q p = S.top();
    S.pop();
    Point_Q res = S.top();
    S.push(p);
    return res;
}

// A utility function to swap two points
void swap(Point_Q &p1, Point_Q &p2) {
    Point_Q temp = p1;
    p1 = p2;
    p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(Point_Q p1, Point_Q p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) +
           (p1.y - p2.y)*(p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
int orientation(Point_Q p, Point_Q q, Point_Q r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0; // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of points with respect to the first point
int compare(const void *vp1, const void *vp2) {
    Point_Q *p1 = (Point_Q *)vp1;
    Point_Q *p2 = (Point_Q *)vp2;

// Find orientation
    int o = orientation(pCH, *p1, *p2);
    if (o == 0)
        return (distSq(pCH, *p2) >= distSq(pCH, *p1)) ? -1 : 1;

    return (o == 2)? -1: 1;
}

// Prints convex hull of a set of n points.
stack<Point_Q> convexHull(Point_Q points[], int n) {
    // Find the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        // Pick the bottom-most or chose the left
        // most point in case of tie
        if ((y < ymin) || (ymin == y &&
                           points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // Place the bottom-most point at first position
    swap(points[0], points[min]);
    pCH = points[0];
    qsort(&points[1], n-1, sizeof(Point_Q), compare);

    // If two or more points make same angle with pCH,
    // Remove all but the one that is farthest from pCH
    // Remember that, in above sorting, our criteria was
    // to keep the farthest point at the end when more than
    // one points have same angle.
    int m = 1; // Initialize size of modified array
    for (int i=1; i<n; i++) {
        // Keep removing i while angle of i and i+1 is same
        // with respect to pCH
        while (i < n-1 && orientation(pCH, points[i],
                                      points[i+1]) == 0)
            i++;
        points[m] = points[i];
        m++; // Update size of modified array
    }
    // If modified array of points has less than 3 points, convex hull is not possible
    if (m < 3) exit(0);

    // Create an empty stack and push first three points to it.
    stack<Point_Q> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Process remaining n-3 points
    for (int i = 3; i < m; i++) {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while (S.size()>1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }
    return S;
}
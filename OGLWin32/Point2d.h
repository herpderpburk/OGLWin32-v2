#pragma once
#include <math.h>
class Point2d
{
private:
    double m_x;
    double m_y;
public:
    Point2d(): m_x(0), m_y(0) {}
    Point2d(double x, double y): m_x(x), m_y(y) {}

    ~Point2d(void) {}
    double X()
    {
        return m_x;
    }
    double Y()
    {
        return m_y;
    }

    static double Distance(Point2d p1, Point2d p2)
    {
        return sqrt(pow((p1.X() - p2.X()), 2) + pow(p1.Y() - p2.Y(), 2));
    }
};


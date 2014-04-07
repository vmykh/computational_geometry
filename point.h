#ifndef POINT_H
#define POINT_H

#include <cmath>

class Point
{
public:
    Point(double x_in=0, double y_in=0)
    {
        x = x_in;
        y = y_in;
    }

    void setPoint(double x_new, double y_new)
    {
        x = x_new;
        y = y_new;
    }
    double distance(Point p2)
    {
        return sqrt(     (this->x - p2.x)* (this->x - p2.x) +  (this->y - p2.y)* (this->y - p2.y)   );
    }

    double x;
    double y;
};

class Vector: public Point
{
public:
    Vector(double x_in=0, double y_in=0)
        :Point(x_in, y_in)
    {

    }

    double dotProduct(Vector v2)
    {
        return this->x * v2.x + this->y * v2.y;
    }
    double crossProduct(Vector v2)
    {
        return this->x * v2.y - v2.x * this->y;
    }
    double Length()
    {
        return sqrt(x*x + y*y);
    }

};

#endif // POINT_H

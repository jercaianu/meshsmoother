#ifndef NORMAL_H
#define NORMAL_H

#include "point.hpp"

class Normal
{
public:
    Point x1, x2;

    Normal() : x1(), x2()
    {}

    Normal(Point p1, Point p2) : x1(p1), x2(p2)
    {}

    const Point getDir() const 
    {
        return x2 - x1;
    }

    void normalize()
    {
        double len = Point::dist(x1, x2);
        Point dir = getDir();
        dir.x /= len;
        dir.y /= len;
        dir.z /= len;
        x2 = x1 + dir;
    }
};

#endif




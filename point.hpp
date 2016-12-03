#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <iostream>
using namespace std;


class Point 
{
public:
    double x, y, z;

    Point() : x(0), y(0), z(0)
    {}

    Point(double newx, double newy, double newz) :
        x(newx), y(newy), z(newz)
    {}

    static double dist(const Point& p1, const Point& p2)
    {
        return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
    }

    Point operator+(const Point& other) 
    {
        return Point(x + other.x, y + other.y, z + other.z);
    }

    Point& operator+=(const Point& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    Point operator-(const Point& other) const 
    {
        return Point(x - other.x, y - other.y, z - other.z);
    }

    Point operator*(double val) const
    {
        return Point(x * val, y * val, z * val);
    }

    friend ostream& operator<<(ostream& os, const Point& p) 
    {
        os << p.x << " " << p.y << " " << p.z;
        return os;
    }

};

extern Point operator*(double val, const Point& other);
#endif

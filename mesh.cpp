#include "mesh.hpp"
#include "point.hpp"
#include <cmath>
#include <algorithm>
using namespace std;


void Mesh::createFromPolylines(
        const double distance, 
        const vector<Polyline>& polylines)
{
    int index = 0;

    for (auto& polyline : polylines) {
        for (auto& n : polyline) {
            indToNormal[index++] = n; 
            normalMesh.push_back(findClosestPoints(n, distance, polylines));
        }
    }
}

vector<Normal> Mesh::findClosestPoints(
        const Normal& n, 
        const double distance, 
        const vector<Polyline>& polylines)
{
    vector<Normal> closestPoints;
    for (auto& polyline : polylines) {
        for (auto& tmpN : polyline) {
            if (Point::dist(tmpN.x1, n.x1) < distance) 
                closestPoints.push_back(tmpN);
        }
    }
    sort(closestPoints.begin(), closestPoints.end(), 
            [&](const Normal& lhs, const Normal& rhs) 
            {
                return Point::dist(lhs.x1, n.x1) < Point::dist(rhs.x1, n.x1);
            });
    return closestPoints; 
}


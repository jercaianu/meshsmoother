#ifndef MESH_H
#define MESH_H

#include <vector>
#include <unordered_map>
#include "polyline.hpp"
#include "point.hpp"

using namespace std;

class Mesh
{
public:
    unordered_map<int, Normal> indToNormal;
    vector<vector<Normal>> normalMesh; 

    void createFromPolylines(
            const double distance, 
            const vector<Polyline>& polylines);

    vector<Normal>findClosestPoints(
            const Normal& n, 
            const double distance, 
            const vector<Polyline>& polylines);
};

#endif



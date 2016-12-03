#include "normal.hpp"
#include "polyline.hpp"
#include "point.hpp"
#include "mesh.hpp"
#include <cmath>
#include <fstream>

using namespace std;

float maxRadius = 100;
Point center;
Mesh mesh;
const double maxDist = 2;
const double smoothDist = 0.4;
vector<Polyline> polySphere;
vector<Polyline> smoothPolySphere;
Mesh newMesh;

extern Point operator*(double val, const Point& other)
{
    return other * val;
}

vector<double> errors {-0.3, 0.3, -0.5, 0,5, 0, 0};

void smoothPolyMesh(const vector<Polyline>& in, vector<Polyline>& out, const double dist)
{
    out = in;
    const double doubleDist = 2 * dist;
    for (int i = 0; i < in.size(); i++) {
        auto& inLine = in[i];
        auto& outLine = out[i];

        for (int j = 0; j < inLine.size(); j++) { 
            Normal currentNormal = inLine[j];
            Point prevPoint;

            double leftDist = 0;
            double rightDist = 0;

            int left = j - 1;
            int right = j + 1;

            prevPoint = inLine[j].x1;
            Point newDir;

            while (left >= 0 && leftDist < dist) {
                leftDist += Point::dist(inLine[left--].x1, prevPoint);
                newDir += (leftDist / doubleDist) * inLine[left + 1].getDir();  
                prevPoint = inLine[left + 1].x1;
            }

            prevPoint = inLine[j].x1;
            while (right < inLine.size() && rightDist < dist) {
                rightDist += Point::dist(inLine[right++].x1, prevPoint);
                newDir += (rightDist / doubleDist) * inLine[right - 1].getDir();  
                prevPoint = inLine[right - 1].x1;
            }

            newDir += 0.5 * inLine[j].getDir();
            outLine[j].x2 = outLine[j].x1 + newDir;
            outLine[j].normalize();
        }
    }
}

void smoothMesh(const Mesh& in, Mesh& out, const double dist)
{
    const double doubleDist = 2 * dist;
    out = in;

    for (int i = 0; i < in.normalMesh.size(); i++) {
        auto& inVec = in.normalMesh[i];
        auto& outVec = out.normalMesh[i];
        auto& currentNormal = out.indToNormal[i];

        Point newDir;
        for (int j = 0; j < inVec.size(); j++) {
            double currentDist = Point::dist(currentNormal.x1, inVec[j].x1);
            if (currentDist > dist)
                break;

            newDir += (currentDist / dist) * inVec[j].getDir(); 
        }

        newDir += 0.5 * currentNormal.getDir();
        out.indToNormal[i].x2 = out.indToNormal[i].x1 + newDir;
        out.indToNormal[i].normalize();
    }
}

vector<Polyline> createSphere()
{
    vector<Polyline> ret;

    const double radiusStep = 2;
    double currentRadius = maxRadius;
    while (currentRadius > radiusStep / 2) { 
        const double step = 1;
        const double sqrtRad = sqrt(currentRadius);
        
        double x = sqrtRad;
        Polyline newPolyline;
        
        while (x > 0) {

            // x^2 + y^2 = currentRadius
            x -= step;
            double y = sqrt(currentRadius - pow(x, 2));

            // x^2 + y^2 + z^2 = maxRadius 
            double z = sqrt(maxRadius - pow(x, 2) - pow(y, 2));

            double dx = x - center.x + errors[rand() % errors.size()];
            double dy = y - center.y + errors[rand() % errors.size()];
            double dz = z - center.z + errors[rand() % errors.size()];

            double len = 0.3 * sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));

            dx /= len;
            dy /= len;
            dz /= len;

            Point x1(x, y, z);
            Point x2(x + dx, y + dy, z + dz);
            
            Normal n(x1, x2);
            newPolyline.push_back(n);
        }

        ret.push_back(newPolyline);

        currentRadius -= radiusStep; 
    }

    return ret;
}

int main(int argc, char** argv)
{
    polySphere = createSphere();
    mesh.createFromPolylines(maxDist, polySphere);    

    smoothMesh(mesh, newMesh, smoothDist);
    smoothPolyMesh(polySphere, smoothPolySphere, smoothDist);
    
    if (argc == 1)
        return 0;

    ofstream fout(argv[1]);
    for (auto& line : polySphere)
        for (auto& n : line) 
            fout << n.x1 << '\n' << n.x2 << '\n';

    fout.close();

    fout.open(argv[2]);
    for (auto& line : smoothPolySphere)
        for (auto& n : line) 
            fout << n.x1 << '\n' << n.x2 << '\n';
    fout.close();
}

#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include "Point3D.h"
#include "Reader.h"
#include "Triangle.h"
#include "Triangulation.h"

using namespace std;

Reader::Reader()
{
}
Reader ::~Reader()
{
}

void Reader::readFile(Triangulation& triangualtion)
{
    std::ifstream readFromFile("E:\\Abhishek\\03-Cpp\\03-AssignmentThree\\01-AssignmentSTLReader\\cube.stl");

    map<Point3D, int> mapppedPoint3D;
    map<Point3D, int> mappedNormals;
    string line;
    vector<Triangle> tri;

    if (readFromFile.is_open())
    {

        int numberOfVertex = 1;
        int normalIndex = 1;
        int v1;
        int v2;
        int v3;
        int Normal;
        while (getline(readFromFile, line))
        {
            if (line.find("facet normal") != std::string::npos)
            {
                double x;
                double y;
                double z;
                istringstream facetNormal(line);
                string token1;
                string token2;
                facetNormal >> token1 >> token2 >> x >> y >> z;
                // Create a Point3D object
                Point3D point(x, y, z);

                // Check if the point is already mapped
                auto iterator = mappedNormals.find(point);

                // If not mapped, add to uniquePoints and update the mapping
                if (iterator == mappedNormals.end())
                {
                    mappedNormals[point] = triangualtion.uniqueNormal().size();
                    triangualtion.uniqueNormal().push_back(point);
                }

                normalIndex = mappedNormals[point];
            }

            if (line.find("vertex") != string::npos)
            {
                istringstream vertexStream(line);
                string token;
                double x, y, z;

                vertexStream >> token >> x >> y >> z;
                // Stored Coordinates x,y,z into object of Point3D
                Point3D point(x, y, z);


                auto it = mapppedPoint3D.find(point);

                if (it == mapppedPoint3D.end())
                {
                    triangualtion.uniquePoints().push_back(point);

                    mapppedPoint3D[point] = triangualtion.uniquePoints().size();
                }
                if (numberOfVertex == 1)
                {
                    v1 = mapppedPoint3D[point];
                    numberOfVertex++;
                }
                else if (numberOfVertex == 2)
                {
                    v2 = mapppedPoint3D[point];
                    numberOfVertex++;
                }
                else if (numberOfVertex == 3)
                {

                    v3 = mapppedPoint3D[point];
                    numberOfVertex++;
                }
            }
            if (numberOfVertex == 4)
            {

                Triangle T(v1 - 1, v2 - 1, v3 - 1, normalIndex - 1);
                triangualtion.triangles().push_back(T);
                numberOfVertex = 1;
            }
        }


        // copied all data of tri into triangles

        // copied all data of different vector into uniquePoints
        cout << "file close successfully" << endl;
        readFromFile.close();
    }
}
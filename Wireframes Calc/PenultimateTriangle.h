//
//  PenultimateTriangle.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/4/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__PenultimateTriangle__
#define __Wireframes_Calc_4__PenultimateTriangle__

#include <vector>
#include "FaceGenerator.h"

class Vertex;
class Point;
class Triangle;
class PenultimateTriangle:public FaceGenerator
{ //use with equilateral triangles only
private:
    bool verifyFaceIsTriangle();
    
    virtual PenultimateTriangle* doClone();
    virtual std::vector<Triangle> generateTriangles(double frameWidth);
    virtual std::vector<std::pair<Triangle, int>> do_generateTriangleEdgePairs(double frameWidth);
    virtual double do_calculateMaxWidth() const;
    
    std::vector<Point> inners;
    void generateInnerPoints(double frameWidth);
    std::vector<Triangle> connectInnerPoints();
public:
    PenultimateTriangle(const EdgeVector& e,const FaceVertices& pr);
};

#endif /* defined(__Wireframes_Calc_4__PenultimateTriangle__) */

//
//  Face.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/21/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Face__
#define __Wireframes_Calc_4__Face__

#include <vector>
#include <map>
#include "FaceVertices.h"

class Point;
class Vertex;
class Triangle;

typedef std::vector<int> EdgeVector;

class FaceGenerator
{
private:
    FaceVertices vertices;
    
    virtual FaceGenerator* doClone()=0;
    virtual std::vector<Triangle> generateTriangles(double frameWidth)=0;
    virtual std::vector<std::pair<Triangle, int>> do_generateTriangleEdgePairs(double frameWidth)=0;
    virtual double do_calculateMaxWidth() const=0;
protected:
    std::map<std::string,double> attributes;
    EdgeVector edges;
    
    Point getVertex(int index) const;
    
    FaceGenerator(const EdgeVector& e,const FaceVertices& pr);
public:
    FaceGenerator* clone(const FaceVertices& fv);

    void setAttribute(std::string name,double value);
    double getAttribute(std::string name);
    
    std::vector<Triangle> generateTrianglesList(double frameWidth);
    std::vector<std::pair<Triangle, int>> generateTriangleEdgePairs(double frameWidth);
    double calculateMaxWidth() const;
    virtual ~FaceGenerator();
};

#endif /* defined(__Wireframes_Calc_4__Face__) */

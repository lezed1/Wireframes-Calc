//
//  Face.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/21/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include <vector>

#include "FaceGenerator.h"
#include "Vertex.h"
#include "Utilities.h"
#include "FaceVertices.h"

FaceGenerator::~FaceGenerator()
{
    
}
FaceGenerator::FaceGenerator(const EdgeVector& e,const FaceVertices& pr):vertices(pr),edges(e)
{

}

std::vector<Triangle> FaceGenerator::generateTrianglesList(double frameWidth)
{
    //updateVertexPointer(values);
    return generateTriangles(frameWidth);
}
std::vector<std::pair<Triangle, int>> FaceGenerator::generateTriangleEdgePairs(double frameWidth)
{
    return do_generateTriangleEdgePairs(frameWidth);
}
double FaceGenerator::calculateMaxWidth() const
{
    return do_calculateMaxWidth();
}

void FaceGenerator::setAttribute(std::string name,double value)
{
    attributes.at(name)=value;
}
double FaceGenerator::getAttribute(std::string name)
{
    return attributes.at(name);
}
Point FaceGenerator::getVertex(int index) const
{
    return vertices.getVertexValue(index);
}

FaceGenerator* FaceGenerator::clone(const FaceVertices& fv)
{
    FaceGenerator* newFace=doClone();
    newFace->vertices=fv;
    return newFace;
}
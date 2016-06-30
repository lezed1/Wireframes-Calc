//
//  FrameEdge.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/3/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "FrameEdge.h"
#include "PovFileGenerator.h"
#include "TTIntersection.h"

FrameEdge::FrameEdge(const Line& l):edge(l)
{

}
void FrameEdge::addTriangle(const Triangle& t)
{
    triangles.push_back(t);
}
std::string FrameEdge::povRayString(const std::string& color) const
{
    return povRayTriangleList(triangles, color);
}
int FrameEdge::getNumOfTriangles() const
{
    return (int)triangles.size();
}
Triangle FrameEdge::getTriangle(int index) const
{
    return triangles.at(index);
}
Line FrameEdge::getLine() const
{
    return edge;
}

bool FrameEdge::doFrameEdgesIntersect(const FrameEdge& fe1,const FrameEdge& fe2)
{
    int fe1size=fe1.getNumOfTriangles();
    int fe2size=fe2.getNumOfTriangles();
    for (int i=0;i<fe1size;i++)
    {
        for (int j=0;j<fe2size;j++)
        {
            if (doTrianglesIntersect(fe1.getTriangle(i), fe2.getTriangle(j)))
            {
                return true;
            }
        }
    }
    return false;
}
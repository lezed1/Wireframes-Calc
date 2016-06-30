//
//  Frame.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/3/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "Frame.h"
#include "FrameEdge.h"

Frame::Frame(int en,double fw):edgeNum(en),frameWidth(fw)
{
    edges.reserve(en);
}
void Frame::addFrameEdge(const Line& l)
{
    edges.push_back(FrameEdge(l));
}
void Frame::addTriangle(int index,const Triangle& t)
{
    edges.at(index).addTriangle(t);
}
double Frame::getFrameWidth() const
{
    return frameWidth;
}
void Frame::printPovRay(const std::string& color, std::ostream &ostream) const
{
    for (int i=0;i<edgeNum;i++)
    {
        //edges.at(i).printPovRay(color);
        std::string tList=edges.at(i).povRayString(color);
        if (tList.size()>0)
        {
            ostream << tList << "\n";
        }
    }
}
FrameEdge Frame::getFrameEdge(int index) const
{
    return edges.at(index);
}
const std::vector<FrameEdge>* Frame::getFrameEdges() const
{
    return &edges;
}
int Frame::getEdgeNum() const
{
    return edgeNum;
}
std::vector<std::pair<int,int>> Frame::getFrameEdgeIntersections(const Frame& f1,const Frame& f2)
{
    std::vector<std::pair<int,int>> intersections;
    int f1size=f1.getEdgeNum();
    int f2size=f2.getEdgeNum();
    for (int i=0;i<f1size;i++)
    {
        for (int j=0;j<f2size;j++)
        {
            if (FrameEdge::doFrameEdgesIntersect(f1.getFrameEdge(i), f2.getFrameEdge(j)))
            {
                intersections.push_back(std::pair<int,int>(i,j));
            }
        }
    }
    return intersections;
}
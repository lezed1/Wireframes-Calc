//
//  Frame.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/3/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Frame__
#define __Wireframes_Calc_4__Frame__

#include <vector>
#include "FrameEdge.h"

//class FrameEdge;
class Line;
class Triangle;
class Frame
{
private:
    std::vector<FrameEdge> edges;
    int edgeNum;
    double frameWidth;
public:
    Frame(int en,double fw);
    void addFrameEdge(const Line& l);
    void addTriangle(int index,const Triangle& t);
    void printPovRay(const std::string& color) const;
    double getFrameWidth() const;
    
    FrameEdge getFrameEdge(int index) const;
    const std::vector<FrameEdge>* getFrameEdges() const;
    
    int getEdgeNum() const;
    
    static std::vector<std::pair<int,int>> getFrameEdgeIntersections(const Frame& f1,const Frame& f2);
    static bool doFrameEdgesIntersect(const Frame& f1,const Frame& f2,const std::pair<int,int> edgepair);
};

#endif /* defined(__Wireframes_Calc_4__Frame__) */

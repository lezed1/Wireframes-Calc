//
//  FrameEdge.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/3/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__FrameEdge__
#define __Wireframes_Calc_4__FrameEdge__

#include <vector>
#include "basicshapes.h"

class FrameEdge
{
private:
    Line edge;
    std::vector<Triangle> triangles;
public:
    FrameEdge(const Line& l);
    void addTriangle(const Triangle& t);
    std::string povRayString(const std::string& color) const;
    int getNumOfTriangles() const;
    Triangle getTriangle(int index) const;
    Line getLine() const;
    
    static bool doFrameEdgesIntersect(const FrameEdge& fe1,const FrameEdge& fe2);
};

#endif /* defined(__Wireframes_Calc_4__FrameEdge__) */

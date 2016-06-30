//
//  FramedFace.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/23/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__FramedFace__
#define __Wireframes_Calc_4__FramedFace__

#include "FaceGenerator.h"
#include "basicshapes.h"

class FramedFace:public FaceGenerator
{
private:
    virtual std::vector<Triangle> generateTriangles(double frameWidth);
    virtual FramedFace* doClone();
    virtual std::vector<std::pair<Triangle, int>> do_generateTriangleEdgePairs(double frameWidth);
protected:
    std::vector<Point> inners; //inner points on edges, index corresponds to the index of corresponding vertex
    
    void generateInnerPoints(double frameWidth);
    std::vector<Triangle> connectInnerPoints();
    std::vector<std::pair<Triangle, int>> makeTriangleEdgePairs(double frameWidth);
    virtual double do_calculateMaxWidth() const;
public:
    FramedFace(const EdgeVector& e,const FaceVertices& pr);
    virtual ~FramedFace();
};

#endif /* defined(__Wireframes_Calc_4__FramedFace__) */

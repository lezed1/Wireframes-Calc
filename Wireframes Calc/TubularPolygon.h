//
//  TubularPolygon.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/13/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__TubularPolygon__
#define __Wireframes_Calc_4_5__TubularPolygon__

#include "FramedFace.h"
#include "basicshapes.h"

class TubularPolygon:public FramedFace
{
private:
    Vector getFaceNormal(double magnitude) const;
    virtual std::vector<Triangle> generateTriangles(double frameWidth);
    virtual std::vector<std::pair<Triangle, int>> do_generateTriangleEdgePairs(double frameWidth);
    virtual TubularPolygon* doClone();
    virtual double do_calculateMaxWidth() const;
public:
    TubularPolygon(const EdgeVector& e,const FaceVertices& pr);
    
};

#endif /* defined(__Wireframes_Calc_4_5__TubularPolygon__) */

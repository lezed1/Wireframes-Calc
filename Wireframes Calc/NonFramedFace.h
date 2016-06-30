//
//  NonFramedFace.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/23/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__NonFramedFace__
#define __Wireframes_Calc_4__NonFramedFace__

#include "FaceGenerator.h"
#include "basicshapes.h"

class NonFramedFace:public FaceGenerator
{
private:
    virtual std::vector<Triangle> generateTriangles(double frameWidth);
    virtual NonFramedFace* doClone();
    virtual std::vector<std::pair<Triangle, int>> do_generateTriangleEdgePairs(double frameWidth);
    virtual double do_calculateMaxWidth() const;
public:
    NonFramedFace(const EdgeVector& e,const FaceVertices& pr);
};

#endif /* defined(__Wireframes_Calc_4__NonFramedFace__) */

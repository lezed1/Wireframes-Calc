//
//  NonFramedFace.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/23/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include "NonFramedFace.h"
#include "FaceVertices.h"

NonFramedFace::NonFramedFace(const EdgeVector& e,const FaceVertices& pr):FaceGenerator(e,pr)
{
    
}
std::vector<Triangle> NonFramedFace::generateTriangles(double frameWidth)
{
    return std::vector<Triangle>(0);
}
NonFramedFace* NonFramedFace::doClone()
{
    return new NonFramedFace(*this);
}
std::vector<std::pair<Triangle, int>> NonFramedFace::do_generateTriangleEdgePairs(double frameWidth)
{
    return std::vector<std::pair<Triangle, int>>(0);
}
double NonFramedFace::do_calculateMaxWidth() const
{
    return 1000000.0;
}
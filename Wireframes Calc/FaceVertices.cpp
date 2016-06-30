//
//  FaceVertices.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/24/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "FaceVertices.h"
#include "Polyhedron.h"

FaceVertices::FaceVertices(const Polyhedron* p,const std::vector<int>& fv):poly(p),faceVertices(fv)
{
    
}
Point FaceVertices::getVertexValue(int index) const
{
    int polyhedronIndex=faceVertices.at(index);
    return poly->getVertex(polyhedronIndex);
}
int FaceVertices::verticesNum() const
{
    return (int)faceVertices.size();
}
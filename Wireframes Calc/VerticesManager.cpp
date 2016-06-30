//
//  VerticesManager.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 4/26/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "VerticesManager.h"

VerticesManager::VerticesManager(int vertexNum)
{
    vertices.resize(vertexNum);
}
void VerticesManager::setVertex(int index, double x,double y,double z)
{
    vertices.at(index).setAll(x, y, z);
}
Point& VerticesManager::getVertexRef(int index)
{
    return vertices.at(index);
}
Point VerticesManager::getVertex(int index) const
{
    return vertices.at(index);
}
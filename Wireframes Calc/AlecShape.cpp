//
//  AlecShape.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/19/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include "AlecShape.h"
#include "TubularPolygon.h"

void AlecShape::setVertexValues()
{
    setVertex(0, -.88,.59,-1.09);    //top lower right
    setVertex(1, -.78,.95,-.9);     //top lower left
    setVertex(2, -1.11,.71,-.75);    //top top
    setVertex(3, .78,-1.06,-.76);    //lower right lower left
    setVertex(4, .78,.83,1.01);    //lower right lower right //z
    setVertex(5, 1.12,-.92,-.77);    //lower right top
    setVertex(6, 1,.94,.65);    //lower left lower left
    setVertex(7, -.79,-.69,1.11);    //lower left lower right //z
    setVertex(8, .64,1.15,.76);    //lower left top
    setVertex(9, -1,-.85,.76);     //back lower left
    setVertex(10, -.64,-1.04,.9);    //back lower right
    setVertex(11, .88,-.72,-1.01);    //back top
}
void AlecShape::initStructure()
{
    structure.addEdge(0, 6);
    structure.addEdge(8, 11);
    structure.addEdge(1, 5);
    structure.addEdge(1, 7);
    structure.addEdge(9, 8);
    structure.addEdge(1, 8);
    structure.addEdge(6, 5);
    structure.addEdge(0, 11);
    structure.addEdge(2, 4);
    structure.addEdge(2, 9);
    structure.addEdge(7, 4);
    structure.addEdge(10, 6);
    structure.addEdge(4, 3);
    structure.addEdge(7, 5);
    structure.addEdge(9, 11);
    structure.addEdge(10, 0);
    structure.addEdge(3, 2);
    structure.addEdge(3, 10);
}
void AlecShape::setFaceAttributes()
{
    
}

void AlecShape::initAtts()
{
    
}

AlecShape::AlecShape():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
AlecShape::AlecShape(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
AlecShape* AlecShape::doClone() const
{
    return new AlecShape(*this);
}
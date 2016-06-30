//
//  Tetrahedron.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/4/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "Tetrahedron.h"
#include "FramedFace.h"
#include "PenultimateTriangle.h"

void Tetrahedron::setVertexValues()
{
    setVertex(0, 1,1,1);
    setVertex(1, -1,-1,1);
    setVertex(2, -1,1,-1);
    setVertex(3, 1,-1,-1);
}
void Tetrahedron::initStructure()
{
    structure.addEdge(0, 1);
    structure.addEdge(0, 2);
    structure.addEdge(0, 3);
    structure.addEdge(1, 2);
    structure.addEdge(1, 3);
    structure.addEdge(2, 3);
    
    addFace<FramedFace>({0,1,2});
    addFace<FramedFace>({0,1,3});
    addFace<FramedFace>({0,2,3});
    addFace<FramedFace>({1,2,3});
    
    /*addFace<PenultimateTriangle>({0,1,2});
    addFace<PenultimateTriangle>({0,1,3});
    addFace<PenultimateTriangle>({0,2,3});
    addFace<PenultimateTriangle>({1,2,3});
    
    setFaceAttribute(0, "ttt", 1.0);
    setFaceAttribute(1, "ttt", -1.0);
    setFaceAttribute(2, "ttt", 1.0);
    setFaceAttribute(3, "ttt", -1.0);
    
    setFaceAttribute(0, "nnn", -1.0);
    setFaceAttribute(1, "nnn", -1.0);
    setFaceAttribute(2, "nnn", -1.0);
    setFaceAttribute(3, "nnn", -1.0);*/
}
void Tetrahedron::setFaceAttributes()
{
    
}

void Tetrahedron::initAtts()
{
    
}

Tetrahedron::Tetrahedron():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Tetrahedron::Tetrahedron(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Tetrahedron* Tetrahedron::doClone() const
{
    return new Tetrahedron(*this);
}

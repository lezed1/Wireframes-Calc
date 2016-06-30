//
//  Octahedron.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/11/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include "Octahedron.h"
#include "FIT.h"
#include "FramedFace.h"

void Octahedron::setVertexValues()
{
    setVertex(0, 1,0,0);
    setVertex(1, -1,0,0);
    setVertex(2, 0,1,0);
    setVertex(3, 0,-1,0);
    setVertex(4, 0,0,1);
    setVertex(5, 0,0,-1);
}
void Octahedron::initStructure()
{
    structure.addEdge(0, 2);
    structure.addEdge(0, 3);
    structure.addEdge(0, 4);
    structure.addEdge(0, 5);
    
    structure.addEdge(1, 2);
    structure.addEdge(1, 3);
    structure.addEdge(1, 4);
    structure.addEdge(1, 5);
    
    structure.addEdge(2, 4);
    structure.addEdge(4, 3);
    structure.addEdge(3, 5);
    structure.addEdge(5, 2);
    
    addFace<FramedFace>({0,2,4});
    addFace<FramedFace>({0,4,3});
    addFace<FramedFace>({0,3,5});
    addFace<FramedFace>({0,5,2});
    
    addFace<FramedFace>({1,2,4});
    addFace<FramedFace>({1,4,3});
    addFace<FramedFace>({1,3,5});
    addFace<FramedFace>({1,5,2});
}
void Octahedron::setFaceAttributes()
{
    
}

void Octahedron::initAtts()
{
    
}

Octahedron::Octahedron():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Octahedron::Octahedron(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Octahedron* Octahedron::doClone() const
{
    return new Octahedron(*this);
}
//
//  Icosahedron.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/10/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>

#include "Icosahedron.h"
#include "FIT.h"
#include "FramedFace.h"

void Icosahedron::setVertexValues()
{
    double phi =(1+sqrt(5))/2;
    setVertex(0, 0,phi,1);
    setVertex(1, 0,phi,-1);
    setVertex(2, 0,-phi,-1);
    setVertex(3, 0,-phi,1);
    
    setVertex(4, 1,0,phi);
    setVertex(5, -1,0,phi);
    setVertex(6, -1,0,-phi);
    setVertex(7, 1,0,-phi);
    
    setVertex(8, phi,1,0);
    setVertex(9, phi,-1,0);
    setVertex(10, -phi,-1,0);
    setVertex(11, -phi,1,0);
}
void Icosahedron::initStructure()
{
    structure.addEdge(4, 5);
    structure.addEdge(6, 7);
    
    structure.addEdge(4, 8);
    structure.addEdge(4, 9);
    structure.addEdge(5, 10);
    structure.addEdge(5, 11);
    
    structure.addEdge(4, 0);
    structure.addEdge(5, 0);
    structure.addEdge(4, 3);
    structure.addEdge(5, 3);
    
    structure.addEdge(0, 8);
    structure.addEdge(0, 11);
    structure.addEdge(3, 9);
    structure.addEdge(3, 10);
    
    structure.addEdge(8, 9);
    structure.addEdge(10, 11);
    
    structure.addEdge(0, 1);
    structure.addEdge(2, 3);
    
    structure.addEdge(1, 8);
    structure.addEdge(1, 11);
    structure.addEdge(2, 9);
    structure.addEdge(2, 10);
    
    structure.addEdge(6, 1);
    structure.addEdge(7, 1);
    structure.addEdge(6, 2);
    structure.addEdge(7, 2);
    
    structure.addEdge(6, 10);
    structure.addEdge(6, 11);
    structure.addEdge(7, 8);
    structure.addEdge(7, 9);
    
    addFace<FramedFace>({4,8,9});
    addFace<FramedFace>({5,10,11});
    addFace<FramedFace>({4,5,0});
    addFace<FramedFace>({4,5,3});
    
    addFace<FramedFace>({0,8,4});
    addFace<FramedFace>({0,11,5});
    addFace<FramedFace>({3,9,4});
    addFace<FramedFace>({3,10,5});
    
    addFace<FramedFace>({0,1,8});
    addFace<FramedFace>({0,1,11});
    addFace<FramedFace>({2,3,9});
    addFace<FramedFace>({2,3,10});
    
    addFace<FramedFace>({6,7,1});
    addFace<FramedFace>({6,7,2});
    addFace<FramedFace>({6,10,11});
    addFace<FramedFace>({7,8,9});
    
    addFace<FramedFace>({1,8,7});
    addFace<FramedFace>({1,11,6});
    addFace<FramedFace>({2,9,7});
    addFace<FramedFace>({2,10,6});
}
void Icosahedron::setFaceAttributes()
{
    
}

void Icosahedron::initAtts()
{
    
}

Icosahedron::Icosahedron():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Icosahedron::Icosahedron(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Icosahedron* Icosahedron::doClone() const
{
    return new Icosahedron(*this);
}
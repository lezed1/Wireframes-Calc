//
//  Bilunabirotunda.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/25/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>

#include "Bilunabirotunda.h"
#include "FramedFace.h"

void Bilunabirotunda::setVertexValues()
{
    double phi=(1.0+sqrt(5))/2.0;
    double phi2=phi/2.0;
    double phiPlus=(phi+1)/2.0;
    
    setVertex(0, 0,0,phi2);
    setVertex(1, 0,0,-phi2);
    
    setVertex(2, phiPlus,0.5,0);
    setVertex(3, phiPlus,-0.5,0);
    setVertex(4, -phiPlus,0.5,0);
    setVertex(5, -phiPlus,-0.5,0);
    
    setVertex(6, 0.5,phi2,0.5);
    setVertex(7, 0.5,phi2,-0.5);
    setVertex(8, 0.5,-phi2,0.5);
    setVertex(9, 0.5,-phi2,-0.5);
    setVertex(10, -0.5,phi2,0.5);
    setVertex(11, -0.5,phi2,-0.5);
    setVertex(12, -0.5,-phi2,0.5);
    setVertex(13, -0.5,-phi2,-0.5);
}
void Bilunabirotunda::initStructure()
{
    structure.addEdge(0, 6);
    structure.addEdge(0, 8);
    structure.addEdge(0, 10);
    structure.addEdge(0, 12);
    
    structure.addEdge(1, 7);
    structure.addEdge(1, 9);
    structure.addEdge(1, 11);
    structure.addEdge(1, 13);
    
    structure.addEdge(2, 3);
    structure.addEdge(4, 5);
    
    structure.addEdge(6, 10);
    structure.addEdge(7, 11);
    structure.addEdge(8, 12);
    structure.addEdge(9, 13);
    
    structure.addEdge(6, 7);
    structure.addEdge(8, 9);
    structure.addEdge(10, 11);
    structure.addEdge(12, 13);
    
    structure.addEdge(2, 6);
    structure.addEdge(2, 7);
    structure.addEdge(3, 8);
    structure.addEdge(3, 9);
    
    structure.addEdge(4, 10);
    structure.addEdge(4, 11);
    structure.addEdge(5, 12);
    structure.addEdge(5, 13);
    
    addFace<FramedFace>({0,6,10});
    addFace<FramedFace>({0,8,12});
    addFace<FramedFace>({1,7,11});
    addFace<FramedFace>({1,9,13});
    
    addFace<FramedFace>({6,7,11,10});
    addFace<FramedFace>({8,9,13,12});
    
    addFace<FramedFace>({6,7,2});
    addFace<FramedFace>({10,11,4});
    addFace<FramedFace>({8,9,3});
    addFace<FramedFace>({12,13,5});
    
    addFace<FramedFace>({2,3,8,0,6});
    addFace<FramedFace>({4,5,12,0,10});
    
    addFace<FramedFace>({2,3,9,1,7});
    addFace<FramedFace>({4,5,13,1,11});
}
void Bilunabirotunda::setFaceAttributes()
{
    
}

void Bilunabirotunda::initAtts()
{
    
}

Bilunabirotunda::Bilunabirotunda():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Bilunabirotunda::Bilunabirotunda(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Bilunabirotunda* Bilunabirotunda::doClone() const
{
    return new Bilunabirotunda(*this);
}
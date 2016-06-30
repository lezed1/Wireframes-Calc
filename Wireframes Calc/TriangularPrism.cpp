//
//  TriangularPrism.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/29/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>
#include "TriangularPrism.h"
#include "FramedFace.h"
#include "NonFramedFace.h"

void TriangularPrism::setVertexValues()
{
    double height=getAttribute("height").getCurrentValue();
    
    getVertexRef(0).setAll(height,sqrt(3),1);
    getVertexRef(1).setAll(height,-sqrt(3),1);
    getVertexRef(2).setAll(height,0,-2);
    
    getVertexRef(3).setAll(-height,sqrt(3),1);
    getVertexRef(4).setAll(-height,-sqrt(3),1);
    getVertexRef(5).setAll(-height,0,-2);
}
void TriangularPrism::initStructure()
{
    structure.addEdge(0, 1);
    structure.addEdge(1, 2);
    structure.addEdge(2, 0);
    
    structure.addEdge(3, 4);
    structure.addEdge(4, 5);
    structure.addEdge(5, 3);
    
    structure.addEdge(0, 3);
    structure.addEdge(1, 4);
    structure.addEdge(2, 5);
    
    addFace<FramedFace>({0,1,2});
    addFace<FramedFace>({3,4,5});
    addFace<FramedFace>({0,1,4,3});
    addFace<FramedFace>({1,2,5,4});
    addFace<FramedFace>({2,0,3,5});
}
void TriangularPrism::setFaceAttributes()
{
    
}

void TriangularPrism::initAtts()
{
    addAttribute("height", Attribute(1.0, 0.0, 2.0, 0.01));
}

TriangularPrism::TriangularPrism():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
TriangularPrism::TriangularPrism(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
TriangularPrism* TriangularPrism::doClone() const
{
    return new TriangularPrism(*this);
}
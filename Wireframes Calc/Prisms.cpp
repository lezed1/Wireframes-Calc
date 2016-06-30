//
//  Prisms.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/26/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include "Prisms.h"
#include "FramedFace.h"
#include "NonFramedFace.h"
#include "DihedralFace.h"

void RectPrism::setVertexValues()
{
    double height=getAttribute("height").getCurrentValue();
    
    setVertex(0, height,1,1);
    setVertex(1, height,1,-1);
    setVertex(2, height,-1,-1);
    setVertex(3, height,-1,1);
    setVertex(4, -height,1,1);
    setVertex(5, -height,1,-1);
    setVertex(6, -height,-1,-1);
    setVertex(7, -height,-1,1);
}
void RectPrism::initStructure()
{
    structure.addEdge(0, 1);
    structure.addEdge(1, 2);
    structure.addEdge(2, 3);
    structure.addEdge(3, 0);
    
    structure.addEdge(4, 5);
    structure.addEdge(5, 6);
    structure.addEdge(6, 7);
    structure.addEdge(7, 4);
    
    structure.addEdge(0, 4);
    structure.addEdge(1, 5);
    structure.addEdge(2, 6);
    structure.addEdge(3, 7);
    
    addFace<FramedFace>({0,1,2,3});
    addFace<FramedFace>({4,5,6,7});
    addFace<FramedFace>({0,1,5,4});
    addFace<FramedFace>({1,2,6,5});
    addFace<FramedFace>({2,3,7,6});
    addFace<DihedralFace>({3,0,4,7});
    
    setFaceAttribute(5, "uorl", -1.0);
}
void RectPrism::setFaceAttributes()
{
    double dihedral=getAttribute("dihedral").getCurrentValue();
    setFaceAttribute(5, "dihedral", dihedral);
}

void RectPrism::initAtts()
{
    addAttribute("height", Attribute(1.0, 0.0, 2.0, 0.01));
    addAttribute("dihedral", Attribute(45.0, -180.0, 180.0, 1.0));
}

RectPrism::RectPrism():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
RectPrism::RectPrism(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
RectPrism* RectPrism::doClone() const
{
    return new RectPrism(*this);
}
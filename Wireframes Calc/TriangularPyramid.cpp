//
//  TriangularPyramid.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/10/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>

#include "TriangularPyramid.h"
#include "FramedFace.h"
#include "DihedralFace.h"
#include "PenultimateTriangle.h"

void TriangularPyramid::setVertexValues()
{
    double height=getAttribute("height").getCurrentValue();
    
    setVertex(0, 0,sqrt(3),1);
    setVertex(1, 0,-sqrt(3),1);
    setVertex(2, 0,0,-2);
    setVertex(3, height,0,0);
}
void TriangularPyramid::initStructure()
{
    structure.addEdge(0, 1);
    structure.addEdge(1, 2);
    structure.addEdge(2, 0);
    structure.addEdge(0, 3);
    structure.addEdge(1, 3);
    structure.addEdge(2, 3);
    
    addFace<FramedFace>({0,1,2});
    addFace<FramedFace>({0,1,3});
    addFace<FramedFace>({0,2,3});
    addFace<FramedFace>({1,2,3});
    
    /*addFace<DihedralFace>({0,1,2});
    setFaceAttribute(0, "uorl", -1.0);
    setFaceAttribute(0, "dihedral", 20);
    addFace<DihedralFace>({0,1,2});
    setFaceAttribute(1, "uorl", 1.0);
    setFaceAttribute(1, "dihedral", 20);*/
}
void TriangularPyramid::setFaceAttributes()
{
    
}

void TriangularPyramid::initAtts()
{
    addAttribute("height", Attribute(sqrt(8), 0.0, 2.0, 0.01));
}

TriangularPyramid::TriangularPyramid():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
TriangularPyramid::TriangularPyramid(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
TriangularPyramid* TriangularPyramid::doClone() const
{
    return new TriangularPyramid(*this);
}
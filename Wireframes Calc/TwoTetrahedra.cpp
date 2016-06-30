//
//  TwoTetrahedra.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/9/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "TwoTetrahedra.h"
#include "FramedFace.h"
#include "PenultimateTriangle.h"

void TwoTetrahedra::setVertexValues()
{
    double height=getAttribute("height").getCurrentValue();
    double w=getAttribute("w").getCurrentValue();
    double twist=getAttribute("twist").getCurrentValue();
    
    Point axis(0, 1, 0);
    Point axis2(0,0,0);
    
    setVertex(0, height,w,1);
    setVertex(1, height,-w,-1);
    setVertex(2, -height,-w,1);
    setVertex(3, -height,w,-1);
    
    setVertex(4, height,w,1);
    setVertex(5, height,-w,-1);
    setVertex(6, -height,-w,1);
    setVertex(7, -height,w,-1);
    
    getVertexRef(0).twistPoint(axis, axis2, twist);
    getVertexRef(1).twistPoint(axis, axis2, twist);
    getVertexRef(2).twistPoint(axis, axis2, twist);
    getVertexRef(3).twistPoint(axis, axis2, twist);
    
    getVertexRef(4).twistPoint(axis, axis2, -twist);
    getVertexRef(5).twistPoint(axis, axis2, -twist);
    getVertexRef(6).twistPoint(axis, axis2, -twist);
    getVertexRef(7).twistPoint(axis, axis2, -twist);
}
void TwoTetrahedra::initStructure()
{
    structure.addEdge(0, 1);
    structure.addEdge(0, 2);
    structure.addEdge(0, 3);
    structure.addEdge(1, 2);
    structure.addEdge(1, 3);
    structure.addEdge(2, 3);

    structure.addEdge(4, 5);
    structure.addEdge(4, 6);
    structure.addEdge(4, 7);
    structure.addEdge(5, 6);
    structure.addEdge(5, 7);
    structure.addEdge(6, 7);
    
    addFace<FramedFace>({0,1,2});
    addFace<FramedFace>({0,1,3});
    addFace<FramedFace>({0,2,3});
    addFace<FramedFace>({1,2,3});
    
    addFace<FramedFace>({4,5,6});
    addFace<FramedFace>({4,5,7});
    addFace<FramedFace>({4,6,7});
    addFace<FramedFace>({5,6,7});
}
void TwoTetrahedra::setFaceAttributes()
{
    
}

void TwoTetrahedra::initAtts()
{
    addAttribute("height",Attribute(0.6,0.2,1.4,0.01)); //current,lower,upper,increment
    addAttribute("w",Attribute(0.5,0.2,1.4,0.01));
    addAttribute("twist",Attribute(20,-60,60,1));
}

TwoTetrahedra::TwoTetrahedra():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
TwoTetrahedra::TwoTetrahedra(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
TwoTetrahedra* TwoTetrahedra::doClone() const
{
    return new TwoTetrahedra(*this);
}

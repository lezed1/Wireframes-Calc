//
//  TwoTrapezoids.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/27/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "TwoTrapezoids.h"
#include "DihedralFace.h"

void TwoTrapezoids::setVertexValues()
{
    double triangleDistance=getAttribute("triangleDistance").getCurrentValue();
    double triangleHeight=getAttribute("triangleHeight").getCurrentValue();
    double twist=getAttribute("twist").getCurrentValue();
    double trapezoid=getAttribute("trapezoid").getCurrentValue();
    
    
}
void TwoTrapezoids::initStructure()
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
void TwoTrapezoids::setFaceAttributes()
{
    
}

void TwoTrapezoids::initAtts()
{
    addAttribute("triangleDistance",Attribute(0.2575,0.2,0.3,0.01)); //current,lower,upper,increment
    addAttribute("triangleHeight",Attribute(1.732,1.5,2.0,0.05));
    addAttribute("twist",Attribute(54.5,40,65,2));
    addAttribute("trapezoid",Attribute(0.5,0.3,0.7,0.05));
    addAttribute("dihedral",Attribute(42,30,55,2));
}

TwoTrapezoids::TwoTrapezoids():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
TwoTrapezoids::TwoTrapezoids(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
TwoTrapezoids* TwoTrapezoids::doClone() const
{
    return new TwoTrapezoids(*this);
}
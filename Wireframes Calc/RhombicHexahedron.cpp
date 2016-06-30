//
//  RhombicHexahedron.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/26/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "RhombicHexahedron.h"
#include <cmath>

#include "Bilunabirotunda.h"
#include "FramedFace.h"

void RhombicHexahedron::setVertexValues()
{
    double x=getAttribute("crimp").getCurrentValue();
    
    Point center(0,0,0);
    
    Point tp1(1,1,1);
    Point tp2(1,1,-1);
    Point tp3(1,-1,-1);
    Point tp4(1,-1,1);
    
    Point tp5(-1,1,1);
    Point tp6(-1,1,-1);
    Point tp7(-1,-1,-1);
    Point tp8(-1,-1,1);
    
    double d1=Point::distance(center, tp1);
    double f1=1-x/d1;
    
    getVertexRef(0)=Point::extendLine(tp1,center,f1);
    getVertexRef(2)=Point::extendLine(tp3,center,f1);
    getVertexRef(5)=Point::extendLine(tp6,center,f1);
    getVertexRef(7)=Point::extendLine(tp8,center,f1);
    
    double d2=Point::distance(center, tp2);
    double f2=1-(1-x)/d2;
    
    getVertexRef(1)=Point::extendLine(tp2,center,f2);
    getVertexRef(3)=Point::extendLine(tp4,center,f2);
    getVertexRef(4)=Point::extendLine(tp5,center,f2);
    getVertexRef(6)=Point::extendLine(tp7,center,f2);
    
    double elength=1.0/Point::distance(getVertexRef(0), getVertexRef(1));
    getVertexRef(0)*=elength;
    getVertexRef(1)*=elength;
    getVertexRef(2)*=elength;
    getVertexRef(3)*=elength;
    getVertexRef(4)*=elength;
    getVertexRef(5)*=elength;
    getVertexRef(6)*=elength;
    getVertexRef(7)*=elength;
}
void RhombicHexahedron::initStructure()
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
}
void RhombicHexahedron::setFaceAttributes()
{
    
}

void RhombicHexahedron::initAtts()
{
    addAttribute("crimp",Attribute(0.3608,0.0,1.0,0.0001)); //current,lower,upper,increment
}

RhombicHexahedron::RhombicHexahedron():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
RhombicHexahedron::RhombicHexahedron(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
RhombicHexahedron* RhombicHexahedron::doClone() const
{
    return new RhombicHexahedron(*this);
}
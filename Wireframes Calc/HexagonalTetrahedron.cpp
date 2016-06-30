//
//  HexagonalTetrahedron.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/24/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "HexagonalTetrahedron.h"
#include <cmath>

#include "Bilunabirotunda.h"
#include "FramedFace.h"

void HexagonalTetrahedron::setVertexValues()
{
    double x=getAttribute("crimp").getCurrentValue();
    //double x=0.362434;
    
    Point center(0,0,0);
    
    Point tp1(1,1,1);
    Point tp2(1,-1,-1);
    Point tp3(-1,-1,1);
    Point tp4(-1,1,-1);
    
    double d1=Point::distance(center, tp1);
    double f1=1-x/d1;
    
    getVertexRef(0)=Point::extendLine(tp1,center,f1);
    getVertexRef(1)=Point::extendLine(tp2,center,f1);
    getVertexRef(2)=Point::extendLine(tp3,center,f1);
    getVertexRef(3)=Point::extendLine(tp4,center,f1);
    
    Point m1=(tp1+tp2)/2;
    Point m2=(tp1+tp3)/2;
    Point m3=(tp1+tp4)/2;
    Point m4=(tp2+tp3)/2;
    Point m5=(tp2+tp4)/2;
    Point m6=(tp3+tp4)/2;
    
    double d2=Point::distance(center, m1);
    double f2=1-(1-x)/d2;
    
    getVertexRef(4)=Point::extendLine(m1,center,f2);
    getVertexRef(5)=Point::extendLine(m2,center,f2);
    getVertexRef(6)=Point::extendLine(m3,center,f2);
    getVertexRef(7)=Point::extendLine(m4,center,f2);
    getVertexRef(8)=Point::extendLine(m5,center,f2);
    getVertexRef(9)=Point::extendLine(m6,center,f2);
    
    double elength=1.0/Point::distance(getVertexRef(0), getVertexRef(4));
    getVertexRef(0)*=elength;
    getVertexRef(1)*=elength;
    getVertexRef(2)*=elength;
    getVertexRef(3)*=elength;
    getVertexRef(4)*=elength;
    getVertexRef(5)*=elength;
    getVertexRef(6)*=elength;
    getVertexRef(7)*=elength;
    getVertexRef(8)*=elength;
    getVertexRef(9)*=elength;
}
void HexagonalTetrahedron::initStructure()
{
    structure.addEdge(0, 4);
    structure.addEdge(0, 5);
    structure.addEdge(0, 6);
    
    structure.addEdge(1, 4);
    structure.addEdge(1, 7);
    structure.addEdge(1, 8);
    
    structure.addEdge(2, 5);
    structure.addEdge(2, 7);
    structure.addEdge(2, 9);
    
    structure.addEdge(3, 6);
    structure.addEdge(3, 8);
    structure.addEdge(3, 9);
}
void HexagonalTetrahedron::setFaceAttributes()
{
    
}

void HexagonalTetrahedron::initAtts()
{
    addAttribute("crimp",Attribute(0.3608,0.0,1.0,0.0001)); //current,lower,upper,increment
}

HexagonalTetrahedron::HexagonalTetrahedron():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
HexagonalTetrahedron::HexagonalTetrahedron(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
HexagonalTetrahedron* HexagonalTetrahedron::doClone() const
{
    return new HexagonalTetrahedron(*this);
}
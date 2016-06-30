//
//  Hendecahedron.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 1/1/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include "Hendecahedron.h"
#include "FramedFace.h"

void Hendecahedron::setVertexValues()
{
    Point axis1(1,0,0);
    Point axis2(0,0,0);
    double poleHeight=getAttribute("poleHeight").getCurrentValue();
    double triangleHeight=getAttribute("triangleHeight").getCurrentValue();
    double twist=getAttribute("twist").getCurrentValue();
    
    Point tp1(poleHeight,0,0);
    Point tp2(-poleHeight,0,0);
    
    Point tp3(triangleHeight,1.732,1);
    Point tp4(triangleHeight,-1.732,1);
    Point tp5(triangleHeight,0,-2);
    
    Point tp6(-triangleHeight,1.732,1);
    Point tp7(-triangleHeight,-1.732,1);
    Point tp8(-triangleHeight,0,-2);
    
    tp3.twistPoint(axis2, axis1, twist);
    tp4.twistPoint(axis2, axis1, twist);
    tp5.twistPoint(axis2, axis1, twist);
    tp6.twistPoint(axis2, axis1, -twist);
    tp7.twistPoint(axis2, axis1, -twist);
    tp8.twistPoint(axis2, axis1, -twist);
    
    Vector e9=Vector(0,-1.732,-1);
    Vector e10=Vector(0,1.732,-1);
    Vector e11=Vector(0,0,2);
    Point tp9=planarize(tp1, tp4, tp5, e9, axis2);
    Point tp10=planarize(tp1, tp5, tp3, e10, axis2);
    Point tp11=planarize(tp1, tp3, tp4, e11, axis2);
    
    getVertexRef(0)=Point::dualize(tp1,tp3,tp11);
    getVertexRef(1)=Point::dualize(tp1,tp4,tp9);
    getVertexRef(2)=Point::dualize(tp1,tp5,tp10);
    
    getVertexRef(3)=Point::dualize(tp2,tp6,tp11);
    getVertexRef(4)=Point::dualize(tp2,tp7,tp9);
    getVertexRef(5)=Point::dualize(tp2,tp8,tp10);
    
    getVertexRef(6)=Point::dualize(tp3,tp6,tp10);
    getVertexRef(7)=Point::dualize(tp3,tp6,tp11);
    
    getVertexRef(8)=Point::dualize(tp4,tp7,tp11);
    getVertexRef(9)=Point::dualize(tp4,tp7,tp9);
    
    getVertexRef(10)=Point::dualize(tp5,tp8,tp9);
    getVertexRef(11)=Point::dualize(tp5,tp8,tp10);
}
void Hendecahedron::initStructure()
{
    structure.addEdge(0, 1);
    structure.addEdge(1, 2);
    structure.addEdge(2, 0);
    
    structure.addEdge(3, 4);
    structure.addEdge(4, 5);
    structure.addEdge(5, 3);
    
    structure.addEdge(6, 7);
    structure.addEdge(8, 9);
    structure.addEdge(10, 11);
    
    structure.addEdge(1, 9);
    structure.addEdge(1, 10);
    structure.addEdge(4, 9);
    structure.addEdge(4, 10);
    
    structure.addEdge(0, 8);
    structure.addEdge(0, 7);
    structure.addEdge(3, 8);
    structure.addEdge(3, 7);
    
    structure.addEdge(2, 6);
    structure.addEdge(2, 11);
    structure.addEdge(5, 6);
    structure.addEdge(5, 11);
    
    addFace<FramedFace>({0,1,2});
    addFace<FramedFace>({3,4,5});
    
    addFace<FramedFace>({6,7,0,2});
    addFace<FramedFace>({8,9,1,0});
    addFace<FramedFace>({10,11,2,1});
    
    addFace<FramedFace>({6,7,3,5});
    addFace<FramedFace>({8,9,4,3});
    addFace<FramedFace>({10,11,5,4});
    
    addFace<FramedFace>({0,8,3,7});
    addFace<FramedFace>({1,9,4,10});
    addFace<FramedFace>({2,6,5,11});
}
void Hendecahedron::setFaceAttributes()
{
    
}

void Hendecahedron::initAtts()
{
    addAttribute("poleHeight",Attribute(2.828,1.0,4.0,0.01)); //current,lower,upper,increment
    addAttribute("triangleHeight",Attribute(1.414,0.5,3.0,0.01));
    addAttribute("twist",Attribute(0,0,20,1));
}

Hendecahedron::Hendecahedron():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Hendecahedron::Hendecahedron(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Hendecahedron* Hendecahedron::doClone() const
{
    return new Hendecahedron(*this);
}

Point Hendecahedron::planarize(const Point& plane1,const Point& plane2,const Point& plane3,const Vector& lineVector,const Point& lineStart) const
{
    Vector planeVector1(plane2,plane1);
    Vector planeVector2(plane2,plane3);
    Vector planeNormal=Vector::cross(planeVector1, planeVector2);
    
    double ddd=Vector::dot(Vector(lineStart,plane1),planeNormal)/Vector::dot(lineVector,planeNormal);
    return lineStart+lineVector*ddd;
}
//
//  Hexahedron.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/30/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include "Hexahedron.h"
#include "FramedFace.h"

void Hexahedron::setVertexValues()
{
    Point axis1(1,0,0);
    Point axis2(0,0,0);
    double height=getAttribute("height").getCurrentValue();
    double widthh=getAttribute("widthh").getCurrentValue();
    double twist=getAttribute("twist").getCurrentValue();
    
    Point tp1(height,0,widthh);
    Point tp2(height,0,-widthh);
    Point tp3(-height,0,widthh);
    Point tp4(-height,0,-widthh);
    
    tp4.twistPoint(axis2,axis1,-twist);
    tp3.twistPoint(axis2,axis1,-twist);
    tp2.twistPoint(axis2,axis1,twist);
    tp1.twistPoint(axis2,axis1,twist);
    Point tp5=Point(0,-1.414,0);
    Point tp6=Point(0,1.414,0);
    
    getVertexRef(0)=Point::dualize(tp1,tp2,tp5);
    getVertexRef(1)=Point::dualize(tp1,tp2,tp6);
    
    getVertexRef(2)=Point::dualize(tp3,tp4,tp5);
    getVertexRef(3)=Point::dualize(tp3,tp4,tp6);
    
    getVertexRef(4)=Point::dualize(tp1,tp3,tp5);
    getVertexRef(5)=Point::dualize(tp1,tp3,tp6);
    
    getVertexRef(6)=Point::dualize(tp2,tp4,tp5);
    getVertexRef(7)=Point::dualize(tp2,tp4,tp6);
}
void Hexahedron::initStructure()
{
    structure.addEdge(0, 1);
    structure.addEdge(2, 3);
    structure.addEdge(4, 5);
    structure.addEdge(6, 7);
    
    structure.addEdge(5, 1);
    structure.addEdge(5, 3);
    structure.addEdge(4, 0);
    structure.addEdge(4, 2);
    
    structure.addEdge(7, 1);
    structure.addEdge(7, 3);
    structure.addEdge(6, 0);
    structure.addEdge(6, 2);
    
    addFace<FramedFace>({4,0,6,2});
    addFace<FramedFace>({5,1,7,3});
    addFace<FramedFace>({5,4,2,3});
    addFace<FramedFace>({3,2,6,7});
    addFace<FramedFace>({0,1,7,6});
    addFace<FramedFace>({4,5,1,0});
}
void Hexahedron::setFaceAttributes()
{
    
}

void Hexahedron::initAtts()
{
    addAttribute("height",Attribute(1.715,0.1,3.0,0.01)); //current,lower,upper,increment
    addAttribute("widthh",Attribute(1.055,0.1,3.0,0.01));
    addAttribute("twist",Attribute(26,-60,60,1));
}

Hexahedron::Hexahedron():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Hexahedron::Hexahedron(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Hexahedron* Hexahedron::doClone() const
{
    return new Hexahedron(*this);
}

//
//  FiveRectangles.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/13/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include "FiveRectangles.h"
#include "TubularPolygon.h"

void FiveRectangles::setVertexValues()
{
    double length=getAttribute("length").getCurrentValue();
    double width=getAttribute("width").getCurrentValue();
    double twist=getAttribute("twist").getCurrentValue();
    double shift=getAttribute("shift").getCurrentValue();
    
    double HEIGHT=length/2.0;
    
    setVertex(0, HEIGHT,.5,-.6882);
    setVertex(1, HEIGHT,-.5,-.6882);
    setVertex(2, HEIGHT,-.8090,.2629);
    setVertex(3, HEIGHT,0,.8507);
    setVertex(4, HEIGHT,.8090,.2629);
    
    setVertex(5, -HEIGHT,.5,-.6882);
    setVertex(6, -HEIGHT,-.5,-.6882);
    setVertex(7, -HEIGHT,-.8090,.2629);
    setVertex(8, -HEIGHT,0,.8507);
    setVertex(9, -HEIGHT,.8090,.2629);
    
    Point c1(HEIGHT,0,0);
    Point c2(-HEIGHT,0,0);
    double ddd=Point::distance(c1, getVertex(0));
    double shiftFactor=(ddd+shift)/ddd;
    
    getVertexRef(0)=Point::extendLine(c1, getVertex(0), shiftFactor);
    getVertexRef(1)=Point::extendLine(c1, getVertex(1), shiftFactor);
    getVertexRef(2)=Point::extendLine(c1, getVertex(2), shiftFactor);
    getVertexRef(3)=Point::extendLine(c1, getVertex(3), shiftFactor);
    getVertexRef(4)=Point::extendLine(c1, getVertex(4), shiftFactor);
    
    getVertexRef(5)=Point::extendLine(c2, getVertex(5), shiftFactor);
    getVertexRef(6)=Point::extendLine(c2, getVertex(6), shiftFactor);
    getVertexRef(7)=Point::extendLine(c2, getVertex(7), shiftFactor);
    getVertexRef(8)=Point::extendLine(c2, getVertex(8), shiftFactor);
    getVertexRef(9)=Point::extendLine(c2, getVertex(9), shiftFactor);
    
    Point origin(0,0,0);
    double dist=Point::distance(c1, getVertex(0));
    double extension=(dist+width)/dist;

    getVertexRef(10)=Point::extendLine(c1, getVertex(0), extension);
    getVertexRef(11)=Point::extendLine(c1, getVertex(1), extension);
    getVertexRef(12)=Point::extendLine(c1, getVertex(2), extension);
    getVertexRef(13)=Point::extendLine(c1, getVertex(3), extension);
    getVertexRef(14)=Point::extendLine(c1, getVertex(4), extension);
    
    getVertexRef(15)=Point::extendLine(c2, getVertex(5), extension);
    getVertexRef(16)=Point::extendLine(c2, getVertex(6), extension);
    getVertexRef(17)=Point::extendLine(c2, getVertex(7), extension);
    getVertexRef(18)=Point::extendLine(c2, getVertex(8), extension);
    getVertexRef(19)=Point::extendLine(c2, getVertex(9), extension);
    
    getVertexRef(0).twistPoint(origin, Point(0,.5,-.6882), twist);
    getVertexRef(1).twistPoint(origin, Point(0,-.5,-.6882), twist);
    getVertexRef(2).twistPoint(origin, Point(0,-.8090,.2629), twist);
    getVertexRef(3).twistPoint(origin, Point(0,0,.8507), twist);
    getVertexRef(4).twistPoint(origin, Point(0,.8090,.2629), twist);
    getVertexRef(10).twistPoint(origin, Point(0,.5,-.6882), twist);
    getVertexRef(11).twistPoint(origin, Point(0,-.5,-.6882), twist);
    getVertexRef(12).twistPoint(origin, Point(0,-.8090,.2629), twist);
    getVertexRef(13).twistPoint(origin, Point(0,0,.8507), twist);
    getVertexRef(14).twistPoint(origin, Point(0,.8090,.2629), twist);
    
    getVertexRef(5).twistPoint(origin, Point(0,.5,-.6882), twist);
    getVertexRef(6).twistPoint(origin, Point(0,-.5,-.6882), twist);
    getVertexRef(7).twistPoint(origin, Point(0,-.8090,.2629), twist);
    getVertexRef(8).twistPoint(origin, Point(0,0,.8507), twist);
    getVertexRef(9).twistPoint(origin, Point(0,.8090,.2629), twist);
    getVertexRef(15).twistPoint(origin, Point(0,.5,-.6882), twist);
    getVertexRef(16).twistPoint(origin, Point(0,-.5,-.6882), twist);
    getVertexRef(17).twistPoint(origin, Point(0,-.8090,.2629), twist);
    getVertexRef(18).twistPoint(origin, Point(0,0,.8507), twist);
    getVertexRef(19).twistPoint(origin, Point(0,.8090,.2629), twist);
}
void FiveRectangles::initStructure()
{
    structure.addEdge(0, 10);
    structure.addEdge(1, 11);
    structure.addEdge(2, 12);
    structure.addEdge(3, 13);
    structure.addEdge(4, 14);
    
    structure.addEdge(5, 15);
    structure.addEdge(6, 16);
    structure.addEdge(7, 17);
    structure.addEdge(8, 18);
    structure.addEdge(9, 19);
    
    structure.addEdge(0, 5);
    structure.addEdge(1, 6);
    structure.addEdge(2, 7);
    structure.addEdge(3, 8);
    structure.addEdge(4, 9);
    
    structure.addEdge(10, 15);
    structure.addEdge(11, 16);
    structure.addEdge(12, 17);
    structure.addEdge(13, 18);
    structure.addEdge(14, 19);
    
    addFace<TubularPolygon>({0,10,15,5});
    addFace<TubularPolygon>({1,11,16,6});
    addFace<TubularPolygon>({2,12,17,7});
    addFace<TubularPolygon>({3,13,18,8});
    addFace<TubularPolygon>({4,14,19,9});
}
void FiveRectangles::setFaceAttributes()
{
    
}

void FiveRectangles::initAtts()
{
    addAttribute("length",Attribute(2.5,0.0,10.0,0.0001)); //current,lower,upper,increment
    addAttribute("width",Attribute(0.0,0.0,5.0,0.0001)); //current,lower,upper,increment
    addAttribute("twist",Attribute(0.0,-180,180,1)); //current,lower,upper,increment
    addAttribute("shift",Attribute(0.0,-180,180,1)); //current,lower,upper,increment
}

FiveRectangles::FiveRectangles():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
FiveRectangles::FiveRectangles(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
FiveRectangles* FiveRectangles::doClone() const
{
    return new FiveRectangles(*this);
}
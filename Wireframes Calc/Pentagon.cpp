//
//  Pentagon.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/20/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//


#include <cmath>
#include "Pentagon.h"
#include "TubularPolygon.h"

void Pentagon::setVertexValues()
{
    //Point verticies[vertexNum];
    getVertexRef(0).setAll(0,.5,-.6882);
    getVertexRef(1).setAll(0,-.5,-.6882);
    getVertexRef(2).setAll(0,-.8090,.2629);
    getVertexRef(3).setAll(0,0,.8507);
    getVertexRef(4).setAll(0,.8090,.2629);
}
void Pentagon::initStructure()
{
    structure.addEdge(0, 1);
    structure.addEdge(1, 2);
    structure.addEdge(2, 3);
    structure.addEdge(3, 4);
    structure.addEdge(4, 0);
    
    addFace<TubularPolygon>({0,1,2,3,4});
}
void Pentagon::setFaceAttributes()
{
    
}

void Pentagon::initAtts()
{
    
}

Pentagon::Pentagon():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Pentagon::Pentagon(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
Pentagon* Pentagon::doClone() const
{
    return new Pentagon(*this);
}
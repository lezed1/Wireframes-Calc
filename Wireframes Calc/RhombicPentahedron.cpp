//
//  RhombicPentahedron.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/8/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>
#include "RhombicPentahedron.h"

void RhombicPentahedron::setVertexValues()
{
    double att0=getAttribute("crimp").getCurrentValue();
    //Point verticies[vertexNum];
    getVertexRef(0).setAll(0,.5,-.6882);
    getVertexRef(1).setAll(0,-.5,-.6882);
    getVertexRef(2).setAll(0,-.8090,.2629);
    getVertexRef(3).setAll(0,0,.8507);
    getVertexRef(4).setAll(0,.8090,.2629);
    getVertexRef(5).setAll(1-att0,0,0);
    getVertexRef(6).setAll(-(1-att0),0,0);
    scaleTo(att0);
    scaleToOne();
}
void RhombicPentahedron::initStructure()
{
    structure.addEdge(5, 0);
    structure.addEdge(5, 1);
    structure.addEdge(5, 2);
    structure.addEdge(5, 3);
    structure.addEdge(5, 4);
    
    structure.addEdge(6, 0);
    structure.addEdge(6, 1);
    structure.addEdge(6, 2);
    structure.addEdge(6, 3);
    structure.addEdge(6, 4);
}
void RhombicPentahedron::setFaceAttributes()
{
    
}

void RhombicPentahedron::initAtts()
{
    addAttribute("crimp",Attribute(0.5,0.0,1.0,0.0001)); //current,lower,upper,increment
}

RhombicPentahedron::RhombicPentahedron():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
RhombicPentahedron::RhombicPentahedron(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
RhombicPentahedron* RhombicPentahedron::doClone() const
{
    return new RhombicPentahedron(*this);
}
void RhombicPentahedron::scaleTo(double scaleto)
{
    double x1=0;
    double y1=0;
    double z1=0;
    
    double x2=getVertex(0).getX();
    double y2=getVertex(0).getY();
    double z2=getVertex(0).getZ();
    
    double diffX=(x2-x1);
    double diffY=(y2-y1);
    double diffZ=(z2-z1);
    
    double pentscale;
    double check=diffX*diffX+diffY*diffY+diffZ*diffZ;
    if (check==0)
    {
        pentscale=0;
    }
    else
    {
        pentscale=scaleto/sqrt(diffX*diffX+diffY*diffY+diffZ*diffZ);
    }
    
    getVertexRef(0)*=pentscale;
    getVertexRef(1)*=pentscale;
    getVertexRef(2)*=pentscale;
    getVertexRef(3)*=pentscale;
    getVertexRef(4)*=pentscale;
}
void RhombicPentahedron::scaleToOne()
{
    double x1=getVertex(5).getX();
    double y1=getVertex(5).getY();
    double z1=getVertex(5).getZ();
    
    double x2=getVertex(0).getX();
    double y2=getVertex(0).getY();
    double z2=getVertex(0).getZ();
    
    double diffX=(x2-x1);
    double diffY=(y2-y1);
    double diffZ=(z2-z1);
    
    double scale;
    double check=diffX*diffX+diffY*diffY+diffZ*diffZ;
    if (check==0)
    {
        scale=0;
    }
    else
    {
        scale=1.0/sqrt(diffX*diffX+diffY*diffY+diffZ*diffZ);
    }
    
    getVertexRef(0)*=scale;
    getVertexRef(1)*=scale;
    getVertexRef(2)*=scale;
    getVertexRef(3)*=scale;
    getVertexRef(4)*=scale;
    getVertexRef(5)*=scale;
    getVertexRef(6)*=scale;
}
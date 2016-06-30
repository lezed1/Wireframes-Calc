//
//  FIT.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/29/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include "FIT.h"
#include "FramedFace.h"

void FIT::setVertexValues()
{
    setVertex(0, 1.732051,0.000000,0.000000);
    setVertex(1, -0.577350,-1.414214,0.816497);
    setVertex(2, -0.577350,1.414214,0.816497);
    setVertex(3, -0.577350,0.000000,-1.632993);
    
    setVertex(4, 1.290994,-0.437016,-1.068808);
    setVertex(5, -1.290994,-1.144123,-0.155937);
    setVertex(6, 0.577350,-0.000000,1.632993);
    setVertex(7, -0.577350,1.581139,-0.408248);
    
    setVertex(8, 0.577350,1.414214,-0.816497);
    setVertex(9, 1.290994,-0.707107,0.912871);
    setVertex(10, -1.290994,0.437016,1.068808);
    setVertex(11, -0.577350,-1.144123,-1.165182);
    
    setVertex(12, 1.290994,1.144123,0.155937);
    setVertex(13, -0.577350,-0.437016,1.573431);
    setVertex(14, -1.290994,0.707107,-0.912871);
    setVertex(15, 0.577350,-1.414214,-0.816497);
    
    setVertex(16, 0.577350,-1.581139,0.408248);
    setVertex(17, -1.732051,0.000000,-0.000000);
    setVertex(18, 0.577350,1.144123,1.165182);
    setVertex(19, 0.577350,0.437016,-1.573431);
}
void FIT::initStructure()
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
    
    structure.addEdge(8, 9);
    structure.addEdge(8, 10);
    structure.addEdge(8, 11);
    structure.addEdge(9, 10);
    structure.addEdge(9, 11);
    structure.addEdge(10, 11);
    
    structure.addEdge(12, 13);
    structure.addEdge(12, 14);
    structure.addEdge(12, 15);
    structure.addEdge(13, 14);
    structure.addEdge(13, 15);
    structure.addEdge(14, 15);
    
    structure.addEdge(16, 17);
    structure.addEdge(16, 18);
    structure.addEdge(16, 19);
    structure.addEdge(17, 18);
    structure.addEdge(17, 19);
    structure.addEdge(18, 19);
    
    addFace<FramedFace>({0,1,2});
    addFace<FramedFace>({0,1,3});
    addFace<FramedFace>({0,2,3});
    addFace<FramedFace>({1,2,3});
    
    addFace<FramedFace>({4,5,6});
    addFace<FramedFace>({4,5,7});
    addFace<FramedFace>({4,6,7});
    addFace<FramedFace>({5,6,7});
    
    addFace<FramedFace>({8,9,10});
    addFace<FramedFace>({8,9,11});
    addFace<FramedFace>({8,10,11});
    addFace<FramedFace>({9,10,11});
    
    addFace<FramedFace>({12,13,14});
    addFace<FramedFace>({12,13,15});
    addFace<FramedFace>({12,14,15});
    addFace<FramedFace>({13,14,15});
    
    addFace<FramedFace>({16,17,18});
    addFace<FramedFace>({16,17,19});
    addFace<FramedFace>({16,18,19});
    addFace<FramedFace>({17,18,19});
}
void FIT::setFaceAttributes()
{
    
}

void FIT::initAtts()
{
    
}

FIT::FIT():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
FIT::FIT(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
FIT* FIT::doClone() const
{
    return new FIT(*this);
}
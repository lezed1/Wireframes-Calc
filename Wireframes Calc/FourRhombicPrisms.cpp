//
//  FourRhombicPrisms.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 7/18/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "FourRhombicPrisms.h"
#include "FramedFace.h"

void FourRhombicPrisms::setVertexValues()
{
    Point axis1(1,0,0);
    Point axis2(0,0,0);
    double kite=getAttribute("kite").getCurrentValue();
    double shift=getAttribute("shift").getCurrentValue();
    double twist=getAttribute("twist").getCurrentValue();
    double kite1=kite;
    double kite2=kite;
    double height=0.5;
    
    Point tp1(kite1+shift,height,0);
    Point tp2(shift,height,1);
    Point tp3(-kite2+shift,height,0);
    Point tp4(shift,height,-1);
    Point tp5(kite1+shift,-height,0);
    Point tp6(shift,-height,1);
    Point tp7(-kite2+shift,-height,0);
    Point tp8(shift,-height,-1);
    
    Point tp9(-kite1-shift,height,0);
    Point tp10(-shift,height,1);
    Point tp11(kite2-shift,height,0);
    Point tp12(-shift,height,-1);
    Point tp13(-kite1-shift,-height,0);
    Point tp14(-shift,-height,1);
    Point tp15(kite2-shift,-height,0);
    Point tp16(-shift,-height,-1);
    
    tp1.twistPoint(axis2,axis1,twist);
    tp2.twistPoint(axis2,axis1,twist);
    tp3.twistPoint(axis2,axis1,twist);
    tp4.twistPoint(axis2,axis1,twist);
    tp5.twistPoint(axis2,axis1,twist);
    tp6.twistPoint(axis2,axis1,twist);
    tp7.twistPoint(axis2,axis1,twist);
    tp8.twistPoint(axis2,axis1,twist);
    
    tp9.twistPoint(axis2,axis1,-twist);
    tp10.twistPoint(axis2,axis1,-twist);
    tp11.twistPoint(axis2,axis1,-twist);
    tp12.twistPoint(axis2,axis1,-twist);
    tp13.twistPoint(axis2,axis1,-twist);
    tp14.twistPoint(axis2,axis1,-twist);
    tp15.twistPoint(axis2,axis1,-twist);
    tp16.twistPoint(axis2,axis1,-twist);
    
    getVertexRef(0)=Point::twistPoint(tp1, axis2, axis1, 45);
    getVertexRef(1)=Point::twistPoint(tp2, axis2, axis1, 45);
    getVertexRef(2)=Point::twistPoint(tp3, axis2, axis1, 45);
    getVertexRef(3)=Point::twistPoint(tp4, axis2, axis1, 45);
    getVertexRef(4)=Point::twistPoint(tp5, axis2, axis1, 45);
    getVertexRef(5)=Point::twistPoint(tp6, axis2, axis1, 45);
    getVertexRef(6)=Point::twistPoint(tp7, axis2, axis1, 45);
    getVertexRef(7)=Point::twistPoint(tp8, axis2, axis1, 45);
    getVertexRef(8)=Point::twistPoint(tp9, axis2, axis1, 45);
    getVertexRef(9)=Point::twistPoint(tp10, axis2, axis1, 45);
    getVertexRef(10)=Point::twistPoint(tp11, axis2, axis1, 45);
    getVertexRef(11)=Point::twistPoint(tp12, axis2, axis1, 45);
    getVertexRef(12)=Point::twistPoint(tp13, axis2, axis1, 45);
    getVertexRef(13)=Point::twistPoint(tp14, axis2, axis1, 45);
    getVertexRef(14)=Point::twistPoint(tp15, axis2, axis1, 45);
    getVertexRef(15)=Point::twistPoint(tp16, axis2, axis1, 45);
    
    getVertexRef(16)=Point::twistPoint(tp1, axis2, axis1, -45);
    getVertexRef(17)=Point::twistPoint(tp2, axis2, axis1, -45);
    getVertexRef(18)=Point::twistPoint(tp3, axis2, axis1, -45);
    getVertexRef(19)=Point::twistPoint(tp4, axis2, axis1, -45);
    getVertexRef(20)=Point::twistPoint(tp5, axis2, axis1, -45);
    getVertexRef(21)=Point::twistPoint(tp6, axis2, axis1, -45);
    getVertexRef(22)=Point::twistPoint(tp7, axis2, axis1, -45);
    getVertexRef(23)=Point::twistPoint(tp8, axis2, axis1, -45);
    getVertexRef(24)=Point::twistPoint(tp9, axis2, axis1, -45);
    getVertexRef(25)=Point::twistPoint(tp10, axis2, axis1, -45);
    getVertexRef(26)=Point::twistPoint(tp11, axis2, axis1, -45);
    getVertexRef(27)=Point::twistPoint(tp12, axis2, axis1, -45);
    getVertexRef(28)=Point::twistPoint(tp13, axis2, axis1, -45);
    getVertexRef(29)=Point::twistPoint(tp14, axis2, axis1, -45);
    getVertexRef(30)=Point::twistPoint(tp15, axis2, axis1, -45);
    getVertexRef(31)=Point::twistPoint(tp16, axis2, axis1, -45);
}
void FourRhombicPrisms::initStructure()
{
    structure.addEdge(0, 4);
    structure.addEdge(1, 5);
    structure.addEdge(2, 6);
    structure.addEdge(3, 7);
    structure.addEdge(0, 1);
    structure.addEdge(1, 2);
    structure.addEdge(2, 3);
    structure.addEdge(3, 0);
    structure.addEdge(4, 5);
    structure.addEdge(5, 6);
    structure.addEdge(6, 7);
    structure.addEdge(7, 4);
    
    structure.addEdge(8, 12);
    structure.addEdge(9, 13);
    structure.addEdge(10, 14);
    structure.addEdge(11, 15);
    structure.addEdge(8, 9);
    structure.addEdge(9, 10);
    structure.addEdge(10, 11);
    structure.addEdge(11, 8);
    structure.addEdge(12, 13);
    structure.addEdge(13, 14);
    structure.addEdge(14, 15);
    structure.addEdge(15, 12);
    
    structure.addEdge(16, 20);
    structure.addEdge(17, 21);
    structure.addEdge(18, 22);
    structure.addEdge(19, 23);
    structure.addEdge(16, 17);
    structure.addEdge(17, 18);
    structure.addEdge(18, 19);
    structure.addEdge(19, 16);
    structure.addEdge(20, 21);
    structure.addEdge(21, 22);
    structure.addEdge(22, 23);
    structure.addEdge(23, 20);
    
    structure.addEdge(24, 28);
    structure.addEdge(25, 29);
    structure.addEdge(26, 30);
    structure.addEdge(27, 31);
    structure.addEdge(24, 25);
    structure.addEdge(25, 26);
    structure.addEdge(26, 27);
    structure.addEdge(27, 24);
    structure.addEdge(28, 29);
    structure.addEdge(29, 30);
    structure.addEdge(30, 31);
    structure.addEdge(31, 28);
    
    addFace<FramedFace>({0,1,2,3});
    addFace<FramedFace>({4,5,6,7});
    addFace<FramedFace>({0,1,5,4});
    addFace<FramedFace>({1,2,6,5});
    addFace<FramedFace>({2,3,7,6});
    addFace<FramedFace>({3,0,4,7});
    
    addFace<FramedFace>({8,9,10,11});
    addFace<FramedFace>({12,13,14,15});
    addFace<FramedFace>({8,9,13,12});
    addFace<FramedFace>({9,10,14,13});
    addFace<FramedFace>({10,11,15,14});
    addFace<FramedFace>({11,8,12,15});
    
    addFace<FramedFace>({16,17,18,19});
    addFace<FramedFace>({20,21,22,23});
    addFace<FramedFace>({16,17,21,20});
    addFace<FramedFace>({17,18,22,21});
    addFace<FramedFace>({18,19,23,22});
    addFace<FramedFace>({19,16,20,23});
    
    addFace<FramedFace>({24,25,26,27});
    addFace<FramedFace>({28,29,30,31});
    addFace<FramedFace>({24,25,29,28});
    addFace<FramedFace>({25,26,30,29});
    addFace<FramedFace>({26,27,31,30});
    addFace<FramedFace>({27,24,28,31});
}
void FourRhombicPrisms::setFaceAttributes()
{
    
}

void FourRhombicPrisms::initAtts()
{
    addAttribute("kite",Attribute(0.8,0.74,0.86,0.01)); //current,lower,upper,increment
    addAttribute("shift",Attribute(0.24,0.18,0.30,0.01));
    addAttribute("twist",Attribute(14,8,20,1));
}

FourRhombicPrisms::FourRhombicPrisms():Polyhedron(vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
FourRhombicPrisms::FourRhombicPrisms(double xrot,double yrot,double zrot):Polyhedron(xrot,yrot,zrot,vertexNum)
{
    initStructure();
    initAtts();
    setValues();
}
FourRhombicPrisms* FourRhombicPrisms::doClone() const
{
    return new FourRhombicPrisms(*this);
}

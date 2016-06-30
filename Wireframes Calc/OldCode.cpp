//
//  OldCode.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/28/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include "OldCode.h"
#include <iostream>
#include <ctime>
//#include "PolyhedralSkeleton.h"
//#include "NonFramedFace.h"
//#include "FramedFace.h"
#include "DihedralFace.h"
//#include "PovFileGenerator.h"

#include "Frame.h"
#include "Optimization.h"

#include "Prisms.h"
#include "Hexahedron.h"
#include "Tetrahedron.h"
#include "Bilunabirotunda.h"
#include "TwoTetrahedra.h"
#include "HexagonalTetrahedron.h"
#include "FourRhombicPrisms.h"
#include "Hendecahedron.h"

#include "FiveCompound.h"
#include "FifteenCompound.h"
#include "ThreeCompound.h"
#include "TenCompound.h"
#include "SixCompound.h"
#include "RhombicHexahedron.h"

//#include "Polypolyhedra.h"
#include "Polypolyhedra2.h"

void oldCode1() //4/26/15 to 5/28/16
{
    /*PolyhedralSkeleton stateManager(8);
     stateManager.setVertex(0, 1,1,1);
     stateManager.setVertex(1, 1,1,-1); //
     stateManager.setVertex(2, 1,-1,-1);
     stateManager.setVertex(3, 1,-1,1);
     stateManager.setVertex(4, -1,1,1);
     stateManager.setVertex(5, -1,1,-1);
     stateManager.setVertex(6, -1,-1,-1);
     stateManager.setVertex(7, -1,-1,1); //
     
     stateManager.addEdge(0, 1);
     stateManager.addEdge(1, 2);
     stateManager.addEdge(2, 3);
     stateManager.addEdge(3, 0);
     
     stateManager.addEdge(4, 5);
     stateManager.addEdge(5, 6);
     stateManager.addEdge(6, 7);
     stateManager.addEdge(7, 4);
     
     stateManager.addEdge(0, 4);
     stateManager.addEdge(1, 5);
     stateManager.addEdge(2, 6);
     stateManager.addEdge(3, 7);
     
     //stateManager.addFace({0,1,5,4});
     //Face f=stateManager.getFace(0);
     //std::cout << f.verticesString() << "\n" << f.edgesString() << "\n";
     
     stateManager.addFace<FramedFace>({0,1,2,3});
     stateManager.addFace<FramedFace>({4,5,6,7});
     stateManager.addFace<FramedFace>({0,1,5,4});
     stateManager.addFace<FramedFace>({1,2,6,5});
     stateManager.addFace<FramedFace>({2,3,7,6});
     stateManager.addFace<DihedralFace>({3,0,4,7});
     stateManager.setFaceAttribute(5, "uorl", -1.0);
     stateManager.setFaceAttribute(5, "dihedral", 45.0);
     
     //std::cout << "--------\n";
     //for (int i=0;i<stateManager.getEdgeNum();i++)
     //{
     //    Edge e=stateManager.getEdge(i);
     //    std::cout << e.endPointsString() << "\n" << e.adjacentEdgesString();
     //    std::cout << "\n--------\n";
     //}
     //stateManager.setVertex(3, 0,0,0);
     //stateManager.setVertex(4, 0,1,0);
     //stateManager.printPovRayCode(0.1);
     //stateManager.getPoint(3)=Point(2,2,2);
     std::cout << "\n";
     stateManager.printPovFaces(0.9);*/
    
    /*RectPrism prism(0, 30, 0);
     prism.setAttribute("height", 0.67);
     prism.setAttribute("dihedral", 30.0);
     
     RectPrism prism2;
     prism2=prism;
     
     //prism.printStructurePointerInfo();
     //prism2.printStructurePointerInfo();
     
     prism2.setRotation(0, 0, 0);
     prism2.setAttribute("height", 1.0);
     prism2.setAttribute("dihedral", 45.0);
     
     prism.setAttribute("dihedral", -30.0);
     
     prism.printPovRayFrame(0.4,"Green");
     prism2.printPovRayFrame(0.2,"Blue");*/
    
    /*RectPrism prism(0,0,0);
     prism.setAttribute("height", 1.0);
     prism.setAttribute("dihedral", 0.0);
     
     FiveCompound compound(prism);
     compound.printPovRayFrame(0.2, {"Blue","Green","Red","Yellow","Orange"});*/
    
    std::vector<std::string> colors1={"Blue","Green","Red","Yellow","Orange","Violet","Cyan","Magenta","Black","Brown","CadetBlue","Aquamarine","Gray","MediumVioletRed","BlueViolet"};
    std::vector<std::string> colors2={"Yellow","Green","Blue","Red","Violet","MediumVioletRed","CadetBlue","Orange","CornflowerBlue","DarkGreen","Cyan","Magenta","Aquamarine","BlueViolet","Brown"};
    std::vector<std::string> colors3={"MediumVioletRed","CadetBlue","Coral","CornflowerBlue","DarkGreen","Blue","Gray","Black","Magenta","Green","Red","Yellow","Cyan","Brown","Orange"};
    
    
    //Hexahedron hexa(0,0,0);
    //FifteenCompound compound(hexa);
    //compound.printPovRayFrame(0.0861822, colors1);
    
    //Tetrahedron tet(0,0,0);
    //FiveCompound compound(tet);
    //std::cout << compound.computeWidth() << "\n";
    //compound.printPovRayFrame(6.71627, colors1);
    
    //Hexahedron hexa(0,0,0);
    //Hexahedron k2(0,0,0);
    //k2=hexa;
    //FifteenCompound compound(hexa);
    //std::cout << compound.computeWidth() << "\n";
    //compound.optimizeSphereCylinder();
    
    //std::cout << computeCompoundWidth(compound) << "\n";
    
    /*Bilunabirotunda blbr(0,0,0);
     ThreeCompound compound(blbr);
     double width=computeCompoundWidth(compound);
     std::cout << "optimal width:: " << width << "\n\n";
     //std::cout << "long edge:: " << blbr.getLongestEdgeLength() << "\n\n";
     compound.printPovRayFrame(width, {"Magenta","Aquamarine","Yellow"});*/
    
    //TwoTetrahedra tt(0,0,0);
    //FifteenCompound compound(tt);
    //std::cout << compound.computeWidth() << "\n";
    
    //HexagonalTetrahedron ht(0,0,0);
    //FiveCompound compound(ht);
    //compound.printPovRaySkeleton(0.1, {"MediumVioletRed","CadetBlue","Coral","CornflowerBlue","DarkGreen"});
    
    //pph5hextet(colors3);
    
    /*Tetrahedron tetrahedron;
     FiveCompound fit(tetrahedron);
     const Polyhedron* t1=fit.getPolyhedron(0);
     const Polyhedron* t2=fit.getPolyhedron(1);
     double dist=0.0;
     for (int i=0;i<t1->getVertexNum();i++)
     {
     for (int j=0;j<t2->getVertexNum();j++)
     {
     Point p1=t1->getVertex(i);
     Point p2=t2->getVertex(j);
     double distcheck=Point::distance(p1, p2);
     if (distcheck>dist)
     {
     dist=distcheck;
     }
     }
     }
     double edgelength=t1->getEdgeLine(0).getDistance();
     //edgelength/dist=unitlength/???
     double unitlength=7.071067812;
     std::cout << "\n\n" << dist*unitlength/edgelength << "\n";
     
     Point p1(1,0,0);
     p1.twistPoint(Point(0,0,0),Point(0,0,-1), 90);
     std::cout << Point::angleMeasure(Point(0,0,1), Point(0,0,0), Point(0,1,0)) << "\n";*/
    
    //FourRhombicPrisms frp(0,0,0);
    //ThreeCompound compound(frp);
    
    //compound.printPovRayFrame(0.05, colors1);
    //std::cout << computeCompoundWidth(compound) << "\n";
    
    /*for (double i=0.836;i<=0.838;i+=0.0001)
     {
     compound.setPolyhedronAttribute("kite", i);
     for (double j=0.245;j<=0.247;j+=0.0001)
     {
     compound.setPolyhedronAttribute("shift", j);
     for (double k=15.4;k<=15.6;k+=0.01)
     {
     compound.setPolyhedronAttribute("twist", k);
     std::cout << i << " " << j << " " << k << " " << computeCompoundWidth(compound) << "\n";
     }
     }
     }*/
    
     Hendecahedron hd(0,0,0);
     hd.setAttribute("poleHeight", 3.207);
     hd.setAttribute("triangleHeight", 1.198);
     hd.setAttribute("twist", 3.8);
     //TenCompound compound(hd);
     //compound.setPolyhedronAttribute("poleHeight", 3.207);
     //compound.setPolyhedronAttribute("triangleHeight", 1.198);
     //compound.setPolyhedronAttribute("twist", 3.8);
     //compound.printPovRayFrame(0.0350733, colors3);
     
     //4-valent corner
     Point d1=hd.getVertex(0);
     Point d2=hd.getVertex(1);
     Point d3=hd.getVertex(2);
     Point d8=hd.getVertex(7);
     Point d9=hd.getVertex(8);
     double angle213=Point::angleMeasure(d2, d1, d3)/2.0;
     double angle318=Point::angleMeasure(d3, d1, d8)/2.0;
     double angle219=Point::angleMeasure(d2, d1, d9)/2.0;
     double angle819=Point::angleMeasure(d8, d1, d9)/2.0;
     std::cout << degrees(angle213) << " " << degrees(angle318) << " " << degrees(angle219) << " " << degrees(angle819) << "\n";
     
     //3-valent corner
     Point d4=hd.getVertex(3);
     Point d7=hd.getVertex(6);
     double angle187=Point::angleMeasure(d1, d8, d7)/2.0;
     double angle184=Point::angleMeasure(d1, d8, d4)/2.0;
     double angle784=Point::angleMeasure(d7, d8, d4)/2.0;
     std::cout << degrees(angle187) << " " << degrees(angle184) << " " << degrees(angle784) << "\n";
     
     std::cout << hd.getLongestEdgeLength()/(4.0*0.0350733) << "\n";
    
    /*for (double i=2.6;i<=3.6;i+=0.01)
     {
     compound.setPolyhedronAttribute("poleHeight", i);
     for (double j=0.5;j<=1.5;j+=0.01)
     {
     if (j>i) {continue;}
     compound.setPolyhedronAttribute("triangleHeight", j);
     for (double k=3.0;k<=4.0;k+=0.1)
     {
     compound.setPolyhedronAttribute("twist", k);
     double longLength=compound.getPolyhedron(0)->getLongestEdgeLength();
     double widthh=computeCompoundWidth(compound);
     double paper=longLength/(4.0*widthh);
     if (paper>100) {continue;}
     std::cout << i << " " << j << " " << "0" << " " << widthh << " " << paper << "\n";
     }
     std::cout << "--------------\n";
     }
     }*/
    
    //polypolyhedraCode();
}
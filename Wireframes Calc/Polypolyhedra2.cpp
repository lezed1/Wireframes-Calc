//
//  Polypolyhedra2.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/22/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include <vector>
#include <array>
#include <cmath>

#include "Polypolyhedra2.h"
#include "PPHAlgorithms.h"
#include "HexagonalTetrahedron.h"
#include "RhombicPentahedron.h"
#include "RhombicHexahedron.h"
#include "Pentagon.h"
#include "Tetrahedron.h"
#include "FiveCompound.h"
#include "FourCompound.h"
#include "TenCompound.h"
#include "SixCompound.h"
#include "basicshapes.h"
#include "Matrix3x3.h"
#include "Line2D.h"
#include "PovFileGenerator.h"
#include "Utilities.h"

#define EPS 0.000001

void polypolyhedronUnit(const Compound* compound,int edge,int frame,const std::string& color,bool symmetrize,int v1,int v2,int v3,PolypolyOutput output)
{
    int edgeID=edge;
    
    //find edges around the endpoints of the target edge
    const Polyhedron* ref=compound->getPolyhedron(frame);
    Line refEdge=ref->getEdgeLine(edgeID);
    Matrix3x3 polyBasisToStdBasis=generateTargetEdgeBasis(edge, ref);
    std::vector<Point> realCrossSectionPoints=generateCrossSection(edge, frame, compound, polyBasisToStdBasis, symmetrize);

    if (output==CrossSection2D)
    {
        std::cout << "real cross section points: \n";
        for (int i=0;i<realCrossSectionPoints.size();i++)
        {
            std::cout << realCrossSectionPoints.at(i).toString() << "\n";
        }
        std::cout << "\n";
        std::cout << "------------------------\n";
        return;
    }
    
    unsigned long crossSectionSize=realCrossSectionPoints.size();
    bool crossSectionVerticesSmall=v1<0 || v2<0 || v3<0;
    bool crossSectionVerticesLarge=v1>=crossSectionSize || v2>=crossSectionSize || v3>=crossSectionSize;
    if (crossSectionVerticesSmall || crossSectionVerticesLarge)
    {
        std::string verticesString="["+intToString(v1)+","+intToString(v2)+","+intToString(v3)+"]";
        std::string rangeString="0-"+intToString((int) (crossSectionSize-1));
        std::cout << "Error: polypolyhedron--Cross section vertices indices out of range: " << verticesString << " is outside range " << rangeString << "\n";
        std::cout << "------------------------\n";
        return;
    }
    
    std::vector<Point> finalSection(3);
    finalSection.at(0)=realCrossSectionPoints.at(v1);
    finalSection.at(1)=realCrossSectionPoints.at(v2);
    finalSection.at(2)=realCrossSectionPoints.at(v3);
    
    //find lines parallel to the target edge through the cross section points in 3d
    //these will be the segments of the stick edges
    std::vector<Line> crossSectionLines=generateStickEdges(finalSection, polyBasisToStdBasis, refEdge);
    
    //construct end caps for stick
    std::vector<Line> refEdgeEndpoint1Lines=ref->edgesToLines(ref->getEdgesAroundEdge(edgeID,1));
    std::vector<Line> refEdgeEndpoint2Lines=ref->edgesToLines(ref->getEdgesAroundEdge(edgeID,2));
    
    std::vector<Point> endCap1=generateEndCap(refEdge,refEdge.getPointA(),refEdgeEndpoint1Lines,crossSectionLines);
    std::vector<Point> endCap2=generateEndCap(refEdge,refEdge.getPointB(),refEdgeEndpoint2Lines,crossSectionLines);
    
    //int unitIndex1=(int) (topIndex+endCap2.size()-1)%endCap2.size();
    //int unitIndex2=(int) (topIndex+1)%endCap2.size();
    
    int unitIndex1=0;
    int unitIndex2=2;
    int topIndex=1;
    
    double angle1=Point::angleMeasure(endCap1.at(topIndex), endCap2.at(topIndex), endCap2.at(unitIndex1));
    double angle2=Point::angleMeasure(endCap2.at(topIndex), endCap1.at(topIndex), endCap1.at(unitIndex1));
    
    //    std::cout << "angle1: " << degrees(angle1) << "  angle2: " << degrees(angle2) << "\n\n";
    
    if (output==PovRay)
    {
        Triangle t1(endCap1.at(topIndex),endCap2.at(topIndex),endCap2.at(unitIndex1));
        Triangle t2(endCap1.at(unitIndex1),endCap2.at(unitIndex1),endCap1.at(topIndex));
        Triangle t3(endCap1.at(topIndex),endCap2.at(topIndex),endCap2.at(unitIndex2));
        Triangle t4(endCap1.at(unitIndex2),endCap2.at(unitIndex2),endCap1.at(topIndex));
        std::cout << povRayTriangle(t1, color) << "\n";
        std::cout << povRayTriangle(t2, color) << "\n";
        std::cout << povRayTriangle(t3, color) << "\n";
        std::cout << povRayTriangle(t4, color) << "\n";
    }
    
    if (output==UnitInfo)
    {
        double unitLength=Point::distance(endCap1.at(topIndex), endCap2.at(topIndex));
        double unitWidth=Point::distance(finalSection.at(topIndex), finalSection.at(unitIndex1));
        double dimensions=unitLength/(4.0*unitWidth);
        double paperLength=0.25*tan(M_PI/2.0-angle1);
        double cylinderDiameter=compound->computeWidth();
        dimensions+=paperLength;
        std::cout << 1.0/dimensions << " " << unitWidth*4.0/unitLength << " " << paperLength << " " << degrees(angle1) << " " << degrees(angle2) << " " << cylinderDiameter << "\n";
        //std::cout << (unitWidth*4.0)/unitLength;
        std::cout << "------------------------\n";
        return;
    }
}

void polypolyhedron(const Compound* compound, const std::vector<std::string>& colors,bool symmetrize,int v1,int v2,int v3,PolypolyOutput output)
{
    int frameNum=compound->getNumberOfPolyhedra();
    int edgeNum=compound->getPolyhedron(0)->getEdgeNum();
    for (int i=0;i<frameNum;i++)
    {
        for (int j=0;j<edgeNum;j++)
        {
            polypolyhedronUnit(compound,j,i,colors.at(i),symmetrize,v1,v2,v3,output);
        }
    }
    //pph5hextet2(0,0,"Blue",0.748726);
}

void polypolyhedraCode()
{
    std::vector<std::string> colors1={"Blue","Green","Red","Yellow","Orange","Violet","Cyan","Magenta","Black","Brown","CadetBlue","Aquamarine","Gray","MediumVioletRed","BlueViolet"};
    std::vector<std::string> colors2={"Yellow","Green","Blue","Red","Violet","MediumVioletRed","CadetBlue","Orange","CornflowerBlue","DarkGreen","Cyan","Magenta","Aquamarine","BlueViolet","Brown"};
    std::vector<std::string> colors3={"MediumVioletRed","CadetBlue","Coral","CornflowerBlue","DarkGreen","Blue","Gray","Black","Magenta","Green","Red","Yellow","Cyan","Brown","Orange"};
    
    //Tetrahedron td(0,0,0);
    //FiveCompound compound(td);
    //polypolyhedron(&compound,colors3,true,1,5,3,PovRay);
    
    //RhombicHexahedron td(0,0,0);
    //td.setAttribute("crimp", 0.3);
    //FiveCompound compound(td);
    //polypolyhedron(&compound,colors3,true,1,5,3,PovRay);
    
    //RhombicPentahedron td(0,0,0);
    //td.setAttribute("crimp", 0.514849);
    //SixCompound compound(td);
    //polypolyhedron(&compound,colors3,true,0,6,4,PovRay);
    
    //RhombicPentahedron td(0,0,0);
    //td.setAttribute("crimp", 0.420692);
    //SixCompound compound(td);
    //polypolyhedron(&compound,colors3,true,0,6,4,PovRay);
    
    //Pentagon td(0,0,0);
    //SixCompound compound(td);
    //polypolyhedron(&compound,colors3,true,0,3,2,PovRay);
    
    //HexagonalTetrahedron td(0,0,0);
    //td.setAttribute("crimp", 0.464);
    //FiveCompound compound(td);
    //polypolyhedron(&compound,colors3,true,0,5,4,PovRay);
    
    HexagonalTetrahedron td(0,0,0);
    td.setAttribute("crimp", 0.374);
    FiveCompound compound(td);
    polypolyhedron(&compound,colors3,true,0,4,2,PovRay);
    
    //RhombicTrihedron td(0,0,0);
    //td.setAttribute("crimp",0.425905);
    //TenCompound compound(td);
    //polypolyhedron(&compound,colors3,true,0,6,4,PovRay);
    
    //RhombicTrihedron td(0,0,0);
    //td.setAttribute("crimp",0.307);
    //FourCompound compound(td);
    //polypolyhedron(&compound,colors3,true,1,5,3,PovRay);
    
    //std::cout << "-----------------\n";
    //polypolyhedronUnit(&compound,0,0,"Black",true,0,4,2,CrossSection2D);
}

//
//  Polypolyhedra.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/24/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include <vector>
#include <array>
#include <cmath>

#include "Polypolyhedra.h"
#include "PPHAlgorithms.h"
#include "HexagonalTetrahedron.h"
#include "RhombicPentahedron.h"
#include "Pentagon.h"
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

void pph5hextet(int edge,int frame,const std::string& color,double attribute)
{
    //HexagonalTetrahedron td(0,0,0);
    //td.setAttribute("crimp", attribute);
    //FiveCompound compound(td);
     
     //instantiate the polypolyhedron--currently the code only works for pph's with both 2 and 3 valent vertices
     RhombicPentahedron td(0,0,0);
     //Pentagon td(0,0,0);
     td.setAttribute("crimp", attribute);
     SixCompound compound(td);
     //FourCompound compound(td);
     //compound.printPovRaySkeleton(0.04, {"Green"});
     
    int edgeID=edge;
    
    const Polyhedron* ref=compound.getPolyhedron(frame);
    Line refEdge=ref->getEdgeLine(edgeID);
    std::pair<int, int> endpoints=ref->getEdgeEndpoints(edgeID);
    std::vector<int> end1Edges=ref->getEdgesAroundVertex(endpoints.first);
    std::vector<int> end2Edges=ref->getEdgesAroundVertex(endpoints.second);
    std::vector<int> divalentEdges;
    std::vector<int> otherEdges;
    
     int divalentVertex=-1;
     int otherVertex=-1;
    if (end1Edges.size()==2)
    {
        divalentVertex=endpoints.first;
         otherVertex=endpoints.second;
        divalentEdges=end1Edges;
        otherEdges=end2Edges;
    }
    if (end2Edges.size()==2)
    {
        divalentVertex=endpoints.second;
         otherVertex=endpoints.first;
        divalentEdges=end2Edges;
        otherEdges=end1Edges;
    }
    divalentEdges.erase(std::remove(divalentEdges.begin(),divalentEdges.end(),edgeID),divalentEdges.end());
    otherEdges.erase(std::remove(otherEdges.begin(),otherEdges.end(),edgeID),otherEdges.end());
    
    std::vector<int> divalentAdjacent=ref->getVerticesAroundVertex(divalentVertex);
    
    //Line e1=ref->getEdgeLine(otherEdges.at(0));
    //Line e2=ref->getEdgeLine(otherEdges.at(1));
    //Line e1=ref->getEdgeLine(1); //trivalent
    //Line e2=ref->getEdgeLine(2); //trivalent
    //Line e3=ref->getEdgeLine(3); //divalent
    Line e3=ref->getEdgeLine(divalentEdges.at(0));
    Vector zaxis=refEdge.getVector();
    
    Point midpoint=refEdge.getMidpoint();
    
    Point symmetry1=ref->getVertex(divalentVertex);
    Point symmetry2=ref->getVertex(divalentAdjacent.at(0));
    Point symmetry3=ref->getVertex(divalentAdjacent.at(1));
    Plane symmetryPlane=Plane::planeThroughPoints(symmetry1, symmetry2, symmetry3);
    Vector xaxis=symmetryPlane.getNormalVector();
    
    Vector yaxis=Vector::cross(xaxis, zaxis);
    Vector midpointVector(Point(0,0,0),midpoint);
    yaxis*=Vector::dot(yaxis,midpointVector); //keep yaxis pointing outwards
    xaxis*=Vector::dot(yaxis,midpointVector);
    
    xaxis.normalize();
    yaxis.normalize();
    zaxis.normalize();
    
//    std::cout << refEdge.getDistance() << "\n";
//    std::cout << "refEdge\n";
//    std::cout << refEdge.toString() << "\n";
//
//    std::cout << "e1\n";
//    std::cout << e1.toString();
//    std::cout << "\n";
//    
//    std::cout << "e2\n";
//    std::cout << e2.toString();
//    std::cout << "\n";
//    
//    std::cout << "e3\n";
//    std::cout << e3.toString();
//    std::cout << "\n";
//
//    std::cout << "midpoint\n";
//    std::cout << midpoint.toString();
//    std::cout << "\n";
//    
//    std::cout << "zaxis endpoint\n";
//    std::cout << (midpoint+zaxis).toString();
//    std::cout << "\n";
//    
//    std::cout << "xaxis endpoint\n";
//    std::cout << (midpoint+xaxis).toString();
//    std::cout << "\n";
//    
//    std::cout << "yaxis endpoint\n";
//    std::cout << (midpoint+yaxis).toString();
//    std::cout << "\n";
    
    
    Matrix3x3 changeOfBasisMatrix=Matrix3x3(xaxis.getX(), yaxis.getX(), zaxis.getX(),
                                            xaxis.getY(), yaxis.getY(), zaxis.getY(),
                                            xaxis.getZ(), yaxis.getZ(), zaxis.getZ());
    Matrix3x3 inverse=changeOfBasisMatrix.inverse();
    Plane z0=planeThroughPointPerpendicularToLine(midpoint, refEdge);
//    std::cout << "\nplane perpendicular to refEdge\n" << z0.toString() << "\n\n";
    
    Point zero(0,0,0);
    Line zeroLine(zero,zero);
    
    std::vector<Line> crossSection;
    std::vector<Line2D> crossSection2D;
    bool symmetrize=true;
    double compoundCylinder=compound.computeWidth();
    for (int i=0;i<compound.getNumberOfPolyhedra();i++)
    {
        if (i==frame) {continue;}
        const Polyhedron* poly=compound.getPolyhedron(i);
        for (int j=0;j<poly->getEdgeNum();j++)
        {
            Line edge=poly->getEdgeLine(j);
            Line closeApproach=lineOfClosestApproach(edge, refEdge);
            if (closeApproach==zeroLine) {continue;}
            //if (closeApproach.getDistance()>0.9) {continue;}
            
            Point mid=closeApproach.getMidpoint();
            Plane thePlane=planeThroughPointPerpendicularToLine(mid, closeApproach);
            //thePlane.printInfo();
            Line intersection=planePlaneIntersection(z0, thePlane);
            
            if (intersection==zeroLine) {continue;}
            
            Point v1=intersection.getPointA()-midpoint;
            Point v2=intersection.getPointB()-midpoint;
            //std::cout << thePlane.toString() << " " << i << " " << j << "\n\n";
            Point basis1=vectorInBasis(inverse, v1);
            Point basis2=vectorInBasis(inverse, v2);
            Line basisLine=Line(basis1,basis2);

             //std::cout << basisLine.toString() << "\n";
            Line2D basisLine2d=lineToLine2D(basisLine);
             if (closeApproach.getDistance()<compoundCylinder)
             {
                  std::cout << "Error: cross section line is closer than cylinder radius. oa most likely too large\n";
                  double closeDist=segmentSegmentDist(edge, refEdge);
                  std::string different=(fabs(closeDist-closeApproach.getDistance())>EPS)?"???":"";
                  std::cout << i << " " << j << " ";
                  std::cout << lineOfClosestApproach(edge, refEdge,true).getDistance() << " ";
                  std::cout << closeDist << " ";
                  std::cout << different << " ";
                  std::cout << basisLine2d.toString() << "\n\n";
             }
//             if (closeApproach.getDistance()<0.05)
//             {
//                  double closeDist=segmentSegmentDist(edge, refEdge);
//                  std::string different=(fabs(closeDist-closeApproach.getDistance())>EPS)?"???":"";
//                  std::cout << i << " " << j << " ";
//                  std::cout << lineOfClosestApproach(edge, refEdge,true).getDistance() << " ";
//                  std::cout << closeDist << " ";
//                  std::cout << different << " ";
//                  std::cout << basisLine2d.toString() << "\n\n";
//             }
             //std::cout << basisLine2d.toString() << "\n";
            crossSection2D.push_back(lineToLine2D(basisLine));
            if (symmetrize)
            {
                double newm=-1*basisLine2d.getSlope();
                double newb=basisLine2d.getYIntercept();
                Line2D reflect(newm,newb);
                crossSection2D.push_back(reflect);
            }
            
            crossSection.push_back(basisLine);
   
            //std::cout << closeApproach.getDistance() << "\n";
            //std::cout << i << " " << j << "\n\n";
        }
    }

    //make list of all possible cross section points
    //these are the intersections of the cross section lines in 2d
    std::vector<Point> possibleCrossSections;
    int linesSize=(int) crossSection2D.size();
    for (int i=0;i<linesSize;i++)
    {
        for (int j=1;j<linesSize;j++)
        {
            Point intersection=Line2D::intersection(crossSection2D.at(i), crossSection2D.at(j));
            if (intersection.getZ()>=0.0)
            {
                possibleCrossSections.push_back(intersection);
            }
        }
    }
//     std::cout << "possible cross section points: \n";
//     for (int i=0;i<possibleCrossSections.size();i++)
//     {
//          std::cout << possibleCrossSections.at(i).toString() << "\n";
//     }
//     std::cout << "\n";
    
    //make a vector of the points which satisfy all inequalities
    std::vector<Point> realCrossSectionPoints;
    int pointSize=(int) possibleCrossSections.size();
    for (int i=0;i<pointSize;i++)
    {
        bool satisfy=true;
        Point check=possibleCrossSections.at(i);
        for (int j=0;j<linesSize;j++)
        {
            Line2D lineCheck=crossSection2D.at(j);
            double yintercept=lineCheck.getYIntercept();
            if (yintercept>0)
            {
                satisfy=lineCheck.isPointBelowOrOnLine(check);
            }
            else
            {
                satisfy=lineCheck.isPointAboveOrOnLine(check);
            }
            if (!satisfy)
            {
                break;
            }
        }
        if (satisfy)
        {
            realCrossSectionPoints.push_back(check);
        }
    }
    
    //remove any duplicates from this vector of points
    std::sort(realCrossSectionPoints.begin(), realCrossSectionPoints.end(),isPointSmaller);
    realCrossSectionPoints.erase(std::unique(realCrossSectionPoints.begin(), realCrossSectionPoints.end(),arePointsVirtuallyEqual),realCrossSectionPoints.end());
    std::sort(realCrossSectionPoints.begin(), realCrossSectionPoints.end(),isPointAngleSmaller);
    
//    std::cout << "real cross section points: \n";
//    for (int i=0;i<realCrossSectionPoints.size();i++)
//    {
//        std::cout << realCrossSectionPoints.at(i).toString() << "\n";
//    }
//    std::cout << "\n";
    
    //use the finalSection loops only if symmetrize=true
    std::vector<Point> finalSection;
    //find top and bottom cross section points
    Point crossSectionRef(0,0,0);
    for (int i=0;i<realCrossSectionPoints.size();i++)
    {
        Point check=realCrossSectionPoints.at(i);
        if (fabs(check.getX())<EPS)
        {
            finalSection.push_back(check);
            if (check.getY()>0)
            {
                crossSectionRef=check;
            }
        }
    }
    //pick which two points to use in cross section
    double maxDist=0.0;
    Point best(0,0,0);
    bool canSelectBottom=false;
    for (int i=0;i<realCrossSectionPoints.size();i++)
    {
        Point check=realCrossSectionPoints.at(i);
        if (!canSelectBottom)
        {
            if (fabs(atan2(check.getY(), check.getX())+M_PI/2.0)<EPS)
            {
                continue;
            }
        }
         if (fabs(check.getY())>0.01)
         {
              continue;
         }
        double newDist=Point::distance(crossSectionRef, check);
        if (newDist>maxDist /*&& newDist>0.01*/)
        {
            best=check;
            maxDist=newDist;
        }
    }
    finalSection.push_back(best);
    Point otherBest=best;
    otherBest.setX(best.getX()*-1);
    finalSection.push_back(otherBest);
    std::sort(finalSection.begin(), finalSection.end(), isPointAngleSmaller);
    
    //find which point is at the top of the cross section
     finalSection.erase(std::unique(finalSection.begin(), finalSection.end(),arePointsVirtuallyEqual),finalSection.end());
     int topIndex=0;
     for (int i=0;i<finalSection.size();i++)
     {
          if ( fabs(standardAngle(finalSection.at(i))-M_PI/2.0) < EPS)
          {
               topIndex=i;
          }
     }

//    std::cout << "final cross section points: \n";
//    for (int i=0;i<finalSection.size();i++)
//    {
//        std::cout << finalSection.at(i).toString() << "\n";
//    }
//    std::cout << "\n";
    
    //customize for each polypoly
    std::vector<Point> crossSectionPoints2D;
    crossSectionPoints2D=finalSection;
    /*crossSectionPoints2D.push_back(Point(0.0872,-0.0914,0));
    crossSectionPoints2D.push_back(Point(0.0,-0.0999,0));
    crossSectionPoints2D.push_back(Point(-0.0872,-0.0914,0));
    crossSectionPoints2D.push_back(Point(0,0.1406,0));*/
    
//    std::cout << "\ncross section points in 2d:\n";
//    for (int i=0;i<crossSectionPoints2D.size();i++)
//    {
//        std::cout << crossSectionPoints2D.at(i).toString() << "\n";
//    }
    
    
//    std::cout << "cross section points in 3d:\n";
    std::vector<Point> crossSectionPoints;
    for (int i=0;i<crossSectionPoints2D.size();i++)
    {
        Point ppp=crossSectionPoints2D[i];
        Point csp=vectorInBasis(changeOfBasisMatrix, ppp)+midpoint;
        crossSectionPoints.push_back(csp);
//        std::cout << csp.toString();
//        std::cout << "\n";
    }
    
//    std::cout << "\ncross section lengths:\n";
    for (int i=0;i<crossSectionPoints.size();i++)
    {
        Line lll;
        if (i<crossSectionPoints.size()-1)
        {
            lll=Line(crossSectionPoints[i],crossSectionPoints[i+1]);
        }
        else
        {
            lll=Line(crossSectionPoints[i],crossSectionPoints[0]);
        }
        //lll.printInfo();
//        std::cout << lll.getDistance() << "\n";
    }

//    std::cout << "\ncross section lines:\n";
    std::vector<Line> crossSectionLines(crossSectionPoints.size());
    for (int i=0;i<crossSectionPoints.size();i++)
    {
        Line crossSectionLine=lineThroughPointParallelToLine(crossSectionPoints[i], refEdge);
//        std::cout << crossSectionLine.toString() << "\n";
        crossSectionLines.at(i)=crossSectionLine;
//        std::cout << "\n";
    }
    
    //find bounding plane for divalent vertex
     Vector refEdgeVector=refEdge.getVector();
     Vector e3Vector=e3.getVector();
     Point planePoint=ref->getVertex(divalentVertex);//refEdge.getPointB();
     if (!(Point::almostEqual(refEdge.getPointA(), planePoint)))
     {
          refEdgeVector*=-1;
     }
     if (!(Point::almostEqual(e3.getPointA(), planePoint)))
     {
          e3Vector*=-1;
     }
    Vector planeVector1=Vector::angleBisector(refEdgeVector, e3Vector);
    Vector planeVector2=Vector::cross(refEdgeVector, e3Vector);
    Vector perpendicularPlaneVector=Vector::cross(planeVector1, planeVector2);
    Line planeLine(planePoint,planePoint+perpendicularPlaneVector);
    Plane p1=planeThroughPointPerpendicularToLine(planePoint, planeLine);
//    std::cout << "bounding plane\n";
//    std::cout << p1.toString() << "\n";
//    std::cout << "\n";
    
    std::vector<Point> endCap1(crossSectionLines.size());
//    std::cout << "endcap1 lines\n";
    for (int i=0;i<crossSectionLines.size();i++)
    {
        Point intersect=planeLineIntersection(crossSectionLines.at(i),p1);
        endCap1.at(i)=intersect;
//        std::cout << Line(intersect,crossSectionPoints.at(i)).toString() << "\n\n";
    }
    
//    std::cout << "endcap1 points\n";
//    for (int i=0;i<endCap1.size();i++)
//    {
//        std::cout << endCap1.at(i).toString() << "\n";
//    }
//    std::cout << "\n";
    
    Point origin(0,0,0);
    //Plane p2=Plane::planeThroughPoints(origin, e1.getPointA(), e1.getPointB());
    //Plane p3=Plane::planeThroughPoints(origin, e2.getPointA(), e2.getPointB());
     std::vector<Vector> otherEdgeVectors(otherEdges.size());
     for (int i=0;i<otherEdges.size();i++)
     {
          Line oe=ref->getEdgeLine(otherEdges.at(i));
          Point oeEnd=oe.getPointA();
          if (Point::almostEqual(oeEnd, ref->getVertex(otherVertex)))
          {
               otherEdgeVectors.at(i)=oe.getVector();
          }
          else
          {
               otherEdgeVectors.at(i)=oe.getVector()*-1;
          }
     }
     
     std::vector<Plane> endCapPlanes;
     for (int i=0;i<otherEdges.size();i++)
     {
          //Line otherEdge=ref->getEdgeLine(otherEdges.at(i));
          Vector reVector=refEdge.getVector();
          if (!(Point::almostEqual(refEdge.getPointA(), ref->getVertex(otherVertex))))
          {
               reVector*=-1;
          }
          //Vector oeVector=otherEdge.getVector();
          Vector oeVector=otherEdgeVectors.at(i);
          Vector planeVector1=Vector::cross(reVector, oeVector);
          Vector planeVector2=Vector::angleBisector(reVector, oeVector);
          Point planeVertex1=ref->getVertex(otherVertex);
          Point planeVertex2=planeVertex1+planeVector1;
          Point planeVertex3=planeVertex1+planeVector2;
          //std::cout << planeVertex2.toString() << "\n";
          //std::cout << planeVertex3.toString() << "\n";
          
          endCapPlanes.push_back(Plane::planeThroughPoints(planeVertex1, planeVertex2, planeVertex3));
     }
     
    //std::cout << p2.toString() << "\n";
    //std::cout << p3.toString() << "\n";
//     for (int i=0;i<endCapPlanes.size();i++)
//     {
//          Line otherEdge=ref->getEdgeLine(otherEdges.at(i));
//          std::cout << endCapPlanes.at(i).toString() << "\n";
//          std::cout << otherEdge.toString() << "\n";
//     }

    std::vector<Point> endCap2(endCap1.size());
    //customize for each polypoly
    for (int i=0;i<endCap2.size();i++)
    {
         Point endCapPoint(0,0,0);
         double dist=100000.0;
         for (int j=0;j<endCapPlanes.size();j++)
         {
              Point testPoint=planeLineIntersection(crossSectionLines[i],endCapPlanes.at(j));
              double testDist=Point::distance(testPoint, midpoint);
              if (testDist<dist)
              {
                   endCapPoint=testPoint;
                   dist=testDist;
              }
         }
         endCap2.at(i)=endCapPoint;
    }
    
    std::vector<Line> stickEdges(endCap2.size());
//    std::cout << "stick edges\n";
    for (int i=0;i<endCap2.size();i++)
    {
        Line stick1=Line(endCap2.at(i),endCap1.at(i));
        stickEdges.at(i)=stick1;
//        std::cout << stick1.toString() << "\n\n";
    }
    
//    std::cout << "endcap2 points\n";
//    for (int i=0;i<endCap1.size();i++)
//    {
//        std::cout << endCap2.at(i).toString() << "\n";
//    }
//    std::cout << "\n\n";
//
//    std::cout << "stick length -- " << stickEdges.at(topIndex).getDistance() << "\n";
    
    int unitIndex1=(int) (topIndex+endCap2.size()-1)%endCap2.size();
    int unitIndex2=(int) (topIndex+1)%endCap2.size();
    double angle1=Point::angleMeasure(endCap1.at(topIndex), endCap2.at(topIndex), endCap2.at(unitIndex1));
    double angle2=Point::angleMeasure(endCap2.at(topIndex), endCap1.at(topIndex), endCap1.at(unitIndex1));
    
//    std::cout << "angle1: " << degrees(angle1) << "  angle2: " << degrees(angle2) << "\n\n";
    
    Triangle t1(endCap1.at(topIndex),endCap2.at(topIndex),endCap2.at(unitIndex1));
    Triangle t2(endCap1.at(unitIndex1),endCap2.at(unitIndex1),endCap1.at(topIndex));
    Triangle t3(endCap1.at(topIndex),endCap2.at(topIndex),endCap2.at(unitIndex2));
    Triangle t4(endCap1.at(unitIndex2),endCap2.at(unitIndex2),endCap1.at(topIndex));
    std::cout << povRayTriangle(t1, color) << "\n";
    std::cout << povRayTriangle(t2, color) << "\n";
    std::cout << povRayTriangle(t3, color) << "\n";
    std::cout << povRayTriangle(t4, color) << "\n";
    double unitLength=Point::distance(endCap1.at(topIndex), endCap2.at(topIndex));
    double unitWidth=Point::distance(finalSection.at(topIndex), finalSection.at(unitIndex1));
    double dimensions=unitLength/(4.0*unitWidth);
    double paperLength=0.25*tan(M_PI/2.0-angle1);
     double cylinderDiameter=compound.computeWidth();
    dimensions+=paperLength;
    std::cout << 1.0/dimensions << " " << unitWidth*4.0/unitLength << " " << paperLength << " " << degrees(angle1) << " " << degrees(angle2) << " " << cylinderDiameter;
    //std::cout << (unitWidth*4.0)/unitLength;
    
}
void pph5hextet(const std::vector<std::string>& colors)
{
    //5 hexagonal tetrahedra
    //0.3441,0.645
    //0.4005, 1:sqrt(2) paper x=0.75,h=0.5
    //0.378977 0.724577 0.802478 0.133975 75
     
    //0.374 0.736635 0.80982 0.122683 76.214 38.9059
    //3:4 paper, 75 degree x=1,h=0.5 37.761 x=0.5,y=0.625
    
    //pph5hextet(0,0,"Green",0.3441);
    /*for (int i=0;i<5;i++)
    {
        for (int j=0;j<12;j++)
        {
            pph5hextet(j,i,colors.at(i),0.464);
        }
    }*/
    /*for (double i=0.1;i<=0.5;i+=0.001)
    {
        std::cout << i << " ";
        pph5hextet(0,0,"Green",i);
        std::cout << "\n";
    }*/
     //pph5hextet(8, 3, "Green", 0.374);
     //pph5hextet(11, 2, "Blue", 0.374);
     
     
     
     
     //4 rhombic trihedra
     //0.307, x=0.875,y=0.5 x=0.5,y=0.75
     //0.747142
     
     //10 rhombic trihedra -- 0.425905,0.851333
     
     //6 rhombic pentahedra 0.723646, 1:4 30 degrees,y=0.75,h=0.5625
     
     //pph5hextet(0,0,"Blue",0.748726);
     /*for (double i=0.0;i<=1.0;i+=0.001)
     {
          std::cout << i << " ";
          pph5hextet(0,0,"Green",i);
          std::cout << "\n";
     }*/
     //pph5hextet(0,0,"Blue",0.514849); //1.5:11 angle 55.6 x=0.75 k=0.5 26.0 x=0.5 k=1.0
     for (int i=0;i<6;i++)
     {
          for (int j=0;j<10;j++)
          {
               int colorIndex=i%colors.size();
               pph5hextet(j,i,colors.at(colorIndex),0.514849);
          }
     }
     
     //6 pentagons
     /*for (int i=0;i<6;i++)
     {
          for (int j=0;j<5;j++)
          {
               int colorIndex=i%colors.size();
               pph5hextet(j,i,colors.at(colorIndex),0.514849);
          }
     }*/
     //pph5hextet(0,0,"Blue",0.748726);
}
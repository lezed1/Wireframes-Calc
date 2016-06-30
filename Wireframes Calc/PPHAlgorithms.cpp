//
//  PPHAlgorithms.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/24/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>
#include <vector>

#include "PPHAlgorithms.h"
#include "basicshapes.h"
#include "Matrix3x3.h"
#include "Utilities.h"

#define EPS 0.000001

Matrix3x3 generateTargetEdgeBasis(int edge,const Polyhedron* ref)
{
    Line refEdge=ref->getEdgeLine(edge);
    std::pair<int, int> endpoints=ref->getEdgeEndpoints(edge);
    
    //identify a divalent edge if there is one
    int divalentVertex=-1;
    
    if (ref->getVertexValency(endpoints.first)==2)
    {
        divalentVertex=endpoints.first;
    }
    if (ref->getVertexValency(endpoints.second)==2)
    {
        divalentVertex=endpoints.second;
    }
    
    //construct orthonormal basis around the target edge
    Vector zaxis=refEdge.getVector();
    Point midpoint=refEdge.getMidpoint();
    
    Vector xaxis;
    if (divalentVertex!=-1) //calaculate x-axis if there is a divalent vertex
    {
        std::vector<int> divalentAdjacent=ref->getVerticesAroundVertex(divalentVertex);
        Point symmetry1=ref->getVertex(divalentVertex);
        Point symmetry2=ref->getVertex(divalentAdjacent.at(0));
        Point symmetry3=ref->getVertex(divalentAdjacent.at(1));
        Plane symmetryPlane=Plane::planeThroughPoints(symmetry1, symmetry2, symmetry3);
        xaxis=symmetryPlane.getNormalVector();
    }
    else //calculate x-axis is there is NOT a divalent vertex (it must be trivalent)
    {
        std::vector<int> endpoint1AdjacentEdges=ref->getEdgesAroundEdge(edge, 1); //same endpoint as refEdge.getPointA()
        if (endpoint1AdjacentEdges.size()!=2) //vertex is not at least trivalent for some reason
        {
            std::cout << "Error: generateTargetEdgeBasis--endpoint1AdjacentEdges does not have 2 entries\n";
            xaxis=Vector(0, 0, 0);
        }
        else
        {
            Line v1Edge=ref->getEdgeLine(endpoint1AdjacentEdges.at(0));
            Vector v1=v1Edge.getVector();
            Point v1EdgeEnd=v1Edge.getPointA();
            if (!Point::almostEqual(v1EdgeEnd, refEdge.getPointA())) //make sure v1 points away from refEdge
            {
                v1*=-1.0;
            }
            Line v2Edge=ref->getEdgeLine(endpoint1AdjacentEdges.at(1));
            Vector v2=v2Edge.getVector();
            Point v2EdgeEnd=v2Edge.getPointA();
            if (!Point::almostEqual(v2EdgeEnd, refEdge.getPointA())) //make sure v2 points away from refEdge
            {
                v2*=-1.0;
            }
            
            Vector planeVector1=Vector::angleBisector(v1,v2);
            Vector planeVector2=Vector::cross(v1,v2);
            
            Point symmetry1=refEdge.getPointA();
            Point symmetry2=symmetry1+planeVector1;
            Point symmetry3=symmetry1+planeVector2;
            Plane symmetryPlane=Plane::planeThroughPoints(symmetry1, symmetry2, symmetry3);
            
            xaxis=symmetryPlane.getNormalVector();
            
            /*std::cout << refEdge.toString() << "\n\n";
            std::cout << v1Edge.toString() << "\n\n";
            std::cout << v2Edge.toString() << "\n\n";
            std::cout << v1.toString() << "\n";
            std::cout << v2.toString() << "\n\n";
            std::cout << symmetry3.toString() << "\n";
            std::cout << symmetryPlane.toString() << "\n";
            std::cout << "-----------------------------\n";*/
        }
        
    }
    
    Vector yaxis=Vector::cross(xaxis, zaxis);
    Vector midpointVector(Point(0,0,0),midpoint);
    yaxis*=Vector::dot(yaxis,midpointVector); //keep yaxis pointing outwards
    xaxis*=Vector::dot(yaxis,midpointVector);
    
    xaxis.normalize();
    yaxis.normalize();
    zaxis.normalize();
    
    /*std::cout << refEdge.toString() << "\n\n";
    std::cout << midpoint.toString() << "\n";
    std::cout << (midpoint+xaxis).toString() << "\n";
    std::cout << (midpoint+yaxis).toString() << "\n";
    std::cout << (midpoint+zaxis).toString() << "\n";
    std::cout << "-----------------------------\n";z*/
    
    //change of basis matrix from standard basis to new target edge basis
    Matrix3x3 polyBasisToStdBasis=Matrix3x3(xaxis.getX(), yaxis.getX(), zaxis.getX(),
                                            xaxis.getY(), yaxis.getY(), zaxis.getY(),
                                            xaxis.getZ(), yaxis.getZ(), zaxis.getZ());
    
    return polyBasisToStdBasis;
}

std::vector<Line2D> generateCrossSectionBounds(int edge,int frame,const Compound* compound,const Matrix3x3& polyBasisToStdBasis,bool symmetrize)
{
    Line refEdge=compound->getPolyhedron(frame)->getEdgeLine(edge);
    Point midpoint=refEdge.getMidpoint();
    Matrix3x3 stdBasisToPolyBasis=polyBasisToStdBasis.inverse();
    Plane z0=planeThroughPointPerpendicularToLine(midpoint, refEdge);
    
    Point zero(0,0,0);
    Line zeroLine(zero,zero);
    
    //make vectors containing cross section lines
    std::vector<Line2D> crossSection2D; //cross section lines expressed in poly basis (in 2D, z-component is ignored since the cross section is the same along the axis of the edge)
    double compoundCylinder=compound->computeWidth();
    
    for (int i=0;i<compound->getNumberOfPolyhedra();i++)
    {
        if (i==frame) {continue;}
        const Polyhedron* poly=compound->getPolyhedron(i);
        for (int j=0;j<poly->getEdgeNum();j++)
        {
            Line edge=poly->getEdgeLine(j);
            Line closeApproach=lineOfClosestApproach(edge, refEdge);
            if (closeApproach==zeroLine) {continue;} //REDO THIS: closest approach occurs outside the line segments + oa buffers
            
            Point mid=closeApproach.getMidpoint();
            Plane thePlane=planeThroughPointPerpendicularToLine(mid, closeApproach); //plane separating the two line segments
            Line intersection=planePlaneIntersection(z0, thePlane); //intersection of this plane with the xy-plane of the poly basis
            
            if (intersection==zeroLine) {continue;} //the two planes are parallel
            
            Point v1=intersection.getPointA()-midpoint;
            Point v2=intersection.getPointB()-midpoint;
            Point basis1=vectorInBasis(stdBasisToPolyBasis, v1);
            Point basis2=vectorInBasis(stdBasisToPolyBasis, v2);
            Line basisLine=Line(basis1,basis2); //find the intersection line in poly basis
            
            Line2D basisLine2d=lineToLine2D(basisLine); //intersection line in poly basis without z-component (z should be 0 anyway)
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
            
            crossSection2D.push_back(lineToLine2D(basisLine));
            if (symmetrize)
            {
                double newm=-1*basisLine2d.getSlope();
                double newb=basisLine2d.getYIntercept();
                Line2D reflect(newm,newb);
                crossSection2D.push_back(reflect);
            }
        }
    }
    return crossSection2D;
}

std::vector<Point> findInnerCrossSectionVertices(const std::vector<Line2D>& crossSection2D)
{
    //make list of all possible cross section points
    //these are the intersections of the cross section lines in 2d
    std::vector<Point> possibleCrossSections;
    int linesSize=(int) crossSection2D.size();
    for (int i=0;i<linesSize;i++)
    {
        for (int j=1;j<linesSize;j++)
        {
            Point intersection=Line2D::intersection(crossSection2D.at(i), crossSection2D.at(j));
            if (intersection.getZ()>=0.0) //z=-1.0 for no intersection
            {
                possibleCrossSections.push_back(intersection);
            }
        }
    }
    
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
    return realCrossSectionPoints;
}

std::vector<Point> generateCrossSection(int edge,int frame,const Compound* compound,const Matrix3x3& polyBasisToStdBasis,bool symmetrize)
{
    std::vector<Line2D> crossSection2D=generateCrossSectionBounds(edge, frame, compound, polyBasisToStdBasis, symmetrize);
    std::vector<Point> realCrossSectionPoints=findInnerCrossSectionVertices(crossSection2D);
    
    //remove any duplicates from this vector of points and sort
    std::sort(realCrossSectionPoints.begin(), realCrossSectionPoints.end(),isPointSmaller);
    realCrossSectionPoints.erase(std::unique(realCrossSectionPoints.begin(), realCrossSectionPoints.end(),arePointsVirtuallyEqual),realCrossSectionPoints.end());
    std::sort(realCrossSectionPoints.begin(), realCrossSectionPoints.end(),isPointAngleSmaller);
    
    return realCrossSectionPoints;
}

std::vector<Line> generateStickEdges(const std::vector<Point>& crossSectionPoints2D,const Matrix3x3& polyBasisToStdBasis,const Line& refEdge)
{
    //convert 2d cross section to 3d
    std::vector<Point> crossSectionPoints;
    for (int i=0;i<crossSectionPoints2D.size();i++)
    {
        Point ppp=crossSectionPoints2D.at(i);
        Point csp=vectorInBasis(polyBasisToStdBasis, ppp)+refEdge.getMidpoint();
        crossSectionPoints.push_back(csp);
    }
    
    //find lines parallel to the target edge through the cross section points in 3d
    //these will be the segments of the stick edges
    std::vector<Line> crossSectionLines(crossSectionPoints.size());
    for (int i=0;i<crossSectionPoints.size();i++)
    {
        Line crossSectionLine=lineThroughPointParallelToLine(crossSectionPoints.at(i), refEdge);
        crossSectionLines.at(i)=crossSectionLine;
    }
    
    return crossSectionLines;
}

std::vector<Point> generateEndCap(const Line& targetEdge,const Point& targetEndpoint, const std::vector<Line>& adjacentEdges, const std::vector<Line>& crossSectionLines)
{
    std::vector<Vector> adjacentEdgeVectors(adjacentEdges.size());
    for (int i=0;i<adjacentEdges.size();i++)
    {
        Line oe=adjacentEdges.at(i);
        Point oeEnd=oe.getPointA();
        if (Point::almostEqual(oeEnd, targetEndpoint))
        {
            adjacentEdgeVectors.at(i)=oe.getVector();
        }
        else
        {
            adjacentEdgeVectors.at(i)=oe.getVector()*-1;
        }
    }
    
    std::vector<Plane> endCapPlanes;
    for (int i=0;i<adjacentEdges.size();i++)
    {
        Vector reVector=targetEdge.getVector();
        if (!(Point::almostEqual(targetEdge.getPointA(), targetEndpoint)))
        {
            reVector*=-1;
        }

        Vector oeVector=adjacentEdgeVectors.at(i);
        Vector planeVector1=Vector::cross(reVector, oeVector);
        Vector planeVector2=Vector::angleBisector(reVector, oeVector);
        Point planeVertex1=targetEndpoint;
        Point planeVertex2=planeVertex1+planeVector1;
        Point planeVertex3=planeVertex1+planeVector2;
        
        endCapPlanes.push_back(Plane::planeThroughPoints(planeVertex1, planeVertex2, planeVertex3));
    }
    
    std::vector<Point> endCap(crossSectionLines.size());
    for (int i=0;i<endCap.size();i++)
    {
        Point endCapPoint(0,0,0);
        double dist=100000.0;
        for (int j=0;j<endCapPlanes.size();j++)
        {
            Point testPoint=planeLineIntersection(crossSectionLines.at(i),endCapPlanes.at(j));
            double testDist=Point::distance(testPoint, targetEdge.getMidpoint());
            if (testDist<dist)
            {
                endCapPoint=testPoint;
                dist=testDist;
            }
        }
        endCap.at(i)=endCapPoint;
    }
    
    return endCap;
}

Line lineOfClosestApproach(const Line& line1,const Line& line2,bool print)
{
    /*
     * Copyright 2001, softSurfer (www.softsurfer.com)
     * This code may be freely used and modified for any purpose
     * providing that this copyright notice is included with it.
     * SoftSurfer makes no warranty for this code, and cannot be held
     * liable for any real or imagined damage resulting from its use.
     * Users of this code must verify correctness for their application.
     */
    /*Point delta21;
     delta21.setX(line1.getPointB().getX()-line1.getPointA().getX());
     delta21.setY(line1.getPointB().getY()-line1.getPointA().getY());
     delta21.setZ(line1.getPointB().getZ()-line1.getPointA().getZ());
     
     Point delta41;
     delta41.setX(line2.getPointB().getX()-line2.getPointA().getX());
     delta41.setY(line2.getPointB().getY()-line2.getPointA().getY());
     delta41.setZ(line2.getPointB().getZ()-line2.getPointA().getZ());
     
     Point delta13;
     delta13.setX(line1.getPointA().getX()-line2.getPointA().getX());
     delta13.setY(line1.getPointA().getY()-line2.getPointA().getY());
     delta13.setZ(line1.getPointA().getZ()-line2.getPointA().getZ());*/
    
    Vector delta21=line1.getVector();
    Vector delta41=line2.getVector();
    Vector delta13(line2.getPointA(),line1.getPointA());
    
    double a=Vector::dot(delta21,delta21);
    double b=Vector::dot(delta21,delta41);
    double c=Vector::dot(delta41,delta41);
    double d=Vector::dot(delta21,delta13);
    double e=Vector::dot(delta41,delta13);
    double D = a*c - b*b;        // always >= 0
    double sc, tc;
    
    // compute the line parameters of the two closest points
    if (D < EPS) {          // the lines are almost parallel
        sc = 0.0;
        tc = (b>c ? d/b : e/c);    // use the largest denominator
    }
    else {
        sc = (b*e - c*d) / D;
        tc = (a*e - b*d) / D;
    }
    
    Point ca1=line1.getPointA()+delta21*sc;
    Point ca2=line2.getPointA()+delta41*tc;
    if (print) {std::cout << sc << " " << tc << "--\n";}
    
    double oa=0.06;
    if ((sc < -oa || sc > 1+oa) || (tc < -oa || tc > 1+oa))
    {
        //std::cout << "hi there";
        Point zero=Point(0,0,0);
        return Line(zero,zero);
    }
    
    return Line(ca1,ca2);
    
    // get the difference of the two closest points
    //Point dP = w + (sc * u) - (tc * v);  // =  L1(sc) - L2(tc)
}

//Line lineOfClosestApproach(const Line& line1,const Line& line2)
//{
//    // Copyright 2001 softSurfer, 2012 Dan Sunday
//    // This code may be freely used and modified for any purpose
//    // providing that this copyright notice is included with it.
//    // SoftSurfer makes no warranty for this code, and cannot be held
//    // liable for any real or imagined damage resulting from its use.
//    // Users of this code must verify correctness for their application.
//    Vector   u = line1.getVector();
//    Vector   v = line2.getVector();
//    Vector   w = Vector(line2.getPointA(),line1.getPointA());
//    double    a = Vector::dot(u,u);         // always >= 0
//    double    b = Vector::dot(u,v);
//    double    c = Vector::dot(v,v);         // always >= 0
//    double    d = Vector::dot(u,w);
//    double    e = Vector::dot(v,w);
//    double    D = a*c - b*b;        // always >= 0
//    double    sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
//    double    tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0
//    
//    // compute the line parameters of the two closest points
//    if (D < EPS)
//    { // the lines are almost parallel
//        sN = 0.0;         // force using point P0 on segment S1
//        sD = 1.0;         // to prevent possible division by 0.0 later
//        tN = e;
//        tD = c;
//    }
//    else
//    {                 // get the closest points on the infinite lines
//        sN = (b*e - c*d);
//        tN = (a*e - b*d);
//        if (sN < 0.0)
//        {        // sc < 0 => the s=0 edge is visible
//            sN = 0.0;
//            tN = e;
//            tD = c;
//        }
//        else if (sN > sD)
//        {  // sc > 1  => the s=1 edge is visible
//            sN = sD;
//            tN = e + b;
//            tD = c;
//        }
//    }
//    
//    if (tN < 0.0)
//    {            // tc < 0 => the t=0 edge is visible
//        tN = 0.0;
//        // recompute sc for this edge
//        if (-d < 0.0)
//        {
//            sN = 0.0;
//        }
//        else if (-d > a)
//        {
//            sN = sD;
//        }
//        else
//        {
//            sN = -d;
//            sD = a;
//        }
//    }
//    else if (tN > tD)
//    {      // tc > 1  => the t=1 edge is visible
//        tN = tD;
//        // recompute sc for this edge
//        if ((-d + b) < 0.0)
//        {
//            sN = 0;
//        }
//        else if ((-d + b) > a)
//        {
//            sN = sD;
//        }
//        else
//        {
//            sN = (-d +  b);
//            sD = a;
//        }
//    }
//    // finally do the division to get sc and tc
//    sc = (fabs(sN) < EPS ? 0.0 : sN / sD);
//    tc = (fabs(tN) < EPS ? 0.0 : tN / tD);
//    
//    Point ca1=line1.getPointA()+u*sc;
//    Point ca2=line2.getPointA()+v*tc;
//    
//    double oa=0.10;
//    if ((sc < -oa || sc > 1+oa) || (tc < -oa || tc > 1+oa))
//    {
//        Point zero=Point(0,0,0);
//        return Line(zero,zero);
//        //std::cout << "hi there";
//    }
//    
//    return Line(ca1,ca2);
//    
//    // get the difference of the two closest points
//    //Point dP = w + (sc * u) - (tc * v);  // =  L1(sc) - L2(tc)
//}

Plane planeThroughPointPerpendicularToLine(const Point& mid,const Line& line1)
{
    Point ca2=line1.getPointB();
    Point ca1=line1.getPointA();
    Point vectorN;
    vectorN.setX(ca2.getX()-ca1.getX());
    vectorN.setY(ca2.getY()-ca1.getY());
    vectorN.setZ(ca2.getZ()-ca1.getZ());
    
    double ddd=-1*(vectorN.getX()*mid.getX()+vectorN.getY()*mid.getY()+vectorN.getZ()*mid.getZ());
    
    Plane thePlane(vectorN.getX(),vectorN.getY(),vectorN.getZ(),ddd);
    
    return thePlane;
}

Line planePlaneIntersection(const Plane& p1,const Plane& p2)
{
    //Process: http://stackoverflow.com/a/17628505
    Vector normal1=Vector(p1.getA(),p1.getB(),p1.getC()); //vector normal to p1
    Vector normal2=Vector(p2.getA(),p2.getB(),p2.getC()); //vector normal to p2
    Vector cross=Vector::cross(normal1, normal2); //vector parallel to line of intersection
    
    if (fabs(cross.norm())<EPS)
    { //planes are parallel
        Point zero=Point(0,0,0);
        return Line(zero,zero);
    }
    double a1=p1.getA();
    double b1=p1.getB();
    double c1=p1.getC();
    double d1=-1*p1.getD();
    double a2=p2.getA();
    double b2=p2.getB();
    double c2=p2.getC();
    double d2=-1*p2.getD();
    double a3=cross.getX();
    double b3=cross.getY();
    double c3=cross.getZ();
    double d3=0;
    
    //solve with cramers rule
    Matrix3x3 denom(a1,b1,c1,
                    a2,b2,c2,
                    a3,b3,c3);
    Matrix3x3 xNum(d1,b1,c1,
                   d2,b2,c2,
                   d3,b3,c3);
    Matrix3x3 yNum(a1,d1,c1,
                   a2,d2,c2,
                   a3,d3,c3);
    Matrix3x3 zNum(a1,b1,d1,
                   a2,b2,d2,
                   a3,b3,d3);
    double denomDeterminant=denom.determinant();
    
    double xsolution=xNum.determinant()/denomDeterminant;
    double ysolution=yNum.determinant()/denomDeterminant;
    double zsolution=zNum.determinant()/denomDeterminant;
    
    Point onLine(xsolution,ysolution,zsolution);
    Point onLine2=onLine+cross;
    return Line(onLine,onLine2);
}

Point vectorInBasis(const Matrix3x3& basis,const Point& v)
{
    double p1=v.getX()*basis.getEntry(0, 0)+v.getY()*basis.getEntry(0, 1)+v.getZ()*basis.getEntry(0, 2);
    double p2=v.getX()*basis.getEntry(1, 0)+v.getY()*basis.getEntry(1, 1)+v.getZ()*basis.getEntry(1, 2);
    double p3=v.getX()*basis.getEntry(2, 0)+v.getY()*basis.getEntry(2, 1)+v.getZ()*basis.getEntry(2, 2);
    
    return Point(p1,p2,p3);
}

Line2D lineToLine2D(const Line& l)
{
    Point a=l.getPointA();
    Point b=l.getPointB();
    return Line2D(a,b);
    /*double aa=a.getX();
    double bb=a.getY();
    double cc=b.getX();
    double dd=b.getY();
    
    double slope=(bb-dd)/(aa-cc);
    double intercept=(aa*dd-bb*cc)/(aa-cc);
    
    std::cout << "y=" << slope << "x+" << intercept << "\n";*/
}

Line lineThroughPointParallelToLine(const Point& p,const Line& l)
{
    Point la=l.getPointA();
    Point lb=l.getPointB();
    Point lineVector=la-lb;
    
    //line is p+lineVector*t
    Point p2=p+lineVector;
    return Line(p,p2);
}

Point planeLineIntersection(const Line& line1,const Plane& p1)
{
    Vector normal(p1.getA(),p1.getB(),p1.getC());
    Vector u=line1.getVector();
    double si=-1*p1.valueAtPoint(line1.getPointA())/(Vector::dot(normal, u));
    
    return line1.getPointA()+u*si;
}

bool arePointsVirtuallyEqual(const Point& p1,const Point& p2)
{
    if (Point::distance(p1,p2)<EPS)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isPointSmaller(const Point& p1,const Point& p2)
{
    if (p1.getX()<p2.getX() && positiveDifference(p1.getX(), p2.getX())>=EPS) //p1_x<p2_x
    {
        return true;
    }
    else if (positiveDifference(p1.getX(), p2.getX())<EPS) //p1_x=p2_x
    {
        if (p1.getY()<p2.getY() && positiveDifference(p1.getY(), p2.getY())>=EPS) //p1_y<p2_y
        {
            return true;
        }
        else if (positiveDifference(p1.getY(), p2.getY())<EPS) //p1_y=p2_y
        {
            if (p1.getZ()<p2.getZ() && positiveDifference(p1.getY(), p2.getY())>=EPS) //p1_z<p2_z
            {
                return true;
            }
            else //p1_z>=p2_z
            {
                return false;
            }
        }
        else //p1_y>p2_y
        {
            return false;
        }
    }
    else //p1_y>p2_y
    {
        return false;
    }
}
double standardAngle(const Point& p)
{
    double angle=atan2(p.getY(), p.getX());
    if (positiveDifference(angle, M_PI)<EPS) //give angles on the negative x-axis a consistent value despite rounding errors (atan2 jumps from pi to -pi at the negative x-axis)
    {
        angle=-M_PI;
    }
    return angle;
}
bool isPointAngleSmaller(const Point& p1,const Point& p2)
{
    return standardAngle(p1) < standardAngle(p2);
}
bool arePointAnglesEqual(const Point& p1,const Point& p2)
{
    if (fabs(standardAngle(p1)-standardAngle(p2))<EPS)
    {
        return true;
    }
    return false;
}
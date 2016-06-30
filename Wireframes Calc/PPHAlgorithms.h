//
//  PPHAlgorithms.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/24/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__PPHAlgorithms__
#define __Wireframes_Calc_4_5__PPHAlgorithms__

#include "basicshapes.h"
#include "Matrix3x3.h"
#include "Polyhedron.h"
#include "Compound.h"
#include "Line2D.h"

Matrix3x3 generateTargetEdgeBasis(int edge,const Polyhedron* ref);
std::vector<Line2D> generateCrossSectionBounds(int edge,int frame,const Compound* compound,const Matrix3x3& polyBasisToStdBasis,bool symmetrize);
std::vector<Point> findInnerCrossSectionVertices(const std::vector<Line2D>& crossSection2D);
std::vector<Point> generateCrossSection(int edge,int frame,const Compound* compound,const Matrix3x3& polyBasisToStdBasis,bool symmetrize);
std::vector<Line> generateStickEdges(const std::vector<Point>& crossSectionPoints2D, const Matrix3x3& polyBasisToStdBasis, const Line& refEdge);
std::vector<Point> generateEndCap(const Line& targetEdge,const Point& targetEndpoint, const std::vector<Line>& adjacentEdges, const std::vector<Line>& crossSectionLines);

Line lineOfClosestApproach(const Line& line1,const Line& line2,bool print=false);
Plane planeThroughPointPerpendicularToLine(const Point& mid,const Line& line1);
Line planePlaneIntersection(const Plane& p1,const Plane& p2);
Point vectorInBasis(const Matrix3x3& basis, const Point& v);
Line2D lineToLine2D(const Line& l);
Line lineThroughPointParallelToLine(const Point& p,const Line& l);
Point planeLineIntersection(const Line& line1,const Plane& p1);
bool arePointsVirtuallyEqual(const Point& p1,const Point& p2);
bool isPointSmaller(const Point& p1,const Point& p2);
double standardAngle(const Point& p);
bool isPointAngleSmaller(const Point& p1,const Point& p2);

#endif /* defined(__Wireframes_Calc_4_5__PPHAlgorithms__) */

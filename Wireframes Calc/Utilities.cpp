//
//  Utilities.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 11/23/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>

#include "Utilities.h"
#include "basicshapes.h"

#define SMALL_NUM 0.00000001

std::string doubleToString(double d)
{
    return std::to_string(d);
}
std::string intToString(int i)
{
    return std::to_string(i);
}
double segmentSegmentDist(const Line& line1,const Line& line2)
{
    // Copyright 2001 softSurfer, 2012 Dan Sunday
    // This code may be freely used and modified for any purpose
    // providing that this copyright notice is included with it.
    // SoftSurfer makes no warranty for this code, and cannot be held
    // liable for any real or imagined damage resulting from its use.
    // Users of this code must verify correctness for their application.
    Vector   u = line1.getVector();
    Vector   v = line2.getVector();
    Vector   w = Vector(line2.getPointA(),line1.getPointA());
    double    a = Vector::dot(u,u);         // always >= 0
    double    b = Vector::dot(u,v);
    double    c = Vector::dot(v,v);         // always >= 0
    double    d = Vector::dot(u,w);
    double    e = Vector::dot(v,w);
    double    D = a*c - b*b;        // always >= 0
    double    sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
    double    tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0
    
    // compute the line parameters of the two closest points
    if (D < SMALL_NUM)
    { // the lines are almost parallel
        sN = 0.0;         // force using point P0 on segment S1
        sD = 1.0;         // to prevent possible division by 0.0 later
        tN = e;
        tD = c;
    }
    else
    {                 // get the closest points on the infinite lines
        sN = (b*e - c*d);
        tN = (a*e - b*d);
        if (sN < 0.0)
        {        // sc < 0 => the s=0 edge is visible
            sN = 0.0;
            tN = e;
            tD = c;
        }
        else if (sN > sD)
        {  // sc > 1  => the s=1 edge is visible
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }
    
    if (tN < 0.0)
    {            // tc < 0 => the t=0 edge is visible
        tN = 0.0;
        // recompute sc for this edge
        if (-d < 0.0)
        {
            sN = 0.0;
        }
        else if (-d > a)
        {
            sN = sD;
        }
        else
        {
            sN = -d;
            sD = a;
        }
    }
    else if (tN > tD)
    {      // tc > 1  => the t=1 edge is visible
        tN = tD;
        // recompute sc for this edge
        if ((-d + b) < 0.0)
        {
            sN = 0;
        }
        else if ((-d + b) > a)
        {
            sN = sD;
        }
        else
        {
            sN = (-d +  b);
            sD = a;
        }
    }
    // finally do the division to get sc and tc
    sc = (fabs(sN) < SMALL_NUM ? 0.0 : sN / sD);
    tc = (fabs(tN) < SMALL_NUM ? 0.0 : tN / tD);
    
    // get the difference of the two closest points
    Vector   dP = w + (u * sc) - (v * tc);  // =  S1(sc) - S2(tc)
    
    return dP.norm();   // return the closest distance
}
double sgn(double x)
{    
    if (x==0)
    {
        return 0;
    }
    else
    {
        return abs(x)/x;
    }
}
double positiveDifference(double x,double y)
{
    return fabs(x-y);
}
double radians(double deg)
{
    return deg*M_PI/180;
}
double degrees(double rad)
{
    return rad*180/M_PI;
}

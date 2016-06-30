//
//  Line2D.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/25/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>
#include "Line2D.h"
#include "basicshapes.h"
#include "Utilities.h"

#define EPS 0.000001

Line2D::Line2D(const Point& p1,const Point& p2)
{
    double x1=p1.getX();
    double x2=p2.getX();
    double y1=p1.getY();
    double y2=p2.getY();
    
    m=(y2-y1)/(x2-x1);
    b=y1-m*x1;
}
Line2D::Line2D(double mm,double bb)
{
    m=mm;
    b=bb;
}
double Line2D::getSlope() const
{
    return m;
}
double Line2D::getYIntercept() const
{
    return b;
}
Point Line2D::intersection(const Line2D& l1,const Line2D& l2)
{
    double a=l1.getSlope();
    double b=l2.getSlope();
    double c=l1.getYIntercept();
    double d=l2.getYIntercept();
    
    if (fabs(a-b)<EPS)
    {
        return Point(0.0,0.0,-1.0);
    }
    double x=(d-c)/(a-b);
    double y=(a*d-b*c)/(a-b);
    return Point(x,y,0.0);
}
bool Line2D::isPointAboveOrOnLine(const Point& p)
{
    double y=p.getY();
    double equation=m*p.getX()+b;
    if (y-equation>-EPS)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Line2D::isPointBelowOrOnLine(const Point& p)
{
    double y=p.getY();
    double equation=m*p.getX()+b;
    if (equation-y>-EPS)
    {
        return true;
    }
    else
    {
        return false;
    }
}
std::string Line2D::toString()
{
    std::string lineText="y=";
    lineText+=doubleToString(m);
    lineText+="x+";
    lineText+=doubleToString(b);
    return lineText;
}
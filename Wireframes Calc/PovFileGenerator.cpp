//
//  PovFileGenerator.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 11/26/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include <vector>

#include "PovFileGenerator.h"
#include "Utilities.h"

std::string povRaySphere(const Point& p,double thick,const std::string& color)
{
    std::string povCode="sphere {<";
    povCode+=p.toString();
    povCode+=">, ";
    povCode+=doubleToString(thick);
    povCode+=" texture{pigment{color ";
    povCode+=color;
    povCode+="} finish{phong 1}}}";
    
    return povCode;
}
std::string povRaySphere(double x,double y,double z, double thick,const std::string& color)
{
    std::string povCode="sphere {<";
    povCode+=doubleToString(x)+","+doubleToString(y)+","+doubleToString(z);
    povCode+=">, ";
    povCode+=doubleToString(thick);
    povCode+=" texture{pigment{color ";
    povCode+=color;
    povCode+="} finish{phong 1}}}";
    
    return povCode;
}

std::string povRayCylinder(const Point& p1,const Point&p2, double thick,const std::string& color)
{
    std::string povCode="cylinder {<";
    povCode+=p1.toString();
    povCode+=">,<";
    povCode+=p2.toString();
    povCode+=">, ";
    povCode+=doubleToString(thick);
    povCode+=" texture{pigment{color ";
    povCode+=color;
    povCode+="} finish{phong 1}}}";
    
    return povCode;
}
std::string povRayCylinder(const Line& l, double thick,const std::string& color)
{
    return povRayCylinder(l.getPointA(), l.getPointB(), thick, color);
}

std::string povRayTriangle(const Triangle& tri,const std::string& color)
{
    return "polygon {3, <"+tri.getPointA().toString()+">,<"+tri.getPointB().toString()+">,<"+tri.getPointC().toString()+"> texture{pigment{color "+color+"} finish{phong 1}}}";
}

std::string povRayTriangleList(const std::vector<Triangle>& list,const std::string& color)
{
    std::string triList="";
    int size=(int) list.size();
    for (int i=0; i<size; i++)
    {
        triList+=povRayTriangle(list.at(i),color);
        if (i<size-1)
        {
            triList+="\n";
        }
    }
    return triList;
}
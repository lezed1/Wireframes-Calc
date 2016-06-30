//
//  PenultimateTriangle.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/4/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>

#include "PenultimateTriangle.h"
#include "Face.h"
#include "basicshapes.h"
#include "FaceVertices.h"

PenultimateTriangle::PenultimateTriangle(const EdgeVector& e,const FaceVertices& pr):FaceGenerator(e,pr)
{
    attributes["ttt"]=1.0;
    attributes["nnn"]=-1.0;
    
    inners.resize(3);
}
bool PenultimateTriangle::verifyFaceIsTriangle()
{
    if (edges.size()!=3)
    {
        std::cout << "PenultimateTriangle::Face must have exactly three vertices." << "\n";
        return false;
    }
    else
    {
        return true;
    }
}
std::vector<Triangle> PenultimateTriangle::connectInnerPoints()
{
    std::vector<Triangle> triangles(3);
    Point p1=getVertex(0);
    Point p2=getVertex(1);
    Point p3=getVertex(2);
    
    Point fp1=inners.at(0);
    Point fp2=inners.at(1);
    Point fp3=inners.at(2);
    double ttt=attributes.at("ttt");
    double nnn=attributes.at("nnn");
    
    if ( (ttt>0.0 && nnn>0.0) || (ttt<0.0 && nnn<0.0) )
    {
        //std::cout << "\n\n\n" << ttt << " " << nnn << "\n\n\n";
        triangles.at(0)=Triangle(p1,fp2,p2);
        triangles.at(1)=Triangle(p2,fp3,p3);
        triangles.at(2)=Triangle(p3,fp1,p1);
    }
    else
    {
        //std::cout << "\n\n\n" << ttt << " " << nnn << "\n\n\n";
        triangles.at(0)=Triangle(p2,fp1,p1);
        triangles.at(1)=Triangle(p3,fp2,p2);
        triangles.at(2)=Triangle(p1,fp3,p3);
    }
    return triangles;
}

std::vector<Triangle> PenultimateTriangle::generateTriangles(double frameWidth)
{
    generateInnerPoints(frameWidth);
    return connectInnerPoints();
}

std::vector<std::pair<Triangle, int>> PenultimateTriangle::do_generateTriangleEdgePairs(double frameWidth)
{
    if (edges.size()!=3)
    {
        std::cout << "PenultimateTriangle::Face must have exactly 3 edges." << "\n";
        return std::vector<std::pair<Triangle, int>>();
    }
    
    //std::vector<Point> verticess=FaceGenerator::pointsFromEdgePairVector(pointedges);
    generateInnerPoints(frameWidth);
    std::vector<Triangle> triangles=connectInnerPoints();
    
    std::vector<std::pair<Triangle, int>> pairs;
    for (int i=0;i<triangles.size();i++)
    {
        pairs.push_back( std::pair<Triangle, int>(triangles.at(i),edges.at(i)) );
    }
    
    return pairs;
}

void PenultimateTriangle::generateInnerPoints(double frameWidth)
{
    Point p1=getVertex(0);
    Point p2=getVertex(1);
    Point p3=getVertex(2);
    double theta=frameWidth;
    double nnn=attributes.at("nnn");
    
    Point center=(p1+p2+p3)/3.0;
    double sidelength=Point::distance(p1, p2);
    double smallside=sidelength*sin(radians(theta))/sin(radians(120));
    double longside=sidelength*sin(radians(60-theta))/sin(radians(120));
    double newside=longside-smallside;
    double efactor=newside/sidelength;
    
    Point np1=Point::extendLine(p1,center,1-efactor);
    Point np2=Point::extendLine(p2,center,1-efactor);
    Point np3=Point::extendLine(p3,center,1-efactor);
    
    double twist;
    if (nnn>0.0)
    {
        twist=theta;
    }
    else
    {
        twist=-theta;
    }
    
    Line twistAxis(center,Point(0,0,0));
    np1.twistPoint(twistAxis, twist);
    np2.twistPoint(twistAxis, twist);
    np3.twistPoint(twistAxis, twist);
    
    inners.at(0)=np1;
    inners.at(1)=np2;
    inners.at(2)=np3;
}

double PenultimateTriangle::do_calculateMaxWidth() const
{
    return 30.0;
}

PenultimateTriangle* PenultimateTriangle::doClone()
{
    return new PenultimateTriangle(*this);
}
//
//  FramedFace.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/23/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>

#include "FramedFace.h"
#include "basicshapes.h"
#include "Vertex.h"
#include "PovFileGenerator.h"
#include "FaceVertices.h"

FramedFace::~FramedFace()
{
    
}

FramedFace::FramedFace(const EdgeVector& e,const FaceVertices& pr):FaceGenerator(e,pr)
{
    
}
std::vector<Triangle> FramedFace::connectInnerPoints()
{
    int faceSize=(int) edges.size();
    std::vector<Triangle> generatedTriangles;
    generatedTriangles.reserve(2*faceSize);
    for (int i=0;i<faceSize;i++)
    {
        int index1=(i)%faceSize;
        int index2=(i+1)%faceSize;
        
        Point v1=getVertex(index1);
        Point v2=getVertex(index2);
        
        generatedTriangles.push_back( Triangle(v1,inners.at(index2),inners.at(index1)) );
        generatedTriangles.push_back( Triangle(v1,v2,inners.at(index2)) );
    }
    return generatedTriangles;
}
std::vector<std::pair<Triangle, int>> FramedFace::makeTriangleEdgePairs(double frameWidth)
{
    int faceSize=(int) edges.size();
    std::vector<std::pair<Triangle, int>> pairs;
    pairs.reserve(2*faceSize);
    for (int i=0;i<faceSize;i++)
    {
        int index1=(i)%faceSize;
        int index2=(i+1)%faceSize;
        int edgeIndex=edges.at(i);
        
        Point v1=getVertex(index1);
        Point v2=getVertex(index2);
        
        pairs.push_back( std::pair<Triangle,int>( Triangle(v1,inners.at(index2),inners.at(index1)) , edgeIndex) );
        pairs.push_back( std::pair<Triangle,int>( Triangle(v1,v2,inners.at(index2)) , edgeIndex) );
    }
    return pairs;
}
std::vector<Triangle> FramedFace::generateTriangles(double frameWidth)
{
    generateInnerPoints(frameWidth);
    return connectInnerPoints();
}
std::vector<std::pair<Triangle, int>> FramedFace::do_generateTriangleEdgePairs(double frameWidth)
{
    generateInnerPoints(frameWidth);
    return makeTriangleEdgePairs(frameWidth);
}
void FramedFace::generateInnerPoints(double frameWidth)
{
    int faceSize=(int) edges.size();
    inners.resize(faceSize);
    
    Point bisector;
    double angle,factor;

    for (int i=0;i<faceSize;i++)
    {
        int index1=(i-1)%faceSize;
        int index2=i%faceSize;
        int index3=(i+1)%faceSize;
        
        if (index1==-1) { index1=faceSize-1; }
        
        Point v1=getVertex(index1);
        Point v2=getVertex(index2);
        Point v3=getVertex(index3);
        
        bisector=Point::angleBisector(v1, v2, v3);
        angle=Point::angleMeasure(v1, v2, v3)/2.0;
        
        factor=frameWidth/sin(angle)/Point::distance(v2, bisector);
        inners.at(i)=Point::extendLine(v2, bisector, factor);
    }
}
double FramedFace::do_calculateMaxWidth() const
{
    double maxHeight=1000000.0;
    int vertexNum=(int) edges.size();
    for (int i=0;i<vertexNum;i++)
    {
        int a1=i;   //verticies for 1st angle
        int a2=i+1;
        int a3=i+2;
        a1%=vertexNum;
        a2%=vertexNum;
        a3%=vertexNum;
        
        int b1=i+1; //verticies for 2nd angle
        int b2=i+2;
        int b3=i+3;
        b1%=vertexNum;
        b2%=vertexNum;
        b3%=vertexNum;
        
        double angle1=Point::angleMeasure(getVertex(a1), getVertex(a2), getVertex(a3))/2.0; //1st angle measure
        double angle2=Point::angleMeasure(getVertex(b1), getVertex(b2), getVertex(b3))/2.0; //2nd angle measure
        double edgeLength=Point::distance(getVertex(a2), getVertex(b2));
        
        double heightForEdge=edgeLength/(1.0/tan(angle1)+1.0/tan(angle2));
        /*if (heightForEdge<maxHeight)
        {
            maxHeight=heightForEdge;
        }*/
        maxHeight=fmin(heightForEdge,maxHeight);
    }
    return maxHeight;
}
FramedFace* FramedFace::doClone()
{
    return new FramedFace(*this);
}
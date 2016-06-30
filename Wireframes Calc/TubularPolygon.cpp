//
//  TubularPolygon.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/13/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include "TubularPolygon.h"
#include "basicshapes.h"
#include "AffineTransformation.h"

TubularPolygon::TubularPolygon(const EdgeVector& e,const FaceVertices& pr):FramedFace(e,pr)
{
    
}
Vector TubularPolygon::getFaceNormal(double magnitude) const
{
    Point v1=getVertex(0);
    Point v2=getVertex(1);
    Point v3=getVertex(2);
    Plane facePlane=Plane::planeThroughPoints(v1, v2, v3);
    Vector normal=facePlane.getNormalVector();
    normal.normalize();
    normal*=magnitude;
    return normal;
}

std::vector<std::pair<Triangle, int>> TubularPolygon::do_generateTriangleEdgePairs(double frameWidth)
{
    generateInnerPoints(frameWidth);
    std::vector<std::pair<Triangle, int>> flatFacePairs=makeTriangleEdgePairs(frameWidth);
    std::vector<std::pair<Triangle, int>> tubularPairs;
    int faceSize=(int) edges.size();
    tubularPairs.reserve(4*faceSize);
    Vector shift=getFaceNormal(frameWidth/2.0);
    AffineTransformation upShift(shift);
    AffineTransformation downShift(shift*-1.0);
    for (int i=0;i<flatFacePairs.size();i++) //shift triangles up and down
    {
        std::pair<Triangle,int> pair=flatFacePairs.at(i);
        Triangle upperTriangle=Triangle::transform(pair.first,upShift);
        Triangle lowerTriangle=Triangle::transform(pair.first,downShift);
        tubularPairs.push_back(std::pair<Triangle,int>(upperTriangle,pair.second));
        tubularPairs.push_back(std::pair<Triangle,int>(lowerTriangle,pair.second));
    }
    for (int i=0;i<faceSize;i++) //generate the lateral faces of the tube
    {
        int index1=(i)%faceSize;
        int index2=(i+1)%faceSize;
        int edgeIndex=edges.at(i);
        
        Point v1=getVertex(index1);
        Point v2=getVertex(index2);
        Point v1up=upShift.transform(v1);
        Point v2up=upShift.transform(v2);
        Point v1down=downShift.transform(v1);
        Point v2down=downShift.transform(v2);
        
        Triangle t1(v1up,v2down,v2up);
        Triangle t2(v1up,v2down,v1down);
        tubularPairs.push_back(std::pair<Triangle,int>(t1,edgeIndex));
        tubularPairs.push_back(std::pair<Triangle,int>(t2,edgeIndex));
    }
    return tubularPairs;
}
std::vector<Triangle> TubularPolygon::generateTriangles(double frameWidth)
{
    generateInnerPoints(frameWidth);
    std::vector<Triangle> flatFaceTriangles=connectInnerPoints();
    std::vector<Triangle> tubularTriangles;
    int faceSize=(int) edges.size();
    tubularTriangles.reserve(4*faceSize);
    Vector shift=getFaceNormal(frameWidth/2.0);
    AffineTransformation upShift(shift);
    AffineTransformation downShift(shift*-1.0);
    for (int i=0;i<flatFaceTriangles.size();i++) //shift triangles up and down
    {
        Triangle upperTriangle=Triangle::transform(flatFaceTriangles.at(i),upShift);
        Triangle lowerTriangle=Triangle::transform(flatFaceTriangles.at(i),downShift);
        tubularTriangles.push_back(upperTriangle);
        tubularTriangles.push_back(lowerTriangle);
    }
    for (int i=0;i<faceSize;i++) //generate the lateral faces of the tube
    {
        int index1=(i)%faceSize;
        int index2=(i+1)%faceSize;
        
        Point v1=getVertex(index1);
        Point v2=getVertex(index2);
        Point v1up=upShift.transform(v1);
        Point v2up=upShift.transform(v2);
        Point v1down=downShift.transform(v1);
        Point v2down=downShift.transform(v2);
        
        Triangle t1(v1up,v2down,v2up);
        Triangle t2(v1up,v2down,v1down);
        tubularTriangles.push_back(t1);
        tubularTriangles.push_back(t2);
    }
    return tubularTriangles;
}
double TubularPolygon::do_calculateMaxWidth() const
{
    return FramedFace::do_calculateMaxWidth();
}
TubularPolygon* TubularPolygon::doClone()
{
    return new TubularPolygon(*this);
}
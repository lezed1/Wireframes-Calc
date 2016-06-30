//
//  Polyhedron.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/20/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Polyhedron__
#define __Wireframes_Calc_4__Polyhedron__

#include <iostream>

#include "PolyhedralSkeleton.h"
#include "VerticesManager.h"
#include "Attribute.h"
#include "FaceGenerator.h"
#include "FaceVertices.h"
#include "AffineTransformation.h"

class Frame;
class FrameEdge;
class Polyhedron
{
private:
    VerticesManager vertices;
    std::vector<std::unique_ptr<FaceGenerator>> faces;
    AffineTransformation transformation;
    std::map<std::string,Attribute> attributes;
    std::vector<std::string> indexedAttributes;
    int vertexNumber;
    
    void transform();
    virtual void setVertexValues()=0;
    virtual void setFaceAttributes()=0;
    
    virtual Polyhedron* doClone() const=0;
protected:
    PolyhedralSkeleton structure;
    Polyhedron(int vNum);
    Polyhedron(double xrot,double yrot,double zrot,int vNum);
    Polyhedron(const Polyhedron& source);
    Polyhedron& operator=(const Polyhedron& source);
    
    void setValues();
    
    void setVertex(int index, double x,double y,double z);
    Point& getVertexRef(int index);
    
    void addAttribute(const std::string& name,const Attribute& a);
public:
    Polyhedron* clone() const;
    
    Frame makeFrame(double frameWidth=-1.0) const;
    FrameEdge makeFrameEdge(int edgeID,double frameWidth=-1.0) const;
    double calculateMaxFrameWidth() const;
    
    Attribute getAttribute(const std::string& name) const;
    void setAttribute(const std::string& name,double newValue);
    
    void setFaceAttribute(int index,const std::string& name,double value);
    template <class FaceType>
    void addFace(const std::vector<int>& points);
    
    void addTransformation(const AffineTransformation& at);
    void setTransformation(const AffineTransformation& at);
    void addRotation(double xrot,double yrot,double zrot);
    void addRotation(const Point& p);
    void setRotation(double xrot,double yrot,double zrot);
    void setRotation(const Point& p);
    AffineTransformation getTransformation() const;
    
    Point getVertex(int index) const;
    
    int getEdgeNum() const;
    int getFaceNum() const;
    Line getEdgeLine(int index) const;
    double getLongestEdgeLength() const;
    
    int getNumOfAtts() const;
    int getVertexNum() const;
    
    std::vector<int> getEdgesAroundVertex(int index) const;
    std::vector<int> getVerticesAroundVertex(int index) const;
    std::vector<int> getEdgesAroundEdge(int edgeIndex,int endpoint) const;
    std::pair<int,int> getEdgeEndpoints(int index) const;
    int getVertexValency(int index) const;
    std::vector<Line> edgesToLines(const std::vector<int>& edgeIndices) const;
    std::vector<Point> verticesToPoints(const std::vector<int>& vertexIndices) const;
    std::vector<Point> getFaceVertices(int index) const;
    
    void printPovRayFrame(double frameWidth,const std::string& color, std::ostream &ostream = std::cout) const;
    void printPovRaySkeleton(double thickness,const std::string& color, std::ostream& ostream = std::cout) const;
    void printCurrentAttributeList() const;
    
    virtual ~Polyhedron();
};

template<class FaceType>
void Polyhedron::addFace(const std::vector<int>& points)
{
    
    if (points.size()<3)
    {
        std::cout << "Face is degenerate, has less than 3 sides, Face will not be added to PolyhedronSkeleton";
    }
    else
    {
        structure.addFace(points);
        int newFaceIndex=(int) faces.size();
        std::vector<int> newFaceEdges=structure.getFace(newFaceIndex).getEdges();
        std::vector<int> newFacePoints=structure.getFace(newFaceIndex).getVertices();
        FaceVertices pr(this,newFacePoints);
        faces.push_back( std::unique_ptr<FaceGenerator>(new FaceType(newFaceEdges,pr)));
    }
}

#endif /* defined(__Wireframes_Calc_4__Polyhedron__) */

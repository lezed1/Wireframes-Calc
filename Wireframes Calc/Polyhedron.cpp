//
//  Polyhedron.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/20/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>

#include "Polyhedron.h"
#include "Attribute.h"
#include "Frame.h"
#include "VerticesManager.h"
#include "PovFileGenerator.h"

/*Polyhedron::Polyhedron(const Polyhedron& p):structure(p.structure),vertices(p.vertices)
{
    rotations=p.rotations;
    attributes=p.attributes;
    indexedAttributes=p.indexedAttributes;
    vertexNumber=p.vertexNumber;
}*/
Polyhedron::Polyhedron(const Polyhedron& source):vertices(source.vertices),structure(source.structure),transformation(source.transformation),attributes(source.attributes),indexedAttributes(source.indexedAttributes),vertexNumber(source.vertexNumber)
{
    int index=0;
    for (auto it=source.faces.begin();it<source.faces.end();it++)
    {
        std::vector<int> newFacePoints=structure.getFace(index).getVertices();
        FaceVertices fv(this,newFacePoints);
        faces.push_back(std::unique_ptr<FaceGenerator>( (*it)->clone(fv) ));
        
        index++;
    }
}
Polyhedron& Polyhedron::operator=(const Polyhedron& source)
{
    if (this!=&source)
    {
        vertices=source.vertices;
        transformation=source.transformation;
        attributes=source.attributes;
        indexedAttributes=source.indexedAttributes;
        vertexNumber=source.vertexNumber;
        structure=source.structure;
        faces.resize(0);
        
        int index=0;
        for (auto it=source.faces.begin();it<source.faces.end();it++)
        {
            std::vector<int> newFacePoints=structure.getFace(index).getVertices();
            FaceVertices fv(this,newFacePoints);
            faces.push_back(std::unique_ptr<FaceGenerator>( (*it)->clone(fv) ));
            
            index++;
        }
    }
    return *this;
}

Polyhedron::~Polyhedron()
{
    
}
Polyhedron::Polyhedron(int vNum):structure(PolyhedralSkeleton(vNum)),vertices(VerticesManager(vNum))
{
    vertexNumber=vNum;
    //Point rot(0,0,0);
    //rotations.push_back(rot);
    transformation=AffineTransformation(AffineTransformation::makeRotation(0,0,0));
}
Polyhedron::Polyhedron(double xrot,double yrot,double zrot,int vNum):structure(PolyhedralSkeleton(vNum)),vertices(VerticesManager(vNum))
{
    vertexNumber=vNum;
    //Point rot(xrot,yrot,zrot);
    //rotations.push_back(rot);
    transformation=AffineTransformation(AffineTransformation::makeRotation(xrot,yrot,zrot));
}
Polyhedron* Polyhedron::clone() const
{
    return doClone();
}
double Polyhedron::calculateMaxFrameWidth() const
{
    double maxWidth=1000000.0;
    int faceSize=(int) faces.size();
    for (int i=0;i<faceSize;i++)
    {
        maxWidth=fmin(maxWidth,faces.at(i)->calculateMaxWidth());
    }
    return maxWidth;
}

Frame Polyhedron::makeFrame(double frameWidth) const
{
    int edgenum=structure.getEdgeNum();
    
    double maxWidth=calculateMaxFrameWidth();
    if (frameWidth<0.0)
    {
        frameWidth=maxWidth;
    }
    Frame polyFrame(edgenum,frameWidth);
    for (int i=0;i<edgenum;i++)
    {
        polyFrame.addFrameEdge(getEdgeLine(i));
    }
    
    for (int i=0;i<faces.size();i++)
    {
        auto pairs=faces.at(i)->generateTriangleEdgePairs(frameWidth);
        for (int j=0;j<pairs.size();j++)
        {
            auto pair=pairs.at(j);
            polyFrame.addTriangle(pair.second, pair.first);
        }
    }
    
    return polyFrame;
}
FrameEdge Polyhedron::makeFrameEdge(int edgeID,double frameWidth) const
{
    double maxWidth=calculateMaxFrameWidth();
    if (frameWidth<0.0)
    {
        frameWidth=maxWidth;
    }
    
    Line edgeLine=getEdgeLine(edgeID);
    FrameEdge fe(edgeLine);
    
    std::vector<int> adjacentFaces=structure.getEdge(edgeID).getAdjacentFaces();
    for (int i=0;i<adjacentFaces.size();i++)
    {
        auto pairs=faces.at(adjacentFaces.at(i))->generateTriangleEdgePairs(frameWidth);
        for (int j=0;j<pairs.size();j++)
        {
            auto pair=pairs.at(j);
            if (pair.second==edgeID)
            {
                fe.addTriangle(pair.first);
            }
        }
    }
    
    return fe;
}

void Polyhedron::setVertex(int index, double x,double y,double z)
{
    vertices.setVertex(index, x,y,z);
}
Point& Polyhedron::getVertexRef(int index)
{
    return vertices.getVertexRef(index);
}
Point Polyhedron::getVertex(int index) const
{
    return vertices.getVertex(index);
}

void Polyhedron::setValues()
{
    setVertexValues();
    setFaceAttributes();
    transform();
}
void Polyhedron::transform()
{
    for (int i=0;i<vertexNumber;i++)
    {
        getVertexRef(i)=transformation.transform(getVertexRef(i));
    }
}
void Polyhedron::addAttribute(const std::string& name,const Attribute& a)
{
    attributes.insert(std::pair<std::string, Attribute>(name,a));
}
Attribute Polyhedron::getAttribute(const std::string& name) const
{
    return attributes.at(name);
}
void Polyhedron::setAttribute(const std::string& name,double newValue)
{
    attributes.at(name).setCurrentValue(newValue);
    setValues();
}

void Polyhedron::addTransformation(const AffineTransformation& at)
{
    transformation.compose(at);
    setValues();
}
void Polyhedron::setTransformation(const AffineTransformation& at)
{
    transformation=at;
    setValues();
}
void Polyhedron::addRotation(double xrot,double yrot,double zrot)
{
    transformation.compose(AffineTransformation::makeRotation(xrot,yrot,zrot));
    setValues();
}
void Polyhedron::addRotation(const Point& p)
{
    addRotation(p.getX(),p.getY(),p.getZ());
}
void Polyhedron::setRotation(double xrot,double yrot,double zrot)
{
    transformation=AffineTransformation::makeRotation(xrot,yrot,zrot);
    setValues();
}
void Polyhedron::setRotation(const Point& p)
{
    setRotation(p.getX(),p.getY(),p.getZ());
}
AffineTransformation Polyhedron::getTransformation() const
{
    return transformation;
}

void Polyhedron::setFaceAttribute(int index,const std::string& name,double value)
{
    faces.at(index)->setAttribute(name,value);
}
void Polyhedron::printPovRayFrame(double frameWidth,const std::string& color, std::ostream &ostream) const
{
    makeFrame(frameWidth).printPovRay(color, ostream);
}
void Polyhedron::printPovRaySkeleton(double thickness,const std::string& color, std::ostream& ostream) const
{
    for (int i=0;i<vertexNumber;i++)
    {
        ostream << povRaySphere(getVertex(i), thickness, color) << "\n";
    }
    for (int i=0;i<getEdgeNum();i++)
    {
        Line theEdge=getEdgeLine(i);
        ostream << povRayCylinder(theEdge, thickness, color) << "\n";
    }
}
int Polyhedron::getEdgeNum() const
{
    return structure.getEdgeNum();
}
int Polyhedron::getFaceNum() const
{
    return structure.getFaceNum();
}
Line Polyhedron::getEdgeLine(int index) const
{
    Edge theEdge=structure.getEdge(index);
    int endpoint1=theEdge.getEnd1();
    int endpoint2=theEdge.getEnd2();
    return Line(vertices.getVertex(endpoint1),vertices.getVertex(endpoint2));
}
double Polyhedron::getLongestEdgeLength() const
{
    double longest=getEdgeLine(0).getDistance();
    for (int i=1;i<structure.getEdgeNum();i++)
    {
        longest=fmax(longest,getEdgeLine(i).getDistance());
    }
    return longest;
}
void Polyhedron::printCurrentAttributeList() const
{
    for (auto i=attributes.begin();i!=attributes.end();++i)
    {
        std::cout << i->first << ":" << i->second.getCurrentValue() << " ";
    }
}
int Polyhedron::getNumOfAtts() const
{
    return (int)attributes.size();
}
int Polyhedron::getVertexNum() const
{
    return vertexNumber;
}


std::vector<int> Polyhedron::getEdgesAroundVertex(int index) const
{
    return structure.getVertex(index).getAdjacentEdges();
}
std::pair<int,int> Polyhedron::getEdgeEndpoints(int index) const
{
    Edge theEdge=structure.getEdge(index);
    return std::pair<int,int>(theEdge.getEnd1(), theEdge.getEnd2());
}
std::vector<int> Polyhedron::getVerticesAroundVertex(int index) const
{
    return structure.getVertex(index).getAdjacentVertices();
}
std::vector<int> Polyhedron::getEdgesAroundEdge(int edgeIndex,int endpoint) const
{
    Edge theEdge=structure.getEdge(edgeIndex);
    return theEdge.getAdjacentEdges(endpoint);
}
int Polyhedron::getVertexValency(int index) const
{
    //return number of edges around a vertex
    return structure.getVertex(index).getNumberOfAdjacentEdges();
}
std::vector<Line> Polyhedron::edgesToLines(const std::vector<int>& edgeIndices) const
{
    std::vector<Line> lines;
    for (int i=0;i<edgeIndices.size();i++)
    {
        lines.push_back(getEdgeLine(edgeIndices.at(i)));
    }
    return lines;
}
std::vector<Point> Polyhedron::verticesToPoints(const std::vector<int>& vertexIndices) const
{
    std::vector<Point> points;
    for (int i=0;i<vertexIndices.size();i++)
    {
        points.push_back(getVertex(vertexIndices.at(i)));
    }
    return points;
}
std::vector<Point> Polyhedron::getFaceVertices(int index) const
{
    return verticesToPoints(structure.getFace(index).getVertices());
}
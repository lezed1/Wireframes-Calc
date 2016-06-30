//
//  PolyhedralSkeleton.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 11/26/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>

#include "PolyhedralSkeleton.h"
#include "PovFileGenerator.h"
#include "Face.h"
#include "Frame.h"

PolyhedralSkeleton::PolyhedralSkeleton(int vertexNum)
{
    vertices.resize(vertexNum);
}
void PolyhedralSkeleton::establishEdgeConnections(int index,const std::vector<int>& connectees)
{
    //edges.at(index).addAdjacentEdges(connectees);
    
    //add adjacent old edges to new edge
    Edge newEdge=edges.at(index);
    for (auto it=connectees.begin(); it<connectees.end(); it++)
    {
        bool addToEnd1=edges.at(*it).hasVertex(newEdge.getEnd1()); //old edge has new edge's endpoint1
        bool addToEnd2=edges.at(*it).hasVertex(newEdge.getEnd2()); //old edge has new edge's endpoint2
        if (addToEnd1) {edges.at(index).addAdjacentEdge(*it, 1);}
        if (addToEnd2) {edges.at(index).addAdjacentEdge(*it, 2);}
    }
    //add new edge to adjacent old edges
    for (auto it=connectees.begin(); it<connectees.end(); it++)
    {
        bool addToEnd1=newEdge.hasVertex(edges.at(*it).getEnd1()); //new edge has old edge's endpoint1
        bool addToEnd2=newEdge.hasVertex(edges.at(*it).getEnd2()); //new edge has old edge's endpoint2
        if (addToEnd1) {edges.at(*it).addAdjacentEdge(index, 1);}
        if (addToEnd2) {edges.at(*it).addAdjacentEdge(index, 2);}
        
        //edges.at(*it).addAdjacentEdge(index);
    }
}
void PolyhedralSkeleton::addEdge(int end1, int end2)
{
    //std::cout << vertices.size();
    Edge newEdge(end1,end2);
    edges.push_back(newEdge);
    int newEdgeID=(int) edges.size()-1;
    establishEdgeConnections(newEdgeID, vertices.at(end1).getAdjacentEdges());
    establishEdgeConnections(newEdgeID, vertices.at(end2).getAdjacentEdges());
    vertices.at(end1).addAdjacentEdge(newEdgeID,end2);
    vertices.at(end2).addAdjacentEdge(newEdgeID,end1);
}
void PolyhedralSkeleton::addFace(const std::vector<int>& points)
{
    std::vector<int> faceEdges;
    int vertexNum=(int) points.size();
    for (int i=0;i<vertexNum;i++) //generate face edge list
    {
        int index1=i%vertexNum;
        int index2=(i+1)%vertexNum;
        int v1=points.at(index1);
        int v2=points.at(index2);
        
        int edgeID=vertices.at(v1).getEdgeToVertex(v2);
        if (edgeID==-1) //no edge between the vertices
        {
            std::cout << "Invalid Face: Edge between " << v1 << " and " << v2 << " does not exist. \n";
            return;
        }
        else
        {
            faceEdges.push_back(edgeID);
        }
    }
    faces.push_back(Face(points,faceEdges));
    int newFaceID=(int) (faces.size()-1);
    for (int i=0;i<faceEdges.size();i++)
    {
        edges.at(faceEdges.at(i)).addAdjacentFace(newFaceID);
    }
}

//GETTERS//
Edge PolyhedralSkeleton::getEdge(int index) const
{
    if (!inEdgeBounds(index))
    {
        std::cout << "Error: PolyhedronSkeleton::getEdge called with index out of range: " << index << "\n";
        Edge defaultEdge;
        return defaultEdge;
    }
    return edges.at(index);
}
Face PolyhedralSkeleton::getFace(int index) const
{
    if (!inFaceBounds(index))
    {
        std::cout << "Error: PolyhedronSkeleton::getFace called with index out of range: " << index << "\n";
        Face defaultFace({},{});
        return defaultFace;
    }
    return faces.at(index);
}
Vertex PolyhedralSkeleton::getVertex(int index) const
{
    if (!inVertexBounds(index))
    {
        std::cout << "Error: PolyhedronSkeleton::getVertex called with index out of range: " << index << "\n";
        Vertex defaultVertex;
        return defaultVertex;
    }
    return vertices.at(index);
}
int PolyhedralSkeleton::getEdgeNum() const
{
    return (int)edges.size();
}
int PolyhedralSkeleton::getFaceNum() const
{
    return (int)faces.size();
}
std::pair<int,int> PolyhedralSkeleton::getEdgeValencies(int index) const
{
    int v1=edges.at(index).getEnd1();
    int v2=edges.at(index).getEnd2();
    int v1Valency=vertices.at(v1).getNumberOfAdjacentEdges();
    int v2Valency=vertices.at(v2).getNumberOfAdjacentEdges();
    return std::pair<int,int>(v1Valency,v2Valency);
}

//BOUNDS CHECKING//
bool PolyhedralSkeleton::inEdgeBounds(int index) const
{
    if (index<edges.size() && index>=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool PolyhedralSkeleton::inVertexBounds(int index) const
{
    if (index<vertices.size() && index>=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool PolyhedralSkeleton::inFaceBounds(int index) const
{
    if (index<faces.size() && index>=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool PolyhedralSkeleton::isFaceValid(const std::vector<int>& points) const
{
    int vertexNum=(int) points.size();
    for (int i=0;i<vertexNum;i++)
    {
        int index1=i%vertexNum;
        int index2=(i+1)%vertexNum;
        int v1=points.at(index1);
        int v2=points.at(index2);
        
        int edgeID=vertices.at(v1).getEdgeToVertex(v2);
        if (edgeID==-1) //no edge between the vertices
        {
            return false;
        }
    }
    return true;
}
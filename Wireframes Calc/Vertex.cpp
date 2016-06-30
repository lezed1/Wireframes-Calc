//
//  Vertex.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 11/23/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include <vector>
#include <map>
#include <string>

#include "Vertex.h"
#include "basicshapes.h"
#include "Utilities.h"

Vertex::Vertex()
{

}
std::vector<int> Vertex::getAdjacentEdges() const
{
    return adjacentEdges;
}
void Vertex::addAdjacentEdge(int edge,int otherEndpoint)
{
    adjacentEdges.push_back(edge);
    addMapPairing(otherEndpoint, edge);
}

/*std::vector<int> Vertex::getAdjacentFaces() const
{
    return adjacentFaces;
}
void Vertex::addAdjacentFace(int face)
{
    adjacentFaces.push_back(face);
}*/

void Vertex::addMapPairing(int vertex, int edge)
{
    adjacentVerticesToEdges.insert(std::pair<int, int>(vertex,edge));
}
int Vertex::getEdgeToVertex(int vertexIndex) const
{
    auto it=adjacentVerticesToEdges.find(vertexIndex);
    if (it==adjacentVerticesToEdges.end())
    {
        return -1; //no edge joining this vertex and the vertex at vertexIndex
    }
    else
    {
        return it->second;
    }
}
std::vector<int> Vertex::getAdjacentVertices() const
{
    std::vector<int> adjacentVertices;
    for (auto it=adjacentVerticesToEdges.begin(); it!=adjacentVerticesToEdges.end(); it++)
    {
        adjacentVertices.push_back(it->first);
    }
    return adjacentVertices;
}
int Vertex::getNumberOfAdjacentEdges() const
{
    return (int)adjacentEdges.size();
}

std::string Vertex::adjacentEdgesString()
{
    std::string edges="";
    for (auto it=adjacentEdges.begin(); it<adjacentEdges.end(); it++)
    {
        edges+=intToString(*it);
        edges+=",";
    }
    edges.pop_back();
    edges="["+edges+"]";
    return edges;
}
/*std::string Vertex::adjacentFacesString()
{
    std::string faces="[";
    for (auto it=adjacentFaces.begin(); it<adjacentFaces.end(); it++)
    {
        faces+=intToString(*it);
        faces+=",";
    }
    faces.pop_back();
    faces+="]";
    return faces;
}*/
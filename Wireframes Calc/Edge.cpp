//
//  Edge.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 11/23/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include <vector>
#include <string>

#include "Edge.h"
#include "Utilities.h"

Edge::Edge():end1ID(-1),end2ID(-1)
{
    //end1ID=-1;
    //end2ID=-1;
}
Edge::Edge(int e1,int e2):end1ID(e1),end2ID(e2)
{
    //end1ID=e1;
    //end2ID=e2;
}
void Edge::addAdjacentEdge(int edge,int endpoint)
{
    if (endpoint==1)
    {
        adjacentEdgesEnd1.push_back(edge);
    }
    if (endpoint==2)
    {
        adjacentEdgesEnd2.push_back(edge);
    }
    //adjacentEdges.push_back(edge);
}
bool Edge::hasVertex(int vertexID) const
{
    return end1ID==vertexID || end2ID==vertexID;
}
/*void Edge::addAdjacentEdges(const std::vector<int>& newEdges)
{
    adjacentEdges.insert(adjacentEdges.end(),newEdges.begin(),newEdges.end());
}*/

void Edge::addAdjacentFace(int face)
{
    adjacentFaces.push_back(face);
}

int Edge::getEnd1() const
{
    return end1ID;
}
int Edge::getEnd2() const
{
    return end2ID;
}
std::vector<int> Edge::getAdjacentEdges(int endpoint) const
{
    if (endpoint==1)
    {
        return adjacentEdgesEnd1;
    }
    else if (endpoint==2)
    {
        return adjacentEdgesEnd2;
    }
    else
    {
        std::cout << "Error:  Edge::getAdjacentEdges called with enpoint other than 1 or 2: " << endpoint << "\n";
        std::vector<int> empty;
        return empty;
    }
}
std::vector<int> Edge::getAdjacentFaces() const
{
    return adjacentFaces;
}
std::string Edge::endPointsString() const
{
    return intToString(end1ID)+","+intToString(end2ID);
}
std::string Edge::adjacentEdgesString() const
{
    std::string edgesEnd1="";
    for (auto it=adjacentEdgesEnd1.begin(); it<adjacentEdgesEnd1.end(); it++)
    {
        edgesEnd1+=intToString(*it);
        edgesEnd1+=",";
    }
    edgesEnd1.pop_back();
    edgesEnd1="["+edgesEnd1+"]";
    
    std::string edgesEnd2="";
    for (auto it=adjacentEdgesEnd2.begin(); it<adjacentEdgesEnd2.end(); it++)
    {
        edgesEnd1+=intToString(*it);
        edgesEnd1+=",";
    }
    edgesEnd2.pop_back();
    edgesEnd2="["+edgesEnd2+"]";
    
    std::string edges="Endpoint 1: "+edgesEnd1+"\nEndpoint2: "+edgesEnd2;
    
    return edges;
}
std::string Edge::adjacentFacesString() const
{
    std::string faces="";
    for (auto it=adjacentFaces.begin(); it<adjacentFaces.end(); it++)
    {
        faces+=intToString(*it);
        faces+=",";
    }
    faces.pop_back();
    faces="["+faces+"]";
    return faces;
}
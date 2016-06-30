//
//  Vertex.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 11/23/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Vertex__
#define __Wireframes_Calc_4__Vertex__

#include <vector>
#include <map>

#include "basicshapes.h"

class Vertex
{
private:
    std::vector<int> adjacentEdges;
    //std::vector<int> adjacentFaces;
    std::map<int,int> adjacentVerticesToEdges;
    
    void addMapPairing(int vertex,int edge);
public:
    Vertex(); //default (0,0,0)
    
    std::vector<int> getAdjacentEdges() const;
    std::vector<int> getAdjacentVertices() const;
    void addAdjacentEdge(int edge,int otherEndpoint);
    
    //std::vector<int> getAdjacentFaces() const;
    //void addAdjacentFace(int face);
    
    int getEdgeToVertex(int vertexIndex) const;
    int getNumberOfAdjacentEdges() const;
    
    std::string positionString();
    std::string adjacentEdgesString();
    //std::string adjacentFacesString();
};

#endif /* defined(__Wireframes_Calc_4__Vertex__) */

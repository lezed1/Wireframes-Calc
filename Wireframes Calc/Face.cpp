//
//  Face.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 4/26/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include <vector>

#include "Face.h"
#include "Utilities.h"


Face::Face(const std::vector<int>& av,const std::vector<int>& ae):adjacentVertices(av),adjacentEdges(ae)
{
    
}
std::vector<int> Face::getEdges() const
{
    return adjacentEdges;
}
std::vector<int> Face::getVertices() const
{
    return adjacentVertices;
}
std::string Face::verticesString() const
{
    std::string vertices="";
    for (auto it=adjacentVertices.begin(); it<adjacentVertices.end(); it++)
    {
        vertices+=intToString(*it);
        vertices+=",";
    }
    vertices.pop_back();
    vertices="["+vertices+"]";
    return vertices;
}
std::string Face::edgesString() const
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
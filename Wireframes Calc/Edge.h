//
//  Edge.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 11/23/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Edge__
#define __Wireframes_Calc_4__Edge__

#include <vector>

class Edge
{
private:
    int end1ID,end2ID;
    std::vector<int> adjacentEdgesEnd1;
    std::vector<int> adjacentEdgesEnd2;
    std::vector<int> adjacentFaces;
public:
    Edge(); //default endpoints are -1 and -1
    Edge(int e1,int e2);
    
    void addAdjacentEdge(int edge,int endpoint);
    void addAdjacentFace(int face);
    bool hasVertex(int vertexID) const;
    //void addAdjacentEdges(const std::vector<int>& newEdges);
    
    int getEnd1() const;
    int getEnd2() const;
    std::vector<int> getAdjacentEdges(int endpoint) const;
    std::vector<int> getAdjacentFaces() const;
    
    std::string endPointsString() const;
    std::string adjacentEdgesString() const;
    std::string adjacentFacesString() const;
};

#endif /* defined(__Wireframes_Calc_4__Edge__) */

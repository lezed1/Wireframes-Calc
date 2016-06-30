//
//  PolyhedralSkeleton.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 11/26/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__PolyhedralSkeleton__
#define __Wireframes_Calc_4__PolyhedralSkeleton__

#include <vector>

#include "Edge.h"
#include "Vertex.h"
#include "Face.h"

class Frame;
class PolyhedralSkeleton
{
private:
    std::vector<Edge> edges;
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    
    bool inEdgeBounds(int index) const;
    bool inVertexBounds(int index) const;
    bool inFaceBounds(int index) const;
    bool isFaceValid(const std::vector<int>& points) const;
    
    void establishEdgeConnections(int index,const std::vector<int>& connectees);
public:
    PolyhedralSkeleton(int vertexNum);
    
    void addEdge(int end1,int end2);
    void addFace(const std::vector<int>& points);
    
    Edge getEdge(int index) const;
    Face getFace(int index) const;
    Vertex getVertex(int index) const;
    std::pair<int,int> getEdgeValencies(int index) const;
    int getEdgeNum() const;
    int getFaceNum() const;
};

#endif /* defined(__Wireframes_Calc_4__PolyhedralSkeleton__) */

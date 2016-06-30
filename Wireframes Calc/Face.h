//
//  Face.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 4/26/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__Face__
#define __Wireframes_Calc_4_5__Face__

#include <vector>
#include <map>

class Point;
class Vertex;
class Triangle;
class Face
{
private:
    std::vector<int> adjacentVertices;
    std::vector<int> adjacentEdges;
public:
    Face(const std::vector<int>& av,const std::vector<int>& ae);
    
    std::vector<int> getEdges() const;
    std::vector<int> getVertices() const;
    
    std::string verticesString() const;
    std::string edgesString() const;
};

#endif /* defined(__Wireframes_Calc_4_5__Face__) */

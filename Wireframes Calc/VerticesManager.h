//
//  VerticesManager.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 4/26/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__VerticesManager__
#define __Wireframes_Calc_4_5__VerticesManager__

#include <vector>
#include "basicshapes.h"

class Point;
class VerticesManager
{
private:
    std::vector<Point> vertices;
public:
    VerticesManager(int vertexNum);
    void setVertex(int index, double x,double y,double z);
    Point& getVertexRef(int index);
    Point getVertex(int index) const;
};

#endif /* defined(__Wireframes_Calc_4_5__VerticesManager__) */

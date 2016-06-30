//
//  FaceVertices.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/24/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__FaceVertices__
#define __Wireframes_Calc_4_5__FaceVertices__

#include <vector>
#include "basicshapes.h"

class Polyhedron;
class FaceVertices
{
private:
    const Polyhedron* poly;
    std::vector<int> faceVertices;
public:
    FaceVertices(const Polyhedron* p,const std::vector<int>& fv);
    Point getVertexValue(int index) const;
    int verticesNum() const;
};

#endif /* defined(__Wireframes_Calc_4_5__FaceVertices__) */

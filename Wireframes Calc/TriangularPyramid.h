//
//  TriangularPyramid.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/10/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__TriangularPyramid__
#define __Wireframes_Calc_4_5__TriangularPyramid__

#include "Polyhedron.h"

class TriangularPyramid:public Polyhedron
{
private:
    static const int vertexNum=4;
    
    virtual TriangularPyramid* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    TriangularPyramid();
    TriangularPyramid(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4_5__TriangularPyramid__) */

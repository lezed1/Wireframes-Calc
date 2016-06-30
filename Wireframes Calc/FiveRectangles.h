//
//  FiveRectangles.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/13/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__FiveRectangles__
#define __Wireframes_Calc_4_5__FiveRectangles__

#include "Polyhedron.h"

class FiveRectangles:public Polyhedron
{
private:
    static const int vertexNum=20;
    
    virtual FiveRectangles* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    FiveRectangles();
    FiveRectangles(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4_5__FiveRectangles__) */

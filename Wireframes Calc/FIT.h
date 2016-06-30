//
//  FIT.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/29/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__FIT__
#define __Wireframes_Calc_4_5__FIT__

#include "Polyhedron.h"

class FIT:public Polyhedron
{
private:
    static const int vertexNum=20;
    
    virtual FIT* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    FIT();
    FIT(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4_5__FIT__) */

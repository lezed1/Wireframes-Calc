//
//  TwoTrapezoids.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/27/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__TwoTrapezoids__
#define __Wireframes_Calc_4_5__TwoTrapezoids__

#include "Polyhedron.h"

class TwoTrapezoids:public Polyhedron
{
private:
    static const int vertexNum=8;
    
    virtual TwoTrapezoids* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    TwoTrapezoids();
    TwoTrapezoids(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4_5__TwoTrapezoids__) */

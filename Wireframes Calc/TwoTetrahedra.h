//
//  TwoTetrahedra.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/9/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__TwoTetrahedra__
#define __Wireframes_Calc_4__TwoTetrahedra__

#include "Polyhedron.h"

class TwoTetrahedra:public Polyhedron
{
private:
    static const int vertexNum=8;
    
    virtual TwoTetrahedra* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    TwoTetrahedra();
    TwoTetrahedra(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4__TwoTetrahedra__) */

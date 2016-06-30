//
//  RhombicHexahedron.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/26/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__RhombicHexahedron__
#define __Wireframes_Calc_4_5__RhombicHexahedron__

#include "Polyhedron.h"

class RhombicHexahedron:public Polyhedron
{
private:
    static const int vertexNum=8;
    
    virtual RhombicHexahedron* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    RhombicHexahedron();
    RhombicHexahedron(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4_5__RhombicHexahedron__) */

//
//  RhombicPentahedron.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/8/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__RhombicPentahedron__
#define __Wireframes_Calc_4_5__RhombicPentahedron__

#include "Polyhedron.h"

class RhombicPentahedron:public Polyhedron
{
private:
    static const int vertexNum=7;
    
    virtual RhombicPentahedron* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    void scaleToOne();
    void scaleTo(double scaleto);
    
    void initStructure();
    void initAtts();
public:
    RhombicPentahedron();
    RhombicPentahedron(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4_5__RhombicPentahedron__) */

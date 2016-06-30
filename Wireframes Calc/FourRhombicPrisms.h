//
//  FourRhombicPrisms.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 7/18/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__FourRhombicPrisms__
#define __Wireframes_Calc_4_5__FourRhombicPrisms__

#include "Polyhedron.h"

class FourRhombicPrisms:public Polyhedron
{
private:
    static const int vertexNum=32;
    
    virtual FourRhombicPrisms* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    FourRhombicPrisms();
    FourRhombicPrisms(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4_5__FourRhombicPrisms__) */

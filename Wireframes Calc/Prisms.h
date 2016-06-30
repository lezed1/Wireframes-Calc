//
//  Prisms.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/26/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Prisms__
#define __Wireframes_Calc_4__Prisms__

#include "Polyhedron.h"

class RectPrism:public Polyhedron
{
private:
    static const int vertexNum=8;
    
    virtual RectPrism* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    RectPrism();
    RectPrism(double xrot,double yrot,double zrot);
};
#endif /* defined(__Wireframes_Calc_4__Prisms__) */

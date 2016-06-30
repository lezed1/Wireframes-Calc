//
//  Icosahedron.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/10/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__Icosahedron__
#define __Wireframes_Calc_4_5__Icosahedron__

#include "Polyhedron.h"

class Icosahedron:public Polyhedron
{
private:
    static const int vertexNum=12;
    
    virtual Icosahedron* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    Icosahedron();
    Icosahedron(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4_5__Icosahedron__) */

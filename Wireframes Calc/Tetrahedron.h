//
//  Tetrahedron.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/4/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Tetrahedron__
#define __Wireframes_Calc_4__Tetrahedron__

#include "Polyhedron.h"

class Tetrahedron:public Polyhedron
{
private:
    static const int vertexNum=4;
    
    virtual Tetrahedron* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    Tetrahedron();
    Tetrahedron(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4__Tetrahedron__) */

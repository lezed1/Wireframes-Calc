//
//  Octahedron.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/11/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__Octahedron__
#define __Wireframes_Calc_4_5__Octahedron__

#include "Polyhedron.h"

class Octahedron:public Polyhedron
{
private:
    static const int vertexNum=6;
    
    virtual Octahedron* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    Octahedron();
    Octahedron(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4_5__Octahedron__) */

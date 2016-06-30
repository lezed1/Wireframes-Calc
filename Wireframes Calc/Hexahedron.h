//
//  Hexahedron.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/30/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Hexahedron__
#define __Wireframes_Calc_4__Hexahedron__

#include "Polyhedron.h"

class Hexahedron:public Polyhedron
{
private:
    static const int vertexNum=8;
    
    virtual Hexahedron* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    Hexahedron();
    Hexahedron(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4__Hexahedron__) */

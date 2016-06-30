//
//  AlecShape.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/19/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__AlecShape__
#define __Wireframes_Calc_4_5__AlecShape__

#include "Polyhedron.h"

class AlecShape:public Polyhedron
{
private:
    static const int vertexNum=12;
    
    virtual AlecShape* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    AlecShape();
    AlecShape(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4_5__AlecShape__) */

//
//  Bilunabirotunda.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/25/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Bilunabirotunda__
#define __Wireframes_Calc_4__Bilunabirotunda__

#include "Polyhedron.h"

class Bilunabirotunda:public Polyhedron
{
private:
    static const int vertexNum=14;
    
    virtual Bilunabirotunda* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    Bilunabirotunda();
    Bilunabirotunda(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4__Bilunabirotunda__) */

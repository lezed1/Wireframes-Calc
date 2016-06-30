//
//  Pentagon.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/20/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__Pentagon__
#define __Wireframes_Calc_4_5__Pentagon__


#include "Polyhedron.h"

class Pentagon:public Polyhedron
{
private:
    static const int vertexNum=5;
    
    virtual Pentagon* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    void scaleToOne();
    void scaleTo(double scaleto);
    
    void initStructure();
    void initAtts();
public:
    Pentagon();
    Pentagon(double xrot,double yrot,double zrot);
};


#endif /* defined(__Wireframes_Calc_4_5__Pentagon__) */

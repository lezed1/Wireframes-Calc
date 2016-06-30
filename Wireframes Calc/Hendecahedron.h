//
//  Hendecahedron.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 1/1/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__Hendecahedron__
#define __Wireframes_Calc_4_5__Hendecahedron__


#include "Polyhedron.h"

class Hendecahedron:public Polyhedron
{
private:
    static const int vertexNum=12;
    
    virtual Hendecahedron* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
    
    Point planarize(const Point& plane1,const Point& plane2,const Point& plane3,const Vector& lineVector,const Point& lineStart) const;
public:
    Hendecahedron();
    Hendecahedron(double xrot,double yrot,double zrot);
};


#endif /* defined(__Wireframes_Calc_4_5__Hendecahedron__) */

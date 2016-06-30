//
//  HexagonalTetrahedron.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/24/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__HexagonalTetrahedron__
#define __Wireframes_Calc_4_5__HexagonalTetrahedron__

#include "Polyhedron.h"

class HexagonalTetrahedron:public Polyhedron
{
private:
    static const int vertexNum=10;
    
    virtual HexagonalTetrahedron* doClone() const;
    virtual void setVertexValues();
    virtual void setFaceAttributes();
    
    void initStructure();
    void initAtts();
public:
    HexagonalTetrahedron();
    HexagonalTetrahedron(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4_5__HexagonalTetrahedron__) */

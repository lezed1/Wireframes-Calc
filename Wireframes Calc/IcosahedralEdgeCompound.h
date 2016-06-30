//
//  IcosahedralEdgeCompound.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/19/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__IcosahedralEdgeCompound__
#define __Wireframes_Calc_4_5__IcosahedralEdgeCompound__

#include "Compound.h"

class Polyhedron;
class Matrix3x3;
class Line;
class IcosahedralEdgeCompound:public Compound
{
public:
    IcosahedralEdgeCompound(const Polyhedron& polyhedron,double radius,double twist);
    Matrix3x3 getEdgeBasis(const Line& l1,double twist) const;
};

#endif /* defined(__Wireframes_Calc_4_5__IcosahedralEdgeCompound__) */

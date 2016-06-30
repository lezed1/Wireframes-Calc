//
//  TetrahedralCompound.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/29/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__TetrahedralCompound__
#define __Wireframes_Calc_4_5__TetrahedralCompound__

#include "Compound.h"

class Polyhedron;
class TetrahedralCompound:public Compound
{
public:
    TetrahedralCompound(const Polyhedron& polyhedron,double radius,double twist);
};

#endif /* defined(__Wireframes_Calc_4_5__TetrahedralCompound__) */

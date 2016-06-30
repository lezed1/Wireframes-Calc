//
//  OctahedralCompound.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/11/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__OctahedralCompound__
#define __Wireframes_Calc_4_5__OctahedralCompound__

#include "Compound.h"

class Polyhedron;
class OctahedralCompound:public Compound
{
public:
    OctahedralCompound(const Polyhedron& polyhedron,double radius,double twist);
};

#endif /* defined(__Wireframes_Calc_4_5__OctahedralCompound__) */

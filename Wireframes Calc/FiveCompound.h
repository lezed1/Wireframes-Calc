//
//  FiveCompound.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/29/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__FiveCompound__
#define __Wireframes_Calc_4__FiveCompound__

#include "Compound.h"

class Polyhedron;
class FiveCompound:public Compound
{
public:
    FiveCompound(const Polyhedron& polyhedron);
};

#endif /* defined(__Wireframes_Calc_4__FiveCompound__) */

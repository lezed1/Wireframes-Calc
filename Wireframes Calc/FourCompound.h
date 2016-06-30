//
//  FourCompound.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/4/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__FourCompound__
#define __Wireframes_Calc_4__FourCompound__

#include "Compound.h"

class Polyhedron;
class FourCompound:public Compound
{
public:
    FourCompound(const Polyhedron& polyhedron);
};

#endif /* defined(__Wireframes_Calc_4__FourCompound__) */

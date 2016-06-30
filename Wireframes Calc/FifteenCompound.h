//
//  FifteenCompound.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/30/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__FifteenCompound__
#define __Wireframes_Calc_4__FifteenCompound__


#include "Compound.h"

class Polyhedron;
class FifteenCompound:public Compound
{
public:
    FifteenCompound(const Polyhedron& polyhedron);
};

#endif /* defined(__Wireframes_Calc_4__FifteenCompound__) */

//
//  ThreeCompound.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/4/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "ThreeCompound.h"
#include "Polyhedron.h"

ThreeCompound::ThreeCompound(const Polyhedron& polyhedron):Compound(polyhedron,3)
{
    poly.at(0)->setRotation(0,0,0);
    poly.at(1)->setRotation(90,0,90);
    poly.at(2)->setRotation(90,90,0);
}
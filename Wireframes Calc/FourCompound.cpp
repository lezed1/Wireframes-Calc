//
//  FourCompound.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/4/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "FourCompound.h"
#include "Polyhedron.h"

FourCompound::FourCompound(const Polyhedron& polyhedron):Compound(polyhedron,4)
{
    double thirtyFive=35.264389689;
    
    poly.at(0)->setRotation(30,thirtyFive,45);
    poly.at(1)->setRotation(-30,-thirtyFive,45);
    poly.at(2)->setRotation(30,thirtyFive,-45);
    poly.at(3)->setRotation(-30,-thirtyFive,-45);
}
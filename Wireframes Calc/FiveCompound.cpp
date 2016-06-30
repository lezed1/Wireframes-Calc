//
//  FiveCompound.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/29/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include "FiveCompound.h"
#include "Polyhedron.h"

FiveCompound::FiveCompound(const Polyhedron& polyhedron):Compound(polyhedron,5)
{
    double sixtyNine=69.094842554;
    double twentyOne=20.905157447;
    
    poly.at(0)->setRotation(0,0,0);
    poly.at(1)->setRotation(sixtyNine,30,twentyOne);
    poly.at(2)->setRotation(-sixtyNine,30,-twentyOne);
    poly.at(3)->setRotation(-sixtyNine,-30,twentyOne);
    poly.at(4)->setRotation(sixtyNine,-30,-twentyOne);
}
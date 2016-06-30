//
//  SixCompound.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/4/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "SixCompound.h"
#include "Polyhedron.h"

SixCompound::SixCompound(const Polyhedron& polyhedron):Compound(polyhedron,6)
{
    double thirtyOne=31.717474411;
    double fiftyEight=58.282525589;
    
    poly.at(0)->setRotation(-18,thirtyOne,0);
    poly.at(1)->setRotation(18,-thirtyOne,0);
    poly.at(2)->setRotation(-36,0,fiftyEight);
    poly.at(3)->setRotation(0,0,-fiftyEight);
    poly.at(4)->setRotation(18,fiftyEight,-90);
    poly.at(5)->setRotation(18,fiftyEight,90);
}

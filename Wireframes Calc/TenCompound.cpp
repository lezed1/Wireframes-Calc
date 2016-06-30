//
//  TenCompound.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/4/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "TenCompound.h"
#include "Polyhedron.h"

TenCompound::TenCompound(const Polyhedron& polyhedron):Compound(polyhedron,10)
{
    double twentyOne=20.905157447;
    double sixtyNine=69.094842554;
    double seven=7.761243904;
    double fiftyTwo=52.238756096;
    double thrityFive=35.264389689;
    
    poly.at(0)->setRotation(0,0,-twentyOne);
    poly.at(1)->setRotation(60,0,twentyOne);
    poly.at(2)->setRotation(30,sixtyNine,0);
    poly.at(3)->setRotation(90,-sixtyNine,0);
    poly.at(4)->setRotation(90,twentyOne,90);
    poly.at(5)->setRotation(30,-twentyOne,90);
    poly.at(6)->setRotation(seven,thrityFive,45);
    poly.at(7)->setRotation(fiftyTwo,thrityFive,-45);
    poly.at(8)->setRotation(-seven,-thrityFive,45);
    poly.at(9)->setRotation(-fiftyTwo,-thrityFive,-45);
}

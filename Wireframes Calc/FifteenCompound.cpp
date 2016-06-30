//
//  FifteenCompound.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/30/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include "FifteenCompound.h"
#include "Polyhedron.h"
#include "basicshapes.h"

FifteenCompound::FifteenCompound(const Polyhedron& polyhedron):Compound(polyhedron,15)
{
    Point newrot1(90,0,90);
    Point newrot2(90,90,0);
    
    double sixtyNine=69.094842554;
    double twentyOne=20.905157447;
    
    poly.at(0)->setRotation(0,0,0);
    poly.at(1)->setRotation(sixtyNine,30,twentyOne);
    poly.at(2)->setRotation(-sixtyNine,30,-twentyOne);
    poly.at(3)->setRotation(-sixtyNine,-30,twentyOne);
    poly.at(4)->setRotation(sixtyNine,-30,-twentyOne);
    
    poly.at(5)->setRotation(0,0,0);
    poly.at(5)->addRotation(newrot1);
    poly.at(6)->setRotation(sixtyNine,30,twentyOne);
    poly.at(6)->addRotation(newrot1);
    poly.at(7)->setRotation(-sixtyNine,30,-twentyOne);
    poly.at(7)->addRotation(newrot1);
    poly.at(8)->setRotation(-sixtyNine,-30,twentyOne);
    poly.at(8)->addRotation(newrot1);
    poly.at(9)->setRotation(sixtyNine,-30,-twentyOne);
    poly.at(9)->addRotation(newrot1);
    
    poly.at(10)->setRotation(0,0,0);
    poly.at(10)->addRotation(newrot2);
    poly.at(11)->setRotation(sixtyNine,30,twentyOne);
    poly.at(11)->addRotation(newrot2);
    poly.at(12)->setRotation(-sixtyNine,30,-twentyOne);
    poly.at(12)->addRotation(newrot2);
    poly.at(13)->setRotation(-sixtyNine,-30,twentyOne);
    poly.at(13)->addRotation(newrot2);
    poly.at(14)->setRotation(sixtyNine,-30,-twentyOne);
    poly.at(14)->addRotation(newrot2);
}
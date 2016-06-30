//
//  Attribute.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/26/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include <iostream>
#include "Attribute.h"
#include "Utilities.h"

Attribute::Attribute(double cv,double lb,double ub,double inc)
{
    currentValue=cv;
    attLowerBound=lb;
    attUpperBound=ub;
    increment=inc;
}

double Attribute::getUpperBound() const
{
    return attUpperBound;
}
double Attribute::getLowerBound() const
{
    return attLowerBound;
}
double Attribute::getIncrement() const
{
    return increment;
}
double Attribute::getCurrentValue() const
{
    return currentValue;
}
std::string Attribute::currentValueString() const
{
    return doubleToString(currentValue);
}

void Attribute::setCurrentValue(double cv)
{
    if (cv<attLowerBound) {currentValue=attLowerBound; return;}
    if (cv>attUpperBound) {currentValue=attUpperBound; return;}
    currentValue=cv;
}
void Attribute::setBounds(double upper, double lower)
{
    attUpperBound=upper;
    attLowerBound=lower;
}

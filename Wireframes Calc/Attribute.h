//
//  Attribute.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/26/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Attribute__
#define __Wireframes_Calc_4__Attribute__

#include <string>

class Attribute
{ //defines a polyhedron attribute
private:
    double attUpperBound; //value attribute can't exceed
    double increment; //value attribute can increase/decrease by at once
    double attLowerBound; //value attribute can't be lower than
    double currentValue; //current value the attribute takes on
public:
    Attribute(double cv,double lb,double ub,double inc);
    
    double getUpperBound()   const; //return upper bound
    double getLowerBound()   const; //return lower bound
    double getIncrement()    const; //return increment
    double getCurrentValue() const; //return the currentValue
    std::string currentValueString() const;
    
    void setCurrentValue(double cv); //set the attribute's value
    void setBounds(double upper,double lower); //sets attribute's upper and lower bounds
};

#endif /* defined(__Wireframes_Calc_4__Attribute__) */

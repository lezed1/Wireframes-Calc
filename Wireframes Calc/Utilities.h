//
//  Utilities.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 11/23/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Utilities__
#define __Wireframes_Calc_4__Utilities__

#include <iostream>
#include <vector>

class Line;
std::string doubleToString(double d);
std::string intToString(int i);
double segmentSegmentDist(const Line& line1,const Line& line2);
double sgn(double x);
double positiveDifference(double x,double y);
double radians(double deg);
double degrees(double rad);

#endif /* defined(__Wireframes_Calc_4__Utilities__) */

//
//  Line2D.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/25/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__Line2D__
#define __Wireframes_Calc_4_5__Line2D__

#include "basicshapes.h"

class Line2D
{
private:
    double m;
    double b;
public:
    Line2D(const Point& p1,const Point& p2);
    Line2D(double mm,double bb);
    double getSlope() const;
    double getYIntercept() const;
    static Point intersection(const Line2D& l1,const Line2D& l2);
    bool isPointAboveOrOnLine(const Point& p);
    bool isPointBelowOrOnLine(const Point& p);
    
    std::string toString();
};

#endif /* defined(__Wireframes_Calc_4_5__Line2D__) */

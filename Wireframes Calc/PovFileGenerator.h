//
//  PovFileGenerator.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 11/26/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__PovFileGenerator__
#define __Wireframes_Calc_4__PovFileGenerator__

#include <string>
#include <vector>

#include "basicshapes.h"

std::string povRaySphere(const Point& p,double thick,const std::string& color);
std::string povRaySphere(double x,double y,double z, double thick,const std::string& color);

std::string povRayCylinder(const Point& p1,const Point&p2, double thick,const std::string& color);
std::string povRayCylinder(const Line& l, double thick,const std::string& color);
std::string povRayTriangle(const Triangle& tri,const std::string& color);

std::string povRayTriangleList(const std::vector<Triangle>& list,const std::string& color);

#endif /* defined(__Wireframes_Calc_4__PovFileGenerator__) */

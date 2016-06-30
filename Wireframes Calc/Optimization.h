//
//  Optimization.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/3/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Optimization__
#define __Wireframes_Calc_4__Optimization__

typedef std::tuple<int,int,int,int> EdgeID;

class Polyhedron;
class Compound;

double computeCompoundWidth(const Compound& compound,double edgeDistCheckFactor=2.0);
double computeEdgePairWidth(const Polyhedron* p1,const Polyhedron* p2,int e1,int e2,double lowerBound,double upperBound);

#endif /* defined(__Wireframes_Calc_4__Optimization__) */

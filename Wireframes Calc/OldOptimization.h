//
//  OldOptimization.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/30/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__OldOptimization__
#define __Wireframes_Calc_4_5__OldOptimization__

#include <vector>

typedef std::tuple<int,int,int,int> EdgeID;

class Frame;
class FrameEdge;
class Polyhedron;
class Compound;

double computeCompoundWidthOld(const Compound& compound);
std::vector<EdgeID> getListOfIntersections(const std::vector<Frame>& frames);
int areIntersectionsInList(const std::vector<Frame>& frames,const std::vector<EdgeID>& ilist,int start);
bool doFramesIntersect(const std::vector<Frame>& frames);

#endif /* defined(__Wireframes_Calc_4_5__OldOptimization__) */

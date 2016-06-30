//
//  TTIntersection.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/3/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__TTIntersection__
#define __Wireframes_Calc_4__TTIntersection__

class Triangle;

int NoDivTriTriIsect(float V0[3],float V1[3],float V2[3],
                     float U0[3],float U1[3],float U2[3]);
int coplanar_tri_tri(float N[3],float V0[3],float V1[3],float V2[3],
                     float U0[3],float U1[3],float U2[3]);
bool doTrianglesIntersect(const Triangle& t1,const Triangle& t2);

#endif /* defined(__Wireframes_Calc_4__TTIntersection__) */

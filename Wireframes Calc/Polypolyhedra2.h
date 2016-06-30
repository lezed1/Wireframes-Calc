//
//  Polypolyhedra2.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/22/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__Polypolyhedra2__
#define __Wireframes_Calc_4_5__Polypolyhedra2__

#include <vector>
#include "basicshapes.h"
#include "Compound.h"

enum PolypolyOutput {CrossSection2D,PovRay,UnitInfo};

void polypolyhedron(const Compound* compound,const std::vector<std::string>& colors,bool symmetrize,int v1,int v2,int v3,PolypolyOutput output);
void polypolyhedronUnit(const Compound* compound,int edge,int frame,const std::string& color,bool symmetrize,int v1,int v2,int v3,PolypolyOutput output);

void polypolyhedraCode();

#endif /* defined(__Wireframes_Calc_4_5__Polypolyhedra2__) */

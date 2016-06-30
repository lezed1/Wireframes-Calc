//
//  Compound.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/29/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__Compound__
#define __Wireframes_Calc_4__Compound__

#include <vector>
#include <iostream>

class Polyhedron;
class Frame;
class Compound
{
protected:
    int polyNum;
    std::vector<std::unique_ptr<Polyhedron>> poly;
    
    Compound(const Polyhedron& poly,int pNum);
public:
    double computeWidth() const;
    
    void printPovRayFrame(double frameWidth,const std::vector<std::string>& colors) const;
    void printPovRaySkeleton(double thickness,const std::vector<std::string>& colors) const;
    Frame makeFrame(int index,double frameWidth=-1.0) const;
    void setPolyhedronAttribute(const std::string& att,double newValue);
    
    const Polyhedron* getPolyhedron(int index) const;
    double getNumberOfPolyhedra() const;
    
    virtual ~Compound();
};

#endif /* defined(__Wireframes_Calc_4__Compound__) */

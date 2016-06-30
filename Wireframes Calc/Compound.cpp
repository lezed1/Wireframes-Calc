//
//  Compound.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/29/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//


#include <cmath>

#include "Compound.h"
#include "Polyhedron.h"
#include "Utilities.h"

#include "Frame.h"

Compound::Compound(const Polyhedron& polyhedron,int pNum):polyNum(pNum)
{
    poly.reserve(pNum);
    for (int i=0;i<pNum;i++)
    {
        poly.push_back( std::unique_ptr<Polyhedron>(polyhedron.clone()) );
    }
}
void Compound::printPovRayFrame(double frameWidth,const std::vector<std::string>& colors, std::ostream& ostream) const
{
    int colorsSize=(int) colors.size();
    for (int i=0;i<poly.size();i++)
    {
        int colorIndex=i%colorsSize;
        poly.at(i)->printPovRayFrame(frameWidth, colors.at(colorIndex), ostream);
        //poly.at(i)->makeFrame(frameWidth).printPovRay(colors.at(colorIndex));
    }
}
void Compound::printPovRaySkeleton(double thickness,const std::vector<std::string>& colors, std::ostream& ostream) const
{
    int colorsSize=(int) colors.size();
    for (int i=0;i<poly.size();i++)
    {
        int colorIndex=i%colorsSize;
        poly.at(i)->printPovRaySkeleton(thickness, colors.at(colorIndex), ostream);
        //poly.at(i)->makeFrame(frameWidth).printPovRay(colors.at(colorIndex));
    }
}
Frame Compound::makeFrame(int index,double frameWidth) const
{
    return poly.at(index)->makeFrame(frameWidth);
}

void Compound::setPolyhedronAttribute(const std::string& att,double newValue)
{
    for (int i=0;i<polyNum;i++)
    {
        poly.at(i)->setAttribute(att, newValue);
    }
}

const Polyhedron* Compound::getPolyhedron(int index) const
{
    return poly.at(index).get();
}
double Compound::getNumberOfPolyhedra() const
{
    return polyNum;
}
Compound::~Compound()
{
    
}


double Compound::computeWidth() const
{
//    double distance=1000;
//    int edgenum=poly.at(0)->getEdgeNum();
//    for (int n=0;n<edgenum;n++)
//    {
//        for (int m=0;m<edgenum;m++)
//        {
//            for (int i=0;i<polyNum;i++)
//            {
//                for (int j=i+1;j<polyNum;j++)
//                {
//                    double checkDist=segmentSegmentDist(poly.at(i)->getEdgeLine(n), poly.at(j)->getEdgeLine(m));
//                    /*if (i==0 && j==2 && n==0 && m==0)
//                    {
//                        std::cout << checkDist << "\n";
//                    }*/
//                    if (checkDist<distance)
//                    {
//                        distance=checkDist;
//                    }
//                    //distance=fmin(distance,checkDist);
//                }
//            }
//        }
//    }
    
    int polyNum=getNumberOfPolyhedra();
    std::vector<Frame> frames;
    for (int i=0;i<polyNum;i++)
    {
        frames.push_back(makeFrame(i));
    }
    
    int edgeNum=frames.at(0).getEdgeNum();
    double distance=100000.0;
    for (int i=0;i<polyNum;i++)
    {
        for (int j=i+1;j<polyNum;j++)
        {
            for (int k=0;k<edgeNum;k++)
            {
                for (int m=0;m<edgeNum;m++)
                {
                    double edgeDist=segmentSegmentDist(frames.at(i).getFrameEdges()->at(k).getLine(),frames.at(j).getFrameEdges()->at(m).getLine());
                    //edgeDistances.push_back(edgeDist);
                    if (edgeDist<distance)
                    {
                        distance=edgeDist;
                    }
                }
            }
        }
    }
    return distance/2;
}



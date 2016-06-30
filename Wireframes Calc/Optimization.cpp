//
//  Optimization.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 1/3/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include <vector>
#include <ctime>
#include <cmath>

#include "Optimization.h"
#include "Compound.h"
#include "Frame.h"
#include "Utilities.h"
#include "Polyhedron.h"

double computeCompoundWidth(const Compound& compound,double edgeDistCheckFactor)
{
    //clock_t count=0;
    
    int polyNum=compound.getNumberOfPolyhedra();
    std::vector<Frame> frames;
    for (int i=0;i<polyNum;i++)
    {
        frames.push_back(compound.makeFrame(i));
    }
    int edgeNum=frames.at(0).getEdgeNum();
    double upperBound=frames.at(0).getFrameWidth();
    double lowerBound=0.0;
    
    //clock_t t;
    //t = clock();
    //cache edge-edge distances and use the smallest pair to calculate an upper bound on the frame width
    double smallestDist=100000.0;
    EdgeID smallestDistPair={0,0,0,0};
    std::vector<double> edgeDistances;
    for (int i=0;i<polyNum;i++)
    {
        for (int j=i+1;j<polyNum;j++)
        {
            for (int k=0;k<edgeNum;k++)
            {
                for (int m=0;m<edgeNum;m++)
                {
                    double edgeDist=segmentSegmentDist(frames.at(i).getFrameEdges()->at(k).getLine(),frames.at(j).getFrameEdges()->at(m).getLine());
                    edgeDistances.push_back(edgeDist);
                    if (edgeDist<smallestDist)
                    {
                        smallestDist=edgeDist;
                        smallestDistPair={i,j,k,m};
                    }
                }
            }
        }
    }
    //t = clock() - t;
    //count+=t;
    
    //clock_t t;
    //t = clock();
    int f1=std::get<0>(smallestDistPair);
    int f2=std::get<1>(smallestDistPair);
    int e1=std::get<2>(smallestDistPair);
    int e2=std::get<3>(smallestDistPair);
    double newUpperBound=computeEdgePairWidth(compound.getPolyhedron(f1),compound.getPolyhedron(f2),e1,e2,lowerBound,upperBound);
    if (newUpperBound<upperBound) {upperBound=newUpperBound;}
    lowerBound=smallestDist/2.0;
    //t = clock() - t;
    //count+=t;
    
    int index=-1;
    double currentFrameWidth=upperBound;
    for (int i=0;i<polyNum;i++)
    {
        for (int j=i+1;j<polyNum;j++)
        {
            for (int k=0;k<edgeNum;k++)
            {
                for (int m=0;m<edgeNum;m++)
                {
                    //clock_t t;
                    //t = clock();
                    index++;
                    double edgeDist=edgeDistances.at(index);
                    if (edgeDist>upperBound*edgeDistCheckFactor) //edgeDistCheckFactor is usually 2.0
                    {
                        continue;
                    }

                    if (!FrameEdge::doFrameEdgesIntersect(frames.at(i).getFrameEdges()->at(k), frames.at(j).getFrameEdges()->at(m)))
                    {
                        continue;
                    }
                    //t = clock() - t;
                    //count+=t;
                    
                    //clock_t t;
                    //t = clock();
                    upperBound=computeEdgePairWidth(compound.getPolyhedron(i),compound.getPolyhedron(j),k,m,lowerBound,upperBound);
                    //t = clock() - t;
                    //count+=t;
                    
                    //clock_t t;
                    //t = clock();
                    if (upperBound!=currentFrameWidth)
                    {
                        currentFrameWidth=upperBound;
                        for (int i=0;i<polyNum;i++)
                        {
                            frames.at(i)=compound.makeFrame(i,upperBound);
                        }
                    }
                    //t = clock() - t;
                    //count+=t;
                }
            }
        }
    }
    //printf ("\nIt took me %lu clicks (%f seconds).\n",count,((float)count)/CLOCKS_PER_SEC);
    return currentFrameWidth;
}

double computeEdgePairWidth(const Polyhedron* p1,const Polyhedron* p2,int e1,int e2,double lowerBound,double upperBound)
{
    int numberOfIterations=20;
    for (int i=0;i<numberOfIterations;i++) //binary search real numbers for optimal width
        //increase numOfIterations for greater accuracy
    {
        double check=(upperBound+lowerBound)/2.0;
        FrameEdge fe1=p1->makeFrameEdge(e1,check);
        FrameEdge fe2=p2->makeFrameEdge(e2,check);
        bool isect=FrameEdge::doFrameEdgesIntersect(fe1, fe2);
        if (!isect) //frames don't intersect, check too low
        {
            lowerBound=check;
        }
        else //frames do intersect, check too high
        {
            upperBound=check;
        }
    }
    return (upperBound+lowerBound)/2.0;
}
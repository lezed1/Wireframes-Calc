//
//  OldOptimization.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/30/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include <vector>
#include <ctime>

#include "OldOptimization.h"
#include "Compound.h"
#include "Frame.h"
#include "Utilities.h"
#include "Polyhedron.h"

bool doFramesIntersect(const std::vector<Frame>& frames)
{
    int frameNum=(int) frames.size();
    double frameWidth=frames.at(0).getFrameWidth();
    for (int i=0;i<frameNum;i++)
    {
        for (int j=i+1;j<frameNum;j++)
        {
            const std::vector<FrameEdge>* t1=frames.at(i).getFrameEdges();
            const std::vector<FrameEdge>* t2=frames.at(j).getFrameEdges();
            for (int k=0;k<t1->size();k++)
            {
                for (int m=0;m<t2->size();m++)
                {
                    double edgeDist=segmentSegmentDist(t1->at(k).getLine(), t2->at(m).getLine());
                    if (edgeDist>frameWidth*2.0)
                    {
                        continue;
                    }
                    bool isect=FrameEdge::doFrameEdgesIntersect(t1->at(k), t2->at(m));
                    if (isect)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

std::vector<EdgeID> getListOfIntersections(const std::vector<Frame>& frames)
{
    std::vector<EdgeID> intersections;
    double frameWidth=frames.at(0).getFrameWidth();
    int polyNum=(int) frames.size();
    for (int i=0;i<polyNum;i++)
    {
        for (int j=i+1;j<polyNum;j++)
        {
            const std::vector<FrameEdge>* t1=frames.at(i).getFrameEdges();
            const std::vector<FrameEdge>* t2=frames.at(j).getFrameEdges();
            for (int k=0;k<t1->size();k++)
            {
                for (int m=0;m<t2->size();m++)
                {
                    double edgeDist=segmentSegmentDist(t1->at(k).getLine(), t2->at(m).getLine());
                    if (edgeDist<frameWidth*2.0)
                    {
                        bool isect=FrameEdge::doFrameEdgesIntersect(t1->at(k),t2->at(m));
                        if (isect)
                        {
                            intersections.push_back({i,j,k,m});
                        }
                    }
                }
            }
        }
    }
    return intersections;
}

int areIntersectionsInList(const std::vector<Frame>& frames,const std::vector<EdgeID>& ilist,int start)
{ //returns position of first intersection found, -1 if no intersections
    int size=(int) ilist.size();
    for (int i=start;i<size;i++)
    {
        EdgeID intersectionToCheck=ilist.at(i);
        int frame1=std::get<0>(intersectionToCheck);
        int frame2=std::get<1>(intersectionToCheck);
        int edge1=std::get<2>(intersectionToCheck);
        int edge2=std::get<3>(intersectionToCheck);
        bool isect=FrameEdge::doFrameEdgesIntersect(frames.at(frame1).getFrameEdges()->at(edge1), frames.at(frame2).getFrameEdges()->at(edge2));
        if (isect)
        {
            return i;
        }
    }
    return -1;
}


double computeCompoundWidthOld(const Compound& compound)
{
    int polyNum=compound.getNumberOfPolyhedra();
    std::vector<Frame> frames;
    frames.reserve(polyNum);
    for (int i=0;i<polyNum;i++)
    {
        frames.push_back(compound.makeFrame(i));
    }
    
    double lowerWidth=frames.at(0).getFrameWidth();
    
    bool areIntersections=true;
    do //find lower bound for width
    {
        areIntersections=doFramesIntersect(frames);
        if (areIntersections)
        {
            lowerWidth/=2.0;
            for (int i=0;i<polyNum;i++)
            {
                frames.at(i)=compound.makeFrame(i,lowerWidth);
            }
        }
    }
    while (areIntersections);
    
    double upperWidth=lowerWidth*2.0; //guaranteed to have intersections, otherwise it would have ended the loop
    for (int i=0;i<polyNum;i++)
    {
        frames.at(i)=compound.makeFrame(i,upperWidth);
    }
    
    //compute list of intersecting FrameEdges
    std::vector<EdgeID> intersections=getListOfIntersections(frames);
    int searchStart=0;
    
    int numberOfIterations=20;
    
    for (int i=0;i<numberOfIterations;i++) //binary search real numbers for optimal width
        //increase numOfIterations for greater accuracy
    {
        double check=(upperWidth+lowerWidth)/2.0;
        for (int i=0;i<polyNum;i++)
        {
            frames.at(i)=compound.makeFrame(i,check);
        }
        int isect=areIntersectionsInList(frames, intersections, searchStart);
        if (isect<0) //frames don't intersect, check too low
        {
            lowerWidth=check;
        }
        else //frames do intersect, check too high
        {
            upperWidth=check;
            searchStart=isect;
        }
    }
    
    return (upperWidth+lowerWidth)/2.0;
}

//
//  DihedralFace.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 12/24/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>

#include "DihedralFace.h"
#include "Vertex.h"
#include "Utilities.h"
#include "FaceVertices.h"

DihedralFace::DihedralFace(const EdgeVector& e,const FaceVertices& pr):FramedFace(e,pr)
{
    attributes["dihedral"]=0.0;
    attributes["uorl"]=1.0;
}
std::vector<Triangle> DihedralFace::generateTriangles(double frameWidth)
{    
    double dihedral=attributes.at("dihedral");
    generateInnerPoints(frameWidth*cos(dihedral*M_PI/180));
    addDihedral(frameWidth);
    return connectInnerPoints();
}
std::vector<std::pair<Triangle, int>> DihedralFace::do_generateTriangleEdgePairs(double frameWidth)
{
    double dihedral=attributes.at("dihedral");
    generateInnerPoints(frameWidth*cos(dihedral*M_PI/180));
    addDihedral(frameWidth);
    return makeTriangleEdgePairs(frameWidth);
}
void DihedralFace::addDihedral(double frameWidth)
{
    double dihedral=attributes.at("dihedral");
    double uorl=attributes.at("uorl");
    if (dihedral!=0) //raise/lower these inner points out of the plane of face based on dihedral
    {
        Point v1=getVertex(0);
        Point v2=getVertex(1);
        Point v3=getVertex(2);
        double a=v1.getX();
        double b=v1.getY();
        double c=v1.getZ();
        double d=v2.getX();
        double e=v2.getY();
        double f=v2.getZ();
        double g=v3.getX();
        double h=v3.getY();
        double i=v3.getZ();
        
        double na=b*(f-i)+e*(i-c)+h*(c-f);
        double nb=c*(d-g)+f*(g-a)+i*(a-d);
        double nc=a*(e-h)+d*(h-b)+g*(b-e);
        Vector normal(na,nb,nc); //vector normal to plane of face
        
        //double height=sqrt(frameWidth*frameWidth-widthh*widthh);
        double height=frameWidth*sin(dihedral*M_PI/180);
        //height*=sgn(dihedral); //make negative dihedral angle flip direction
        
        Point opoint;
        int upperOrLower;
        if (uorl>=0.0)
        {
            upperOrLower=1;
        }
        else
        {
            upperOrLower=-1;
        }
        
        int faceSize=(int) edges.size();
        for (int i=0;i<faceSize;i++)
        {
            opoint=inners.at(i)+normal;
            double dist=Point::distance(opoint, inners.at(i));
            double hfactor=height/dist;
            inners.at(i)=Point::extendLine(inners.at(i), opoint, hfactor*upperOrLower);
        }
    }
}
double DihedralFace::do_calculateMaxWidth() const
{
    double dihedral=attributes.at("dihedral");
    double maxHeight=FramedFace::do_calculateMaxWidth();
    return maxHeight/cos(dihedral*M_PI/180);
}
DihedralFace* DihedralFace::doClone()
{
    return new DihedralFace(*this);
}
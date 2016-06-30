//
//  IcosahedralEdgeCompound.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 6/19/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>
#include <vector>
#include "IcosahedralEdgeCompound.h"
#include "Polyhedron.h"
#include "Icosahedron.h"
#include "Utilities.h"

IcosahedralEdgeCompound::IcosahedralEdgeCompound(const Polyhedron& polyhedron,double radius,double twist):Compound(polyhedron,30)
{
    Icosahedron icosahedron(0,0,0);
    int edgeNum=icosahedron.getEdgeNum();
    
    std::vector<AffineTransformation> transformations;
    for (int i=0;i<edgeNum;i++)
    {
        Line polyLine=icosahedron.getEdgeLine(i);
        Matrix3x3 rotation=getEdgeBasis(polyLine,twist);
        Point midpoint=polyLine.getMidpoint();
        Vector translation=midpoint.toVector();
        translation.normalize();
        translation*=radius;
        transformations.push_back(AffineTransformation(rotation,translation));
    }
    for (int i=0;i<edgeNum;i++)
    {
        poly.at(i)->setTransformation(transformations.at(i));
    }
    
}

Matrix3x3 IcosahedralEdgeCompound::getEdgeBasis(const Line& l1,double twist) const
{
    Point midpoint=l1.getMidpoint();
    Vector zaxis=midpoint.toVector()*-1;
    zaxis.normalize();
    Vector xaxis=l1.getVector();
    xaxis.normalize();
    Vector yaxis=Vector::cross(zaxis, xaxis);
    Matrix3x3 positioning=Matrix3x3(xaxis,yaxis,zaxis);
    
    //https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
    Vector k=zaxis;
    k.normalize();
    Matrix3x3 kMatrix(0,-k.getZ(),k.getY(),
                      k.getZ(),0,-k.getX(),
                      -k.getY(),k.getX(),0);
    Matrix3x3 twistMatrix=Matrix3x3::identityMatrix()+kMatrix*sin(radians(twist))+kMatrix*kMatrix*(1-cos(radians(twist)));
    
    return twistMatrix*positioning;
}
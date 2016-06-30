//
//  TetrahedralCompound.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/29/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>
#include "TetrahedralCompound.h"
#include "Polyhedron.h"
#include "Tetrahedron.h"
#include "Utilities.h"

TetrahedralCompound::TetrahedralCompound(const Polyhedron& polyhedron,double radius,double twist):Compound(polyhedron,4)
{
    Tetrahedron refTet(0,0,0);
    int faceNumber=refTet.getFaceNum();
    
    std::vector<Triangle> triangles;
    for (int i=0;i<faceNumber;i++)
    {
        triangles.push_back(Triangle(refTet.getFaceVertices(i)));
    }
    
    std::vector<Point> centroids;
    for (int i=0;i<faceNumber;i++)
    {
        centroids.push_back(triangles.at(i).getCentroid());
    }
    
    std::vector<Vector> xaxes;
    std::vector<Vector> yaxes;
    std::vector<Vector> zaxes;
    for (int i=0;i<faceNumber;i++)
    {
        Vector xaxis=centroids.at(i).toVector();
        Vector zaxis(triangles.at(i).getPointA(),centroids.at(i));
        Vector yaxis=Vector::cross(zaxis, xaxis); //in this order since k cross i = j for a right handed coordinate system
        
        xaxis.normalize();
        yaxis.normalize();
        zaxis.normalize();
        
        xaxes.push_back(xaxis);
        yaxes.push_back(yaxis);
        zaxes.push_back(zaxis);
    }
    
    std::vector<Matrix3x3> matrices;
    for (int i=0;i<faceNumber;i++)
    {
        Matrix3x3 poisitioning=Matrix3x3(xaxes.at(i),yaxes.at(i),zaxes.at(i));
        
        //https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
        Vector k=xaxes.at(i);
        k.normalize();
        Matrix3x3 kMatrix(0,-k.getZ(),k.getY(),
                          k.getZ(),0,-k.getX(),
                          -k.getY(),k.getX(),0);
        Matrix3x3 twistMatrix=Matrix3x3::identityMatrix()+kMatrix*sin(radians(twist))+kMatrix*kMatrix*(1-cos(radians(twist)));
        
        matrices.push_back(twistMatrix*poisitioning);
    }
    
    for (int i=0;i<faceNumber;i++)
    {
        Vector translation=centroids.at(i).toVector();
        translation.normalize();
        
        AffineTransformation at(matrices.at(i),translation*radius);
        poly.at(i)->setTransformation(at);
    }
}
//
//  AffineTransformation.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/28/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#include "AffineTransformation.h"
#include "Matrix3x3.h"
#include "basicshapes.h"

AffineTransformation::AffineTransformation():matrix(Matrix3x3::identityMatrix()),translation(Vector(0,0,0))
{
    
}
AffineTransformation::AffineTransformation(const Matrix3x3& m,const Vector& v):matrix(m),translation(v)
{
    
}
AffineTransformation::AffineTransformation(const Matrix3x3& m):matrix(m),translation(Vector(0,0,0))
{
    
}
AffineTransformation::AffineTransformation(const Vector& v):matrix(Matrix3x3::identityMatrix()),translation(v)
{
    
}

Matrix3x3 AffineTransformation::getMatrix() const
{
    return matrix;
}
Vector AffineTransformation::getTranslation() const
{
    return translation;
}

Vector AffineTransformation::transform(const Vector& v) const
{
    return matrix*v+translation;
}

Point AffineTransformation::transform(const Point& p) const
{
    return transform(p.toVector()).toPoint();
}
void AffineTransformation::compose(AffineTransformation a)
{
    //composes current affine transformation inside the new one passed as a parameter, [a(this)]
    
    //a=Ax+b2, this=Tx+b1
    //Ax+b2
    //A(Tx+b1)+b2
    //ATx+Ab1+b2=(AT)x+(Ab1+b2)
    
    Matrix3x3 newMatrix=a.getMatrix()*matrix;
    Vector newTranslation=a.getMatrix()*translation+a.getTranslation();
    
    matrix=newMatrix;
    translation=newTranslation;
}

AffineTransformation AffineTransformation::makeRotation(double xrot,double yrot,double zrot)
{
    Vector xaxis(1,0,0);
    Vector yaxis(0,1,0);
    Vector zaxis(0,0,1);
    
    xaxis.rotate(xrot, yrot, zrot);
    yaxis.rotate(xrot, yrot, zrot);
    zaxis.rotate(xrot, yrot, zrot);
    
    return AffineTransformation(Matrix3x3(xaxis,yaxis,zaxis));
}


void AffineTransformation::printMatrix() const
{
    matrix.printInfo();
}
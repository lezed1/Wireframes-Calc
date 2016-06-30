//
//  Matrix3x3.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/24/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include "Matrix3x3.h"
#include <iostream>
#include "basicshapes.h"

Matrix3x3::Matrix3x3(double aa,double bb,double cc,
                     double dd,double ee,double ff,
                     double gg,double hh,double ii)
{
    a=aa;
    b=bb;
    c=cc;
    d=dd;
    e=ee;
    f=ff;
    g=gg;
    h=hh;
    i=ii;
    
    matrixArray[0][0]=a;
    matrixArray[0][1]=b;
    matrixArray[0][2]=c;
    
    matrixArray[1][0]=d;
    matrixArray[1][1]=e;
    matrixArray[1][2]=f;
    
    matrixArray[2][0]=g;
    matrixArray[2][1]=h;
    matrixArray[2][2]=i;
}
Matrix3x3::Matrix3x3(const Vector& v1,const Vector& v2,const Vector& v3)
{
    a=v1.getX();
    b=v2.getX();
    c=v3.getX();
    d=v1.getY();
    e=v2.getY();
    f=v3.getY();
    g=v1.getZ();
    h=v2.getZ();
    i=v3.getZ();
    
    matrixArray[0][0]=a;
    matrixArray[0][1]=b;
    matrixArray[0][2]=c;
    
    matrixArray[1][0]=d;
    matrixArray[1][1]=e;
    matrixArray[1][2]=f;
    
    matrixArray[2][0]=g;
    matrixArray[2][1]=h;
    matrixArray[2][2]=i;
}

double Matrix3x3::determinant() const
{
    return a*e*i-a*f*h-b*d*i+b*f*g+c*d*h-c*e*g;
}

Matrix3x3 Matrix3x3::inverse() const
{
    double AAA=e*i-f*h;
    double BBB=-1*(d*i-f*g);
    double CCC=d*h-e*g;
    double DDD=-1*(b*i-c*h);
    double EEE=a*i-c*g;
    double FFF=-1*(a*h-b*g);
    double GGG=b*f-c*e;
    double HHH=-1*(a*f-c*d);
    double III=a*e-b*d;
    
    Matrix3x3 preInverse=Matrix3x3(AAA,DDD,GGG,BBB,EEE,HHH,CCC,FFF,III);
    
    return preInverse*(1.0/determinant());
}
double Matrix3x3::getEntry(int  i,int j) const
{
    return matrixArray[i][j];
}
Vector Matrix3x3::getColumnVector(int col) const
{
    if (col>2 || col<0)
    {
        std::cout << "Error Matrix3x3::getColumnVector: column value out of range [0-2]: " << col << "\n";
        return Vector(0,0,0);
    }
    
    double vx=matrixArray[0][col];
    double vy=matrixArray[1][col];
    double vz=matrixArray[2][col];
    
    return Vector(vx,vy,vz);
    
}
Vector Matrix3x3::getRowVector(int row) const
{
    if (row>2 || row<0)
    {
        std::cout << "Error Matrix3x3::getRowVector: row value out of range [0-2]: " << row << "\n";
        return Vector(0,0,0);
    }
    
    double vx=matrixArray[row][0];
    double vy=matrixArray[row][1];
    double vz=matrixArray[row][2];
    
    return Vector(vx,vy,vz);
}
void Matrix3x3::printInfo() const
{
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            std::cout << matrixArray[i][j] << " ";
        }
        std::cout << "\n";
    }
}
Matrix3x3 Matrix3x3::operator*(const double& param) const
{
    double aa=a*param;
    double bb=b*param;
    double cc=c*param;
    double dd=d*param;
    double ee=e*param;
    double ff=f*param;
    double gg=g*param;
    double hh=h*param;
    double ii=i*param;
    
    return Matrix3x3(aa,bb,cc,dd,ee,ff,gg,hh,ii);
}
Vector Matrix3x3::operator*(const Vector& param) const
{
    return getColumnVector(0)*param.getX()+getColumnVector(1)*param.getY()+getColumnVector(2)*param.getZ();
}
Matrix3x3 Matrix3x3::operator*(const Matrix3x3& param) const
{
    double aa=Vector::dot(getRowVector(0),param.getColumnVector(0));
    double bb=Vector::dot(getRowVector(0),param.getColumnVector(1));
    double cc=Vector::dot(getRowVector(0),param.getColumnVector(2));
    
    double dd=Vector::dot(getRowVector(1),param.getColumnVector(0));
    double ee=Vector::dot(getRowVector(1),param.getColumnVector(1));
    double ff=Vector::dot(getRowVector(1),param.getColumnVector(2));
    
    double gg=Vector::dot(getRowVector(2),param.getColumnVector(0));
    double hh=Vector::dot(getRowVector(2),param.getColumnVector(1));
    double ii=Vector::dot(getRowVector(2),param.getColumnVector(2));
    
    return Matrix3x3(aa,bb,cc,dd,ee,ff,gg,hh,ii);
}
Matrix3x3 Matrix3x3::operator+(const Matrix3x3& param) const
{
    double nma[3][3];
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            nma[i][j]=matrixArray[i][j]+param.getEntry(i,j);
        }
    }
    
    return Matrix3x3(nma[0][0],nma[0][1],nma[0][2],
                     nma[1][0],nma[1][1],nma[1][2],
                     nma[2][0],nma[2][1],nma[2][2]);
}

Matrix3x3 Matrix3x3::zeroMatrix()
{
    return Matrix3x3(0,0,0,
                     0,0,0,
                     0,0,0);
}
Matrix3x3 Matrix3x3::identityMatrix()
{
    return Matrix3x3(1,0,0,
                     0,1,0,
                     0,0,1);
}

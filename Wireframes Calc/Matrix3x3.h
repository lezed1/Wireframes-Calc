//
//  Matrix3x3.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/24/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__Matrix3x3__
#define __Wireframes_Calc_4_5__Matrix3x3__

#include "basicshapes.h"

class Matrix3x3
{
private:
    double a,b,c,d,e,f,g,h,i; //individual variables for each entry make copying formulas easier
    double matrixArray[3][3]; //array fo entries makes getting a specific entry easier
    
    Vector getColumnVector(int col) const;
    Vector getRowVector(int row) const;
public:
    Matrix3x3(double aa,double bb,double cc,
              double dd,double ee,double ff,
              double gg,double hh,double ii);
    Matrix3x3(const Vector& v1,const Vector& v2,const Vector& v3);
    double determinant() const;
    Matrix3x3 inverse() const;
    
    Matrix3x3 operator*(const double& param) const;
    Vector operator*(const Vector& param) const;
    Matrix3x3 operator*(const Matrix3x3& param) const;
    Matrix3x3 operator+(const Matrix3x3& param) const;
    double getEntry(int i,int j) const;
    void printInfo() const;
    
    static Matrix3x3 zeroMatrix();
    static Matrix3x3 identityMatrix();
};

#endif /* defined(__Wireframes_Calc_4_5__Matrix3x3__) */

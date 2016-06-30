//
//  basicshapes.h
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 11/23/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4__basicshapes__
#define __Wireframes_Calc_4__basicshapes__

#include <iostream>
#include <vector>

double radians(double deg);
double degrees(double rad);

class Line;
class Vector;
class AffineTransformation;
class Point
{ //defines a point, do not use this class to store vectors, use the Vector class instead
private:
    double x; //x-value of the point
    double y; //y-value of the point
    double z; //z-value of the point
public:
    Point(); //default point is (0,0,0)
    Point(double xx,double yy,double zz);
    
    double getX() const; //gets the x-value of the point
    double getY() const; //gets the y-value of the point
    double getZ() const; //gets the z-value of the point
    
    void setX(double xx); //sets the x-value of the point
    void setY(double yy); //sets the y-value of the point
    void setZ(double zz); //sets the z-value of the point
    void setAll(double xx,double yy,double zz); //sets all values of the point
    void rotate(double xrot,double yrot,double zrot); //rotates the point around the x, y, and z axes, in degrees
    void twistPoint(const Line& ll, double theta); //rotates point P around line L, theta degrees
    void twistPoint(const Point& aa, const Point& bb, double theta); //rotates point P around line L, theta degrees
    
    static Point twistPoint(const Point& p, const Line& ll, double theta);
    static Point twistPoint(const Point& p, const Point& aa, const Point& bb, double theta);
    static Point dualize(const Point& aa,const Point& bb,const Point& cc);
    static Point extendLine(const Point& begin,const Point& end,double factor);
    static Point angleBisector(const Point& p1,const Point& p2,const Point& p3);
    static double distance(const Point& p1,const Point& p2);
    static double angleMeasure(const Point& p1,const Point& p2,const Point& p3);
    static bool almostEqual(const Point& p1,const Point& p2);
    
    std::string toString() const;
    Vector toVector() const;
    
    Point operator+(const Point& rhs) const;
    Point operator-(const Point& rhs) const;
    Point operator+(const Vector& rhs) const;
    Point operator-(const Vector& rhs) const;
    Point operator*(const double& rhs) const;
    Point operator/(const double& rhs) const;
    
    Point& operator+=(const Point& rhs);
    Point& operator-=(const Point& rhs);
    Point& operator+=(const Vector& rhs);
    Point& operator-=(const Vector& rhs);
    Point& operator*=(const double& rhs);
    Point& operator/=(const double& rhs);
    
    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const;
};

class Vector
{
private:
    double x,y,z;
public:
    Vector(); //default: <0,0,0>
    Vector(double xx,double yy,double zz);
    Vector(const Point& initial,const Point& terminal);
    
    double getX() const; //gets the x-value of the vector
    double getY() const; //gets the y-value of the vector
    double getZ() const; //gets the z-value of the vector
    double norm() const; //returns magnitude of the vector
    
    void setX(double xx); //sets the x-value of the vector
    void setY(double yy); //sets the y-value of the vector
    void setZ(double zz); //sets the z-value of the vector
    void setAll(double xx,double yy,double zz); //sets all values of the vector
    void rotate(double xrot,double yrot,double zrot); //rotates the vector around the x, y, and z axes, in degrees
    void normalize();
    
    static double dot(const Vector& u,const Vector& v); //dot procduct
    static Vector cross(const Vector& u,const Vector& v); //cross product
    static Vector angleBisector(const Vector& u,const Vector& v); //angle bisector between two vectors
    static Vector projection(const Vector& u,const Vector&v); //project v onto u
    
    std::string toString() const;
    Point toPoint() const;
    
    Vector operator+(const Vector& rhs) const;
    Vector operator-(const Vector& rhs) const;
    Vector operator*(const double& rhs) const;
    Vector operator/(const double& rhs) const;
    
    Vector& operator+=(const Vector& rhs);
    Vector& operator-=(const Vector& rhs);
    Vector& operator*=(const double& rhs);
    Vector& operator/=(const double& rhs);
    
    bool operator==(const Vector& rhs);
    bool operator!=(const Vector& rhs);
    
};

class Line
{ //defines a line segment
private:
    Point a; //an endpoint of the line segment
    Point b; //an endpoint of the line segment
public:
    Line(); //default line goes through (0,0,0) and (1,0,0)
    Line(const Point& aa,const Point& bb);
    
    Point getPointA()    const; //gets an endpoint of the line segment
    Point getPointB()    const; //gets an endpoint of the line segment
    double getDistance() const; //gets the length of the line segment
    Vector getVector()   const; //returns vector with initial point as A and terminal point as B
    Point getMidpoint()  const; //returns midpoint between the line's endpoints
    
    void setAll(const Point& aa,const Point& bb); //changes the endpoints of the line segment
    
    std::string toString() const;
    
    bool operator==(const Line& rhs);
    bool operator!=(const Line& rhs);
};

class Triangle
{
private:
    Point a;
    Point b;
    Point c;
public:
    Triangle();
    Triangle(const Point& aa,const Point& bb,const Point& cc);
    Triangle(const std::vector<Point>& vertices);
    
    Point getPointA() const;
    Point getPointB() const;
    Point getPointC() const;
    Point getCentroid() const;
    
    void setAll(const Point& aa,const Point& bb,const Point& cc);
    
    static Triangle transform(Triangle t,AffineTransformation af);
    
    std::string toString() const;
    void printPOV(const std::string& ocolor,const std::string& rotation) const;
};

class Plane
{
private:
    double a;
    double b;
    double c;
    double d;
public:
    Plane(double aa,double bb,double cc,double dd);
    void setAll(double aa,double bb,double cc,double dd);
    double getA() const;
    double getB() const;
    double getC() const;
    double getD() const;
    double valueAtPoint(Point p) const;
    Vector getNormalVector() const;
    std::string toString() const;
    
    static Plane planeThroughPoints(Point p1,Point p2,Point p3);
};

#endif /* defined(__Wireframes_Calc_4__basicshapes__) */

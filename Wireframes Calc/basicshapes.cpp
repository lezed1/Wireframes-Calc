//
//  basicshapes.cpp
//  Wireframes Calc 4
//
//  Created by Aaron Pfitzenmaier on 11/23/14.
//  Copyright (c) 2014 Aaron Pfitzenmaier. All rights reserved.
//

#include <cmath>
#include <iostream>

#include "basicshapes.h"
#include "AffineTransformation.h"
#include "Utilities.h"

//-------POINT CLASS--------//
Point::Point()
{
    x=0;
    y=0;
    z=0;
}
Point::Point(double xx,double yy,double zz)
{
    x=xx;
    y=yy;
    z=zz;
}
double Point::getX() const
{
    return x;
}
double Point::getY() const
{
    return y;
}
double Point::getZ() const
{
    return z;
}
void Point::setX(double xx)
{
    x=xx;
}
void Point::setY(double yy)
{
    y=yy;
}
void Point::setZ(double zz)
{
    z=zz;
}
void Point::setAll(double xx,double yy,double zz)
{
    x=xx;
    y=yy;
    z=zz;
}
void Point::rotate(double xrot,double yrot,double zrot)
{
    double preX,preY,preZ;
    
    preY=y*cos(xrot*M_PI/180)-z*sin(xrot*M_PI/180);
    preZ=y*sin(xrot*M_PI/180)+z*cos(xrot*M_PI/180);
    y=preY;
    z=preZ;
    
    preZ=z*cos(yrot*M_PI/180)-x*sin(yrot*M_PI/180);
    preX=z*sin(yrot*M_PI/180)+x*cos(yrot*M_PI/180);
    x=preX;
    z=preZ;
    
    preX=x*cos(zrot*M_PI/180)-y*sin(zrot*M_PI/180);
    preY=x*sin(zrot*M_PI/180)+y*cos(zrot*M_PI/180);
    x=preX;
    y=preY;
}
void Point::twistPoint(const Line& ll, double theta)
{
    Point aa=ll.getPointA();
    Point bb=ll.getPointB();
    double U=bb.getX()-aa.getX();
    double V=bb.getY()-aa.getY();
    double W=bb.getZ()-aa.getZ();
    double X=x;
    double Y=y;
    double Z=z;
    double A=aa.getX();
    double B=aa.getY();
    double C=aa.getZ();
    double L=U*U+V*V+W*W;
    
    double newx=(((A*(V*V+W*W)-U*(B*V+C*W-U*X-V*Y-W*Z))*(1-cos(radians(theta)))+(L*X*cos(radians(theta)))+(sqrt(L)*(-1*C*V+B*W-W*Y+V*Z)*sin(radians(theta))))/L);
    double newy=(((B*(U*U+W*W)-V*(A*U+C*W-U*X-V*Y-W*Z))*(1-cos(radians(theta)))+(L*Y*cos(radians(theta)))+(sqrt(L)*(C*U-A*W+W*X-U*Z)*sin(radians(theta))))/L);
    double newz=(((C*(U*U+V*V)-W*(A*U+B*V-U*X-V*Y-W*Z))*(1-cos(radians(theta)))+(L*Z*cos(radians(theta)))+(sqrt(L)*(-1*B*U+A*V-V*X+U*Y)*sin(radians(theta))))/L);
    x=newx;
    y=newy;
    z=newz;
}
void Point::twistPoint(const Point& aa, const Point& bb, double theta)
{
    double U=bb.getX()-aa.getX();
    double V=bb.getY()-aa.getY();
    double W=bb.getZ()-aa.getZ();
    double X=x;
    double Y=y;
    double Z=z;
    double A=aa.getX();
    double B=aa.getY();
    double C=aa.getZ();
    double L=U*U+V*V+W*W;
    
    double newx=(((A*(V*V+W*W)-U*(B*V+C*W-U*X-V*Y-W*Z))*(1-cos(radians(theta)))+(L*X*cos(radians(theta)))+(sqrt(L)*(-1*C*V+B*W-W*Y+V*Z)*sin(radians(theta))))/L);
    double newy=(((B*(U*U+W*W)-V*(A*U+C*W-U*X-V*Y-W*Z))*(1-cos(radians(theta)))+(L*Y*cos(radians(theta)))+(sqrt(L)*(C*U-A*W+W*X-U*Z)*sin(radians(theta))))/L);
    double newz=(((C*(U*U+V*V)-W*(A*U+B*V-U*X-V*Y-W*Z))*(1-cos(radians(theta)))+(L*Z*cos(radians(theta)))+(sqrt(L)*(-1*B*U+A*V-V*X+U*Y)*sin(radians(theta))))/L);
    x=newx;
    y=newy;
    z=newz;
}

Point Point::twistPoint(const Point& p, const Line& ll, double theta)
{
    Point aa=ll.getPointA();
    Point bb=ll.getPointB();
    double U=bb.getX()-aa.getX();
    double V=bb.getY()-aa.getY();
    double W=bb.getZ()-aa.getZ();
    double X=p.getX();
    double Y=p.getY();
    double Z=p.getZ();
    double A=aa.getX();
    double B=aa.getY();
    double C=aa.getZ();
    double L=U*U+V*V+W*W;
    
    double newx=(((A*(V*V+W*W)-U*(B*V+C*W-U*X-V*Y-W*Z))*(1-cos(radians(theta)))+(L*X*cos(radians(theta)))+(sqrt(L)*(-1*C*V+B*W-W*Y+V*Z)*sin(radians(theta))))/L);
    double newy=(((B*(U*U+W*W)-V*(A*U+C*W-U*X-V*Y-W*Z))*(1-cos(radians(theta)))+(L*Y*cos(radians(theta)))+(sqrt(L)*(C*U-A*W+W*X-U*Z)*sin(radians(theta))))/L);
    double newz=(((C*(U*U+V*V)-W*(A*U+B*V-U*X-V*Y-W*Z))*(1-cos(radians(theta)))+(L*Z*cos(radians(theta)))+(sqrt(L)*(-1*B*U+A*V-V*X+U*Y)*sin(radians(theta))))/L);

    return Point(newx,newy,newz);
}
Point Point::twistPoint(const Point& p, const Point& aa, const Point& bb, double theta)
{
    double U=bb.getX()-aa.getX();
    double V=bb.getY()-aa.getY();
    double W=bb.getZ()-aa.getZ();
    double X=p.getX();
    double Y=p.getY();
    double Z=p.getZ();
    double A=aa.getX();
    double B=aa.getY();
    double C=aa.getZ();
    double L=U*U+V*V+W*W;
    
    double newx=(((A*(V*V+W*W)-U*(B*V+C*W-U*X-V*Y-W*Z))*(1-cos(radians(theta)))+(L*X*cos(radians(theta)))+(sqrt(L)*(-1*C*V+B*W-W*Y+V*Z)*sin(radians(theta))))/L);
    double newy=(((B*(U*U+W*W)-V*(A*U+C*W-U*X-V*Y-W*Z))*(1-cos(radians(theta)))+(L*Y*cos(radians(theta)))+(sqrt(L)*(C*U-A*W+W*X-U*Z)*sin(radians(theta))))/L);
    double newz=(((C*(U*U+V*V)-W*(A*U+B*V-U*X-V*Y-W*Z))*(1-cos(radians(theta)))+(L*Z*cos(radians(theta)))+(sqrt(L)*(-1*B*U+A*V-V*X+U*Y)*sin(radians(theta))))/L);
    
    return Point(newx,newy,newz);
}
Point Point::dualize(const Point& aa,const Point& bb,const Point& cc)
{
    double a=aa.getX();
    double b=aa.getY();
    double c=aa.getZ();
    double d=bb.getX();
    double e=bb.getY();
    double f=bb.getZ();
    double g=cc.getX();
    double h=cc.getY();
    double i=cc.getZ();
    double xx=b*(f-i)+e*(i-c)+h*(c-f);
    double yy=c*(d-g)+f*(g-a)+i*(a-d);
    double zz=a*(e-h)+d*(h-b)+g*(b-e);
    double ww=a*(e*i-h*f)+d*(h*c-b*i)+g*(b*f-e*c);
    double w=ww*-1;
    double tt=(-1*w)/(xx*xx+yy*yy+zz*zz);
    double distancce=sqrt((xx*xx*tt*tt)+(yy*yy*tt*tt)+(zz*zz*tt*tt));
    double n=1/(distancce*distancce);
    double newx=xx*tt*n;
    double newy=yy*tt*n;
    double newz=zz*tt*n;
    Point nnew(newx,newy,newz);
    return nnew;
}
Point Point::extendLine(const Point& begin,const Point& end,double factor)
{
    double newx=begin.getX()+factor*(end.getX()-begin.getX());
    double newy=begin.getY()+factor*(end.getY()-begin.getY());
    double newz=begin.getZ()+factor*(end.getZ()-begin.getZ());
    Point nnew(newx,newy,newz);
    return nnew;
}
Point Point::angleBisector(const Point& p1,const Point& p2,const Point& p3)
{
    Vector v1(p2,p1);
    Vector v2(p2,p3);
    v1.normalize();
    v2.normalize();
    return p2+v1+v2;
}
double Point::distance(const Point& p1,const Point& p2)
{
    double x2=(p1.getX()-p2.getX());
    x2*=x2;
    double y2=(p1.getY()-p2.getY());
    y2*=y2;
    double z2=(p1.getZ()-p2.getZ());
    z2*=z2;
    
    return sqrt(x2+y2+z2);
}
double Point::angleMeasure(const Point& p1,const Point& p2,const Point& p3)
{
    double c=Point::distance(p1, p3);
    double a=Point::distance(p2, p3);
    double b=Point::distance(p1, p2);
    
    return acos((a*a+b*b-c*c)/(2*a*b));
}
bool Point::almostEqual(const Point& p1,const Point& p2)
{
    double smallNum=0.000001;
    double dist=Point::distance(p1, p2);
    if (dist<=smallNum)
    {
        return true;
    }
    else
    {
        return false;
    }
}
std::string Point::toString() const
{
    /*std::string s="";
    s+=doubleToString(x);
    s+=",";
    s+=doubleToString(y);
    s+=",";
    s+=doubleToString(z);
    return s;*/
    return doubleToString(x)+","+doubleToString(y)+","+doubleToString(z);
}
Vector Point::toVector() const
{
    return Vector(x,y,z);
}

Point Point::operator+(const Point& rhs) const
{
    Point result=*this;
    result+=rhs;
    return result;
}
Point Point::operator-(const Point& rhs) const
{
    Point result=*this;
    result-=rhs;
    return result;
}
Point Point::operator+(const Vector& rhs) const
{
    Point result=*this;
    result+=rhs;
    return result;
}
Point Point::operator-(const Vector& rhs) const
{
    Point result=*this;
    result-=rhs;
    return result;
}
Point Point::operator*(const double& rhs) const
{
    Point result=*this;
    result*=rhs;
    return result;
}
Point Point::operator/(const double& rhs) const
{
    Point result=*this;
    result/=rhs;
    return result;
}

Point& Point::operator+=(const Point& rhs)
{
    x+=rhs.x;
    y+=rhs.y;
    z+=rhs.z;
    
    return *this;
}
Point& Point::operator-=(const Point& rhs)
{
    x-=rhs.x;
    y-=rhs.y;
    z-=rhs.z;
    
    return *this;
}
Point& Point::operator+=(const Vector& rhs)
{
    x+=rhs.getX();
    y+=rhs.getY();
    z+=rhs.getZ();
    
    return *this;
}
Point& Point::operator-=(const Vector& rhs)
{
    x-=rhs.getX();
    y-=rhs.getY();
    z-=rhs.getZ();
    
    return *this;
}
Point& Point::operator*=(const double& rhs)
{
    x*=rhs;
    y*=rhs;
    z*=rhs;
    
    return *this;
}
Point& Point::operator/=(const double& rhs)
{
    x/=rhs;
    y/=rhs;
    z/=rhs;
    
    return *this;
}

bool Point::operator==(const Point& rhs) const
{
    return x==rhs.x && y==rhs.y && z==rhs.z;
}
bool Point::operator!=(const Point& rhs) const
{
    return !(*this==rhs);
}

//------VECTOR CLASS-----//
Vector::Vector()
{
    x=0;
    y=0;
    z=0;
}
Vector::Vector(double xx,double yy,double zz)
{
    x=xx;
    y=yy;
    z=zz;
}
Vector::Vector(const Point& initial,const Point& terminal)
{
    Point diff=terminal-initial;
    x=diff.getX();
    y=diff.getY();
    z=diff.getZ();
}

double Vector::getX() const
{
    return x;
}
double Vector::getY() const
{
    return y;
}
double Vector::getZ() const
{
    return z;
}
double Vector::norm() const
{
    return sqrt(dot(*this, *this));
}

void Vector::setX(double xx)
{
    x=xx;
}
void Vector::setY(double yy)
{
    y=yy;
}
void Vector::setZ(double zz)
{
    z=zz;
}
void Vector::setAll(double xx,double yy,double zz)
{
    x=xx;
    y=yy;
    z=zz;
}
void Vector::rotate(double xrot,double yrot,double zrot)
{
    double preX,preY,preZ;
    
    preY=y*cos(xrot*M_PI/180)-z*sin(xrot*M_PI/180);
    preZ=y*sin(xrot*M_PI/180)+z*cos(xrot*M_PI/180);
    y=preY;
    z=preZ;
    
    preZ=z*cos(yrot*M_PI/180)-x*sin(yrot*M_PI/180);
    preX=z*sin(yrot*M_PI/180)+x*cos(yrot*M_PI/180);
    x=preX;
    z=preZ;
    
    preX=x*cos(zrot*M_PI/180)-y*sin(zrot*M_PI/180);
    preY=x*sin(zrot*M_PI/180)+y*cos(zrot*M_PI/180);
    x=preX;
    y=preY;
}
void Vector::normalize()
{
    double n=norm();
    x/=n;
    y/=n;
    z/=n;
}

double Vector::dot(const Vector& u,const Vector& v)
{
    return u.getX()*v.getX()+
    u.getY()*v.getY()+
    u.getZ()*v.getZ();
}
Vector Vector::cross(const Vector& u,const Vector& v)
{
    Vector p;
    double u1=u.getX();
    double u2=u.getY();
    double u3=u.getZ();
    double v1=v.getX();
    double v2=v.getY();
    double v3=v.getZ();
    
    double i=u2*v3-u3*v2;
    double j=u3*v1-u1*v3;
    double k=u1*v2-u2*v1;
    
    p.setAll(i, j, k);
    return p;
}
Vector Vector::angleBisector(const Vector& u,const Vector& v)
{
    return u*v.norm()+v*u.norm();
}
Vector Vector::projection(const Vector& u,const Vector&v)
{
    double vu=Vector::dot(v, u);
    double uu=Vector::dot(u, u);
    return u*(vu/uu);
}

std::string Vector::toString() const
{
    
    std::string s="";
    s+=doubleToString(x);
    s+=",";
    s+=doubleToString(y);
    s+=",";
    s+=doubleToString(z);
    return s;
}
Point Vector::toPoint() const
{
    return Point(x,y,z);
}

Vector Vector::operator+(const Vector& rhs) const
{
    Vector result=*this;
    result+=rhs;
    return result;
}
Vector Vector::operator-(const Vector& rhs) const
{
    Vector result=*this;
    result-=rhs;
    return result;
}
Vector Vector::operator*(const double& rhs) const
{
    Vector result=*this;
    result*=rhs;
    return result;
}
Vector Vector::operator/(const double& rhs) const
{
    Vector result=*this;
    result/=rhs;
    return result;
}

Vector& Vector::operator+=(const Vector& rhs)
{
    x+=rhs.x;
    y+=rhs.y;
    z+=rhs.z;
    
    return *this;
}
Vector& Vector::operator-=(const Vector& rhs)
{
    x-=rhs.x;
    y-=rhs.y;
    z-=rhs.z;
    
    return *this;
}
Vector& Vector::operator*=(const double& rhs)
{
    x*=rhs;
    y*=rhs;
    z*=rhs;
    
    return *this;
}
Vector& Vector::operator/=(const double& rhs)
{
    x/=rhs;
    y/=rhs;
    z/=rhs;
    
    return *this;
}

bool Vector::operator==(const Vector& rhs)
{
    return x==rhs.x && y==rhs.y && z==rhs.z;
}
bool Vector::operator!=(const Vector& rhs)
{
    return !(*this==rhs);
}

//------LINE CLASS------//
Line::Line()
{
    a.setAll(0,0,0);
    b.setAll(1,0,0);
}
Line::Line(const Point& aa,const Point& bb)
{
    a=aa;
    b=bb;
}

Point Line::getPointA() const
{
    return a;
}
Point Line::getPointB() const
{
    return b;
}
double Line::getDistance() const
{
    //return sqrt((a.getX()-b.getX())*(a.getX()-b.getX())+
    //            (a.getY()-b.getY())*(a.getY()-b.getY())+
    //            (a.getZ()-b.getZ())*(a.getZ()-b.getZ()));
    return getVector().norm();
}
Vector Line::getVector() const
{
    Point result=getPointB()-getPointA();
    return Vector(result.getX(),result.getY(),result.getZ());
}
Point Line::getMidpoint() const
{
    return (a+b)/2.0;
}

void Line::setAll(const Point& aa,const Point& bb)
{
    a=aa;
    b=bb;
}

std::string Line::toString() const
{
    return a.toString()+"\n"+b.toString();
}

bool Line::operator==(const Line& rhs)
{
    return a==rhs.a && b==rhs.b;
}
bool Line::operator!=(const Line& rhs)
{
    return !(*this==rhs);
}

//-------TRIANGLE CLASS-------//
Triangle::Triangle()
{
    Point defaultPoint;
    a=defaultPoint;
    b=defaultPoint;
    c=defaultPoint;
    
}
Triangle::Triangle(const Point& aa,const Point& bb,const Point& cc)
{
    a=aa;
    b=bb;
    c=cc;
}
Triangle::Triangle(const std::vector<Point>& vertices)
{
    if (vertices.size()!=3)
    {
        std::cout << "Error: Attempt to construct triangle using vector of size!=3, size=" << vertices.size() << ". Constructing default triangle.\n";
        Point defaultPoint;
        a=defaultPoint;
        b=defaultPoint;
        c=defaultPoint;
    }
    else
    {
        a=vertices.at(0);
        b=vertices.at(1);
        c=vertices.at(2);
    }
}

Point Triangle::getPointA() const
{
    return a;
}
Point Triangle::getPointB() const
{
    return b;
}
Point Triangle::getPointC() const
{
    return c;
}
Point Triangle::getCentroid() const
{
    Point centroid=(a+b+c)/3.0;
    return centroid;
}

void Triangle::setAll(const Point& aa,const Point& bb,const Point& cc)
{
    a=aa;
    b=bb;
    c=cc;
}
Triangle Triangle::transform(Triangle t,AffineTransformation af)
{
    Point p1=af.transform(t.getPointA());
    Point p2=af.transform(t.getPointB());
    Point p3=af.transform(t.getPointC());
    return Triangle(p1,p2,p3);
}

std::string Triangle::toString() const
{
    return a.toString()+"\n"+b.toString()+"\n"+c.toString();
}
void Triangle::printPOV(const std::string& ocolor,const std::string& rotation) const
{
    std::cout << "polygon {3, <" << a.toString() << ">,<" << b.toString() << ">,<" << c.toString() << "> texture{pigment{color " << ocolor << "} finish{phong 1}} rotate " << rotation << "}\n";
}

//-----PLANE CLASS-----//
Plane::Plane(double aa,double bb,double cc,double dd)
{
    a=aa;
    b=bb;
    c=cc;
    d=dd;
}
void Plane::setAll(double aa, double bb, double cc, double dd)
{
    a=aa;
    b=bb;
    c=cc;
    d=dd;
}
double Plane::getA() const
{
    return a;
}
double Plane::getB() const
{
    return b;
}
double Plane::getC() const
{
    return c;
}
double Plane::getD() const
{
    return d;
}
double Plane::valueAtPoint(Point p) const
{
    double xx=p.getX();
    double yy=p.getY();
    double zz=p.getZ();
    
    return a*xx+b*yy+c*zz+d;
}
Vector Plane::getNormalVector() const
{
    return Vector(a,b,c);
}
std::string Plane::toString() const
{
    std::string planeString=doubleToString(a);
                planeString+="x+";
                planeString+=doubleToString(b);
                planeString+="y+";
                planeString+=doubleToString(c);
                planeString+="z+";
                planeString+=doubleToString(d);
                planeString+="=0";
    return planeString;
}
Plane Plane::planeThroughPoints(Point p1, Point p2, Point p3)
{
    double a=p1.getX();
    double b=p1.getY();
    double c=p1.getZ();
    double d=p2.getX();
    double e=p2.getY();
    double f=p2.getZ();
    double g=p3.getX();
    double h=p3.getY();
    double i=p3.getZ();
    
    double x=b*(f-i)+e*(i-c)+h*(c-f);
    double y=c*(d-g)+f*(g-a)+i*(a-d);
    double z=a*(e-h)+d*(h-b)+g*(b-e);
    double w=a*(e*i-h*f)+d*(h*c-b*i)+g*(b*f-e*c);
    w=w*-1;
    
    return Plane(x,y,z,w);
    
}

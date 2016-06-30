//
//  main.cpp
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 4/26/15.
//  Copyright (c) 2015 Aaron Pfitzenmaier. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include "OldCode.h"

#include "basicshapes.h"
#include "Matrix3x3.h"
#include "Tetrahedron.h"
#include "FiveCompound.h"
#include "Polypolyhedra2.h"
#include "FifteenCompound.h"
#include "Hexahedron.h"
#include "Optimization.h"
#include "TriangularPrism.h"
#include "TetrahedralCompound.h"
#include "AffineTransformation.h"
#include "Polyhedron.h"
#include "FIT.h"
#include "Hendecahedron.h"
#include "TenCompound.h"
#include "TriangularPyramid.h"
#include "Icosahedron.h"
#include "IcosahedralCompound.h"
#include "Octahedron.h"
#include "OctahedralCompound.h"
#include "FiveRectangles.h"
#include "SixCompound.h"
#include "Pentagon.h"
#include "AlecShape.h"
#include "IcosahedralEdgeCompound.h"

int main(int argc, const char * argv[])
{
    clock_t t;
    t = clock();
    
    // insert code here...
    std::cout << "Hello, World!\n";
    std::vector<std::string> colors1={"Blue","Green","Red","Yellow","Orange","Violet","Cyan","Magenta","Black","Brown","CadetBlue","Aquamarine","Gray","MediumVioletRed","BlueViolet","SeaGreen","SlateBlue","MediumSlateBlue","Tan","Light_Purple"};
    std::vector<std::string> colors2={"Yellow","Green","Blue","Red","Violet","MediumVioletRed","CadetBlue","Orange","CornflowerBlue","DarkGreen","Cyan","Magenta","Aquamarine","BlueViolet","Brown","MediumSlateBlue","Tan","Light_Purple","SlateBlue","SeaGreen"};
    std::vector<std::string> colors3={"Yellow","Green","Blue","Red","Violet","Cyan","Magenta","Aquamarine","BlueViolet","Brown","MediumVioletRed","Yellow","Cyan","Brown","Orange","Light_Purple","SeaGreen","MediumSlateBlue","SlateBlue","Tan"};
    //oldCode1();
    
    /*Vector v1(4,5,6);
     Vector v2(-1,3,4);
     Vector v3(2,0,-1);
     Matrix3x3 matrix(v1,v2,v3);
     matrix.printInfo();
     std::cout << (matrix*v3).toString() << "\n";*/
    
    //Tetrahedron tet(0,0,0);
    //FiveCompound compound(tet);
    //compound.printPovRaySkeleton(0.1, colors1);
    //polypolyhedron(&compound,colors1,true,1,5,3,PovRay);
    
    //Hexahedron hexa(0,0,0);
    //FifteenCompound compound(hexa);
    //compound.printPovRayFrame(0.0861822, colors1);
    //std::cout << computeCompoundWidth(compound) << "\n";
    //std::cout << compound.computeWidth() << "\n";
    
    //TriangularPrism tp(0,0,0);
    //tp.setAttribute("height", 1.2);
    //TetrahedralCompound compound(tp,0.2,45);
    //compound.printPovRaySkeleton(0.1, colors1);
    
    //Tetrahedron tet(0,0,0);
    //FiveCompound tetcompound(tet);
    //std::cout << computeCompoundWidth(tetcompound);
    //tetcompound.printPovRayFrame(0.233906, colors1);
    
    //FIT fit(0,0,0);
    //TetrahedralCompound compound(fit,-1.35,97);
    //std::cout << fit.getEdgeLine(0).getDistance()/(4*computeCompoundWidth(compound)) << "\n";
    //compound.printPovRayFrame(computeCompoundWidth(compound), colors3);
    
    /*for (double i=1.0;i<=1.1;i+=0.01)
     {
     for (double j=1;j<=120;j+=1)
     {
     clock_t tt=clock();
     TetrahedralCompound compound(fit,-i,j);
     std::cout << i << " " << j << " " << 2*sqrt(2)/(4.0*computeCompoundWidth2(compound)) << " ";
     tt = clock() - tt;
     std::cout << ((float)tt)/CLOCKS_PER_SEC << "\n";
     }
     }*/
    
    /*Hendecahedron hd(0,0,0);
     hd.setAttribute("poleHeight", 3.207);
     hd.setAttribute("triangleHeight", 1.198);
     hd.setAttribute("twist", 3.8);
     TenCompound compound(hd);
     std::cout << computeCompoundWidth(compound) << "\n";*/
    
    //-0.976,25.4--new
    //-1.27,30--dirk eisner
    //-0.7071,15.523--FIT minus 1 tetrahedron
    //-0.14,34--odin's tetrahedra
    //0.6,42--francesco mancini
    //TriangularPyramid tp(0,0,0);
    //TetrahedralCompound compound(tp,0.6,42);
    //compound.printPovRayFrame(computeCompoundWidth(compound), colors1);
    
    //0.58,12--new
    //0.7074,23.77--byriah, k7
    //-3.37,9--new
    //2.39,34--byriah, k6
    //0.59,30--new
    //1.42,11--new
    //-0.9439,33.62--new, neat
    //-1.53,43--new
    //-0.59,41--byriah, k5
    //TriangularPyramid tp(0,0,0);
    //IcosahedralCompound compound(tp,-0.9439,33.62);
    //compound.printPovRayFrame(0.1, colors1);
    //std::cout << sqrt(12)/(4.0*computeCompoundWidth(compound)) << "\n";
    
    //0.25,10--interesting?
    //1.14,35--byriah
    //0.0409,40.59--new
    //-0.6105,39.41--new
    //TriangularPyramid tp(0,0,0);
    //OctahedralCompound compound(tp,-0.6105,39.41);
    //double width=computeCompoundWidth(compound);
    //compound.printPovRayFrame(sqrt(12)/(20), colors1);
    //std::cout << width << "\n";
    //compound.getPolyhedron(0)->printPovRayFrame(width, "Green");
    //compound.getPolyhedron(1)->printPovRayFrame(width, "Red");
    //compound.getPolyhedron(2)->printPovRayFrame(width, "Black");
    //compound.getPolyhedron(3)->printPovRayFrame(width, "Magenta");
    //compound.getPolyhedron(4)->printPovRayFrame(width, "Orange");
    //compound.getPolyhedron(5)->printPovRayFrame(width, "Blue");
    //    compound.getPolyhedron(6)->printPovRayFrame(width, "Cyan"); // Bad!
    //compound.getPolyhedron(7)->printPovRayFrame(width, "Green");
    
    
    //Octahedron o(0,0,0);
    //o.printPovRayFrame(0.1, "Green");
    
    /*for (double i=-0.613;i<=-0.607;i+=0.0001)
     {
     for (double j=39.1;j<=39.7;j+=0.01)
     {
     //clock_t tt=clock();
     OctahedralCompound compound(tp,i,j);
     double width=computeCompoundWidth(compound);
     if (width>=0.5) {continue;}
     std::cout << i << " " << j << " " << width << "\n";
     //tt = clock() - tt;
     //std::cout << ((float)tt)/CLOCKS_PER_SEC << "\n";
     }
     }*/
    
    /*Pentagon p(0,0,0);
     SixCompound compound(p);
     double width=computeCompoundWidth(compound,sqrt(5));
     compound.printPovRayFrame(width, colors1);
     std::cout << width << "\n";*/
    
    //exact: w=0.5837,l=2.3867,shift=0,twist=0
    ///FiveRectangles fr(0,0,0);
    //fr.setAttribute("width", 0.5837);
    //fr.setAttribute("length", 2.3867);
    
    ///fr.setAttribute("width", 0.5986);
    ///fr.setAttribute("length", 2.3569);
    ///fr.setAttribute("twist", 3.69);
    ///fr.setAttribute("shift", -0.0256);
    ///SixCompound compound(fr);
    ///double width=computeCompoundWidth(compound,sqrt(5));
    ///compound.printPovRayFrame(3.5541*2.0/(9.5*5.0), colors1);
    ///std::cout << width << "\n";
    //compound.printPovRaySkeleton(compound.computeWidth(), colors1);
    
    /*for (double j=-180;j<=180;j+=1)
     {
     fr.setAttribute("twist", j);
     //clock_t tt=clock();
     SixCompound compound(fr);
     double thick=computeCompoundWidth(compound,sqrt(5));
     double sizeInverse=thick/(0.58+2.38);
     std::cout << j << " " << sizeInverse << "\n";
     //tt = clock() - tt;
     //std::cout << ((float)tt)/CLOCKS_PER_SEC << "\n";
     }*/
    
    /*for (double i=-0.029;i<=-0.023;i+=0.0001)
     {
     for (double j=3.4;j<=4.0;j+=0.01)
     {
     double length=fr.getAttribute("length").getCurrentValue();
     double width=fr.getAttribute("width").getCurrentValue();
     fr.setAttribute("twist", j);
     fr.setAttribute("shift", i);
     //clock_t tt=clock();
     SixCompound compound(fr);
     double thick=computeCompoundWidth(compound,2.24);
     double sizeInverse=thick/(length+width);
     std::cout << i << " " << j << " " << sizeInverse << "\n";
     //tt = clock() - tt;
     //std::cout << ((float)tt)/CLOCKS_PER_SEC << "\n";
     }
     }*/
    
    
    std::ofstream outputFile;
    outputFile.open("/tmp/out.pov");
    
    outputFile << "#include \"colors.inc\" \n";
    outputFile << "\n";
    outputFile << "background {color White}\n";
    outputFile << "\n";
//    outputFile << "#declare light=<2,3,0>*2;\n";
//    outputFile << "#declare light=<1.3,1.3,1.3>*6;\n";
    outputFile << "#declare light=<1.25,0,-2>*7;\n";
//    outputFile << "#declare light=<5,3,5>*2;\n";
//    outputFile << "#declare light=<10,0,0>*0.5;\n";
    outputFile << "\n";
    outputFile << "camera {location light look_at <0,0,0>}\n";
    outputFile << "\n";
    outputFile << "light_source {light color White}  \n";

    
    TriangularPrism tp(0,0,0);
    tp.setAttribute("height", 2.0);
    IcosahedralEdgeCompound compound(tp, 3.9, 46);
    
    compound.printPovRayFrame(0.17, colors1, outputFile);
    outputFile.close();
    
    system("/usr/local/bin/povray /tmp/out.pov");
    system("open /tmp/out.png");
    
    std::cout << tp.getLongestEdgeLength()/(4.0*computeCompoundWidth(compound)) << "\n";
    
    
    //for (double shift=3.5;shift<4.5;shift+=0.05)
    //{
    //    for (double twist=20;twist<70;twist+=2)
    //    {
    //        for (double height=1.0;height<3.0;height+=0.02)
    //        {
    //            TriangularPrism tp(0,0,0);
    //            tp.setAttribute("height", height);
    //            IcosahedralEdgeCompound compound(tp,3.9,46);
    //            double width=computeCompoundWidth(compound);
    //            std::cout << 3.9 << " " << 46 << " " << height << " " << width << "\n";
    //        }
    //}
    //}
    
    t = clock() - t;
    printf ("\nIt took me %lu clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    return 0;
}


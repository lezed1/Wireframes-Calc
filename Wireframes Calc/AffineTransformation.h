//
//  AffineTransformation.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/28/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__AffineTransformation__
#define __Wireframes_Calc_4_5__AffineTransformation__

//
//  LinearTransfomation.h
//  Wireframes Calc 4.5
//
//  Created by Aaron Pfitzenmaier on 5/28/16.
//  Copyright (c) 2016 Aaron Pfitzenmaier. All rights reserved.
//

#ifndef __Wireframes_Calc_4_5__LinearTransfomation__
#define __Wireframes_Calc_4_5__LinearTransfomation__

#include "Matrix3x3.h"
#include "basicshapes.h"

class AffineTransformation
{
private:
    Matrix3x3 matrix;
    Vector translation;
    
    Matrix3x3 getMatrix() const;
    Vector getTranslation() const;
public:
    AffineTransformation();
    AffineTransformation(const Matrix3x3& m,const Vector& v);
    AffineTransformation(const Vector& v);
    AffineTransformation(const Matrix3x3& m);
    
    Vector transform(const Vector& v) const;
    Point transform(const Point& p) const;
    void compose(AffineTransformation a);
    void printMatrix() const;
    
    static AffineTransformation makeRotation(double xrot,double yrot,double zrot);
};

#endif /* defined(__Wireframes_Calc_4_5__LinearTransfomation__) */


#endif /* defined(__Wireframes_Calc_4_5__AffineTransformation__) */

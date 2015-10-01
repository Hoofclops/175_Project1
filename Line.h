//
//  Line.h
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Line__
#define __Project1__Line__

#include "Point.h"
class Line
{
private:
    Point* mA;
    Point* mB;
    
public:
    Line(Point *a, Point *b);
    
    Point* GetPointA();
    void SetPointA(Point* p);
    
    Point* GetPointB();
    void SetPointB(Point* p);
};

#endif /* defined(__Project1__Line__) */

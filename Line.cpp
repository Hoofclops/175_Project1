//
//  Line.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "Line.h"

Line::Line(Point a, Point b)
{
    mA = a;
    mB = b;
}

Point Line::GetPointA()
{
    return mA;
}

void Line::SetPointA(Point p)
{
    mA = p;
}

Point Line::GetPointB()
{
    return mB;
}

void Line::SetPointB(Point p)
{
    mB = p;
}

string Line::GetAlgorithm()
{
    return mLineAlgorithm;
}

void Line::SetAlgorithm(string algorithm)
{
    mLineAlgorithm = algorithm;
}


//
//  Point.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/25/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "Point.h"

Point::Point(Vector2i pos)
{
    mPos = pos;
}

Point::Point(Vector2i pos, Color color)
{
    mPos = pos;
    mColor = color;
}

Point::Point(int x, int y)
{
    mPos.mX = x;
    mPos.mY = y;
}

Point::Point(int x, int y, Color color)
{
    mPos.mX = x;
    mPos.mY = y;
    mColor = color;
}

Vector2i Point::GetPos()
{
    return mPos;
}
void Point::SetPos(Vector2i pos)
{
    mPos = pos;
}

int Point::GetX()
{
    return mPos.mX;
}
int Point::GetY()
{
    return mPos.mY;
}

Color Point::GetColor()
{
    return mColor;
}
void Point::SetColor(Color color)
{
    mColor = color;
}
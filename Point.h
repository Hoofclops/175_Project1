//
//  Point.h
//  Project1
//
//  Created by Brandon Nguyen on 9/25/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Point__
#define __Project1__Point__

#include "Vector2i.h"
#include "Color.h"

class Point
{
private:
    Vector2i mPos;
    Color mColor;
    
public:
    
    Point();
    Point(Vector2i pos);
    Point(Vector2i pos, Color color);
    Point(int x, int y);
    Point(int x, int y, Color color);
    
    Vector2i GetPos();
    
    int GetX();
    void SetX(int x);
    int GetY();
    void SetY(int y);
    
    Color GetColor();
    void SetColor(Color color);
};

#endif /* defined(__Project1__Point__) */

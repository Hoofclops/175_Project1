//
//  Vector3.h
//  Project1
//
//  Created by Brandon Nguyen on 9/25/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Vector3__
#define __Project1__Vector3__

class Vector3
{
public:
    float mX;
    float mY;
    float mZ;
    
    Vector3();
    Vector3(float x, float y, float z);
    void Add(Vector3 other);
    void Subtract(Vector3 other);
    void Multiply(Vector3 other);
};

#endif /* defined(__Project1__Vector3__) */

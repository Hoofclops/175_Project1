//
//  Polygon.h
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Polygon__
#define __Project1__Polygon__

#include <deque>
#include <list>
#include <stdexcept>
#include "Point.h"
#include "Line.h"

class Polygon
{
private:
    //deque to maintain stable references between edges and vertices
    deque<Point> mVertices;
    deque<Line> mEdges;
    
public:
    Polygon();
    Polygon(deque<Vector2i> vertPositions);
    
    deque<Point> GetVertices();
    void SetVertices(deque<Point> vertices);
    
    deque<Line> GetEdges();
};
#endif /* defined(__Project1__Polygon__) */

//
//  Polygon.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "Polygon.h"

Polygon::Polygon(deque<Vector2i> vertPositions)
{
    long n = vertPositions.size();
    
    if(n <= 0)
    {
        throw invalid_argument("Invalid amount of vertices passed to Polygon constructor");
    }
    
    //Construct lines and edges, insert them into data tables
    Point first = Point(vertPositions[0]);
    mVertices.push_back(first);
    for(int i = 1; i < n; i++)
    {
        Point p = Point(vertPositions[i]);
        mVertices.push_back(p);
        
        Line l = Line(&mVertices[i - 1], &mVertices[i]);
        mEdges.push_back(l);
    }
    
    long vertexCount = mVertices.size();
    Line closingEdge = Line(&mVertices[vertexCount - 1], &mVertices[0]);
    mEdges.push_back(closingEdge);
}

deque<Point> Polygon::GetVertices()
{
    return mVertices;
}
void Polygon::SetVertices(deque<Point> vertices)
{
    mVertices = vertices;
}

deque<Line> Polygon::GetEdges()
{
    return mEdges;
}
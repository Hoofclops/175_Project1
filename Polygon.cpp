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
    }
    
    mSelected = false;
}

deque<Point> Polygon::GetVertices()
{
    return mVertices;
}
void Polygon::SetVertex(int index, Vector2i pos)
{
    mVertices[index].SetX(pos.mX);
    mVertices[index].SetY(pos.mY);
}

void Polygon::SetVertices(deque<Point> verts)
{
    mVertices = verts;
}

deque<Line> Polygon::GetEdges()
{
    mEdges.clear();
    
    long n = mVertices.size();
    for(int i = 1; i < n; i++)
    {
        Line l = Line(mVertices[i - 1], mVertices[i]);
        mEdges.push_back(l);
    }
    
    Line closingEdge = Line(mVertices[n - 1], mVertices[0]);
    mEdges.push_back(closingEdge);
    
    return mEdges;
}

void Polygon::SetSelected(bool isSelected)
{
    mSelected = isSelected;
}

bool Polygon::IsSelected()
{
    return mSelected;
}

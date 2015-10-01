//
//  ObjectEditor.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/28/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "ObjectEditor.h"

ObjectEditor* ObjectEditor::sInstance;
deque<Polygon> ObjectEditor::sPolyList;

ObjectEditor::ObjectEditor(){}

void ObjectEditor::CreatePolygon(deque<Vector2i> vertPositions)
{
    Polygon poly = Polygon(vertPositions);
    sPolyList.push_back(poly);
}

void ObjectEditor::TranslatePolygon(int polygonID, Vector2i translationVector)
{
    if(polygonID >= sPolyList.size())
    {
        throw invalid_argument("Invalid Polygon ID");
    }
       
    Polygon poly = sPolyList[polygonID];
    deque<Point> vertices = poly.GetVertices();
    
    long n = vertices.size();
    for(int i = 0; i < n; i++)
    {
        int x = vertices[i].GetX(), y = vertices[i].GetY();
        x += translationVector.mX;
        y += translationVector.mY;
        
        vertices[i].SetPos(Vector2i(x,y));
    }
    poly.SetVertices(vertices);
    sPolyList[polygonID] = poly;
}

deque<Polygon> ObjectEditor::GetPolygons()
{
    return sPolyList;
}
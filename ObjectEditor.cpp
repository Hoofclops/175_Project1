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
int ObjectEditor::sSelectedPoly;

ObjectEditor::ObjectEditor()
{
    sSelectedPoly = -1;
}

void ObjectEditor::CreatePolygon(deque<Vector2i> vertPositions, bool drawScene)
{
    Polygon poly = Polygon(vertPositions);
    sPolyList.push_back(poly);
    if(drawScene)
        Renderer::Instance()->DrawScene();
}

void ObjectEditor::TranslatePolygon(Vector2i translationVector, bool drawScene)
{
    if(sSelectedPoly == -1)
        CycleSelectedPoly(true);
    
    unsigned int id = sSelectedPoly;
    if(id >= sPolyList.size())
    {
        throw invalid_argument("Invalid Polygon ID");
    }
       
    deque<Point> vertices = sPolyList[sSelectedPoly].GetVertices();
    
    long n = vertices.size();
    for(int i = 0; i < n; i++)
    {
        int x = vertices[i].GetX(), y = vertices[i].GetY();
        x += translationVector.mX;
        y += translationVector.mY;
        
        vertices[i].SetX(x);
        vertices[i].SetY(y);
    }
    sPolyList[sSelectedPoly].SetVertices(vertices);
    
    if(drawScene)
        Renderer::Instance()->DrawScene();
}

void ObjectEditor::ScalePolygon(float scaleX, float scaleY, bool drawScene)
{
    if(sSelectedPoly == -1)
        CycleSelectedPoly(true);
    
    unsigned int id = sSelectedPoly;
    if(id >= sPolyList.size())
    {
        throw invalid_argument("Invalid Polygon ID");
    }
    
    Vector2i centroid = GraphicsAlgorithm::FindPolyCentroid(sPolyList[sSelectedPoly]);
    
    cout << "Centroid: " << centroid.mX << " ," << centroid.mY << endl;
    
    deque<Point> vertices = sPolyList[sSelectedPoly].GetVertices();
    
    long n = vertices.size();
    for(int i = 0; i < n; i++)
    {
        int x = vertices[i].GetX(), y = vertices[i].GetY();
        x = (x * scaleX) + (centroid.mX * (1 - scaleX));
        y = (y * scaleY) + (centroid.mY * (1 - scaleY));
        
        vertices[i].SetX(x);
        vertices[i].SetY(y);
    }
    sPolyList[sSelectedPoly].SetVertices(vertices);
    
    if(drawScene)
        Renderer::Instance()->DrawScene();
}

void ObjectEditor::RotatePolygon(double degrees, bool drawScene)
{
    if(sSelectedPoly == -1)
        CycleSelectedPoly(true);
    
    unsigned int id = sSelectedPoly;
    if(id >= sPolyList.size())
    {
        throw invalid_argument("Invalid Polygon ID");
    }
    
    Vector2i centroid = GraphicsAlgorithm::FindPolyCentroid(sPolyList[sSelectedPoly]);
    deque<Point> vertices = sPolyList[sSelectedPoly].GetVertices();
    double theta = degrees * (M_PI / 180);
    
    long n = vertices.size();
    for(int i = 0; i < n; i++)
    {
        int x = vertices[i].GetX(), y = vertices[i].GetY();
        double cosAngle = cos(theta);
        double sinAngle = sin(theta);
        double dx = x - centroid.mX;
        double dy = y - centroid.mY;
        
        x = centroid.mX + (int)(dx * cosAngle - dy * sinAngle);
        y = centroid.mY + (int)(dx * sinAngle + dy * cosAngle);
        
        vertices[i].SetX(x);
        vertices[i].SetY(y);
        
        cout << "vertex: " << x << ", " << y << endl;
    }
    sPolyList[sSelectedPoly].SetVertices(vertices);
    
    if(drawScene)
        Renderer::Instance()->DrawScene();
}

deque<Polygon> ObjectEditor::GetPolygons()
{
    return sPolyList;
}

void ObjectEditor::CycleSelectedPoly(bool forward)
{
    //Handle first selection
    if(sSelectedPoly == -1)
    {
        sSelectedPoly = 0;
        sPolyList[sSelectedPoly].SetSelected(true);
        Renderer::DrawScene();
        return;
    }
    
    if(forward)
    {
        sPolyList[sSelectedPoly].SetSelected(false);
        if(sSelectedPoly != sPolyList.size() - 1)
        {
            sSelectedPoly++;
        }
        else
        {
            sSelectedPoly = 0;
        }
        sPolyList[sSelectedPoly].SetSelected(true);
    }
    else
    {
        sPolyList[sSelectedPoly].SetSelected(false);
        if(sSelectedPoly != 0)
        {
            sSelectedPoly--;
        }
        else
        {
            sSelectedPoly = (int)(sPolyList.size() - 1);
        }
        sPolyList[sSelectedPoly].SetSelected(true);

    }
    
    Renderer::DrawScene();
}

void ObjectEditor::ClearPolygons()
{
    sPolyList.clear();
    sSelectedPoly = -1;
}



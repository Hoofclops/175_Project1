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
deque<Line> ObjectEditor::sLineList;
int ObjectEditor::sSelectedPoly;
Vector2i ObjectEditor::sMinClip;
Vector2i ObjectEditor::sMaxClip;

ObjectEditor::ObjectEditor()
{
    sSelectedPoly = -1;
    sMinClip = Vector2i(0,0);
    Vector2i screenSize = Renderer::Instance()->GetScreenSize();
    sMaxClip = Vector2i(screenSize.mX, screenSize.mY);
}

void ObjectEditor::CreatePolygon(deque<Vector2i> vertPositions)
{
    Polygon poly = Polygon(vertPositions);
    sPolyList.push_back(poly);
}

void ObjectEditor::CreateLine(Line line)
{
    sLineList.push_back(line);
}

void ObjectEditor::TranslatePolygon(Vector2i translationVector)
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
}

void ObjectEditor::ScalePolygon(float scaleX, float scaleY)
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
}

void ObjectEditor::RotatePolygon(double degrees)
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
    }
    sPolyList[sSelectedPoly].SetVertices(vertices);
}

deque<Polygon> ObjectEditor::GetPolygons()
{
    return sPolyList;
}

deque<Line> ObjectEditor::GetLines()
{
    return sLineList;
}

Vector2i ObjectEditor::GetMinClip()
{
    return sMinClip;
}

Vector2i ObjectEditor::GetMaxClip()
{
    return sMaxClip;
}

void ObjectEditor::CycleSelectedPoly(bool forward)
{
    //Handle first selection
    if(sSelectedPoly == -1)
    {
        if(sPolyList.size() == 0)
            return;
        
        sSelectedPoly = 0;
        sPolyList[sSelectedPoly].SetSelected(true);
        return;
    }
    
    if(forward)
    {
        sPolyList[sSelectedPoly].SetSelected(false);
        unsigned int selectedUnsigned = sSelectedPoly;
        if(selectedUnsigned != sPolyList.size() - 1)
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
}

void ObjectEditor::ClearData()
{
    sPolyList.clear();
    sLineList.clear();
    sSelectedPoly = -1;
}

void ObjectEditor::ClipScene(deque<Line> *clippedLines, deque<Polygon> *clippedPolys)
{
    long n = sLineList.size();
    for(unsigned int i = 0; i < n; i++)
    {
        Line l = sLineList[i];
        GraphicsAlgorithm::LineClipCohenSutherland(sMinClip, sMaxClip, &l);
        clippedLines->push_back(l);
    }
    
    n = sPolyList.size();
    for(unsigned int i = 0 ; i < n; i++)
    {
        Vector2i *pOut;
        pOut = new Vector2i[100];
        int count = GraphicsAlgorithm::PolygonClipSutherlandHodgman(sMinClip, sMaxClip, sPolyList[i], pOut);
        
        deque<Vector2i> vertices;
        for(int i = 0; i < count; i++)
        {
            Vector2i v = Vector2i(pOut[i].mX, pOut[i].mY);
            vertices.push_back(v);
        }
        Polygon p = Polygon(vertices);
        
        if(sPolyList[i].IsSelected())
            p.SetSelected(true);
        clippedPolys->push_back(p);
    }
}

void ObjectEditor::SetClip(Vector2i minClip, Vector2i maxClip)
{    
    sMinClip = minClip;
    sMaxClip = maxClip;
}


//
//  Renderer.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "Renderer.h"

Renderer* Renderer::sInstance;
Vector2i Renderer::sScreenSize;
float*  Renderer::sPixelBuffer;

Renderer::Renderer()
{
    sScreenSize = Vector2i(SCREEN_SIZE, SCREEN_SIZE);
    sPixelBuffer = new float[SCREEN_SIZE * SCREEN_SIZE * 3]; //Multiply by 3 for rgb, when changing this constant, be sure to change hard code in DrawPoint()
}

Vector2i Renderer::GetScreenSize()
{
    return sScreenSize;
}

void Renderer::SetScreenSize(Vector2i size)
{
    sScreenSize = size;
}

void Renderer::DrawPoint(Point point)
{
    int pixelStart = PosToIndex((point.GetPos()));
    
    Color color = point.GetColor();
    
    if(pixelStart >= 0 && pixelStart + 2 < SCREEN_SIZE * SCREEN_SIZE * 3)
    {
        sPixelBuffer[pixelStart] = color.GetRed();
        sPixelBuffer[pixelStart + 1] = color.GetGreen();
        sPixelBuffer[pixelStart + 2] = color.GetBlue();
    }
    else
    {
        throw out_of_range("Point outside of pixel buffer range");
    }
}

void Renderer::DrawLine(Line line, Algo algo)
{
    if(algo == DDA)
    {
        GraphicsAlgorithm::LineDDA(line);
    }
    else if(algo == BRESENHAM)
    {
        GraphicsAlgorithm::LineBresenham(line);
    }
}

void Renderer::DrawPolygon(Polygon poly)
{
    GraphicsAlgorithm::PolyScanLine(poly);
    
    deque<Line> edges = poly.GetEdges();
    //draw just the edges to cover top and right edges that weren't drawn by scan line
    long edgesCount = edges.size();
    for(int i = 0; i < edgesCount; i++)
    {
        GraphicsAlgorithm::LineDDA(edges[i]);
    }
}

int Renderer::PosToIndex(Vector2i pos)
{
    int width = sScreenSize.mX;
    
    return (pos.mX + width * pos.mY) * 3;
}

void Renderer::DrawScene()
{
    ClearBuffer();
    deque<Polygon> polys = ObjectEditor::Instance()->GetPolygons();

    cout << "Drawing Polygon" << endl;
    for(int i = 0; i < polys.size(); i++)
    {
        
        deque<Line> edges = polys[i].GetEdges();
        for(int j = 0; j < edges.size(); j++)
        {
            cout << edges[j].GetPointA().GetX() << ", ";
            cout << edges[j].GetPointA().GetY() << " --> ";
            
            cout << edges[j].GetPointB().GetX() << ", ";
            cout << edges[j].GetPointB().GetY() << endl;;
        }
    }
    
    Vector2i centroid = GraphicsAlgorithm::FindPolyCentroid(polys[0]);
    
    cout << "Centroid: " << centroid.mX << " ," << centroid.mY << endl;

    long n = polys.size();
    for(int i = 0; i < n; i++)
    {
        DrawPolygon(polys[i]);
    }
}

void Renderer::ClearBuffer()
{
    //sPixelBuffer = new float[SCREEN_SIZE * SCREEN_SIZE * 3];

    int n = SCREEN_SIZE * SCREEN_SIZE * 3;
    for(int i = 0; i < n; i++)
    {
        sPixelBuffer[i] = 0.0f;
    }
}

void Renderer::DisplayPixelBuffer()
{
    //Misc.
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();//load identity matrix
    
    //draws pixel on screen, width and height must match pixel buffer dimension
    glDrawPixels(sScreenSize.mX, sScreenSize.mY, GL_RGB, GL_FLOAT, sPixelBuffer);
    glEnd();
    glFlush();
}

//
//  Renderer.h
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Renderer__
#define __Project1__Renderer__

#define SCREEN_SIZE 800
#define CANVAS_RED 0
#define CANVAS_GREEN 0
#define CANVAS_BLUE 0

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "Vector2i.h"
#include "Color.h"
#include "Polygon.h"
#include "GraphicsAlgorithm.h"

//Should contain the pixel buffer and handle drawing of points, lines, and polygons
class Renderer
{
private:
    static Renderer* sInstance;
    static Vector2i  sScreenSize;
    static float*  sPixelBuffer;
    
    Renderer();
    
    //Convert coordinate position to appropriate array index in pixel buffer
    int PosToIndex(Vector2i pos);
    
public:
    
    enum Algo
    {
        DDA,
        BRESENHAM,
    };
    
    static Renderer* Instance()
    {
        if (!sInstance)
            sInstance = new Renderer;
        return sInstance;
    }
    
    Vector2i GetScreenSize();
    void SetScreenSize(Vector2i size);
    
    void DrawPoint(Point point);
    void DrawLine(Line line, Algo algo);
    void DrawPolygon(Polygon poly);
    
    static void ClearBuffer();
    
    static void DisplayPixelBuffer();
};

#endif /* defined(__Project1__Renderer__) */

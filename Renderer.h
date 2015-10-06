//
//  Renderer.h
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Renderer__
#define __Project1__Renderer__

#define SCREEN_SIZE 1000
#define CANVAS_RED 0
#define CANVAS_GREEN 0
#define CANVAS_BLUE 0

 #include <OpenGL/gl.h>
 #include <OpenGL/glu.h>
 #include <GLUT/glut.h>
//#include <GL/glut.h>
#include <iostream>
#include "Vector2i.h"
#include "Color.h"
#include "Polygon.h"
#include "GraphicsAlgorithm.h"
#include "ObjectEditor.h"

//Should contain the pixel buffer and handle drawing of points, lines, and polygons
class Renderer
{
private:
    static Renderer* sInstance;
    static Vector2i  sScreenSize;
    static float*  sPixelBuffer;
    
    Renderer();
    
    //Convert coordinate position to appropriate array index in pixel buffer
    static int PosToIndex(Vector2i pos);
    
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
    static void SetScreenSize(Vector2i size);
    
    static void DrawPoint(Point point);
    static void DrawLine(Line line, Algo algo);
    static void DrawPolygon(Polygon poly);
    
    static void ClearBuffer();
    
    static void DisplayPixelBuffer();

    static void DrawScene();
};

#endif /* defined(__Project1__Renderer__) */

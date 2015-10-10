//
//  GraphicsAlgorithm.h
//  Project1
//
//  Created by Brandon Nguyen on 9/27/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__GraphicsAlgorithm__
#define __Project1__GraphicsAlgorithm__

#include <cmath>
#include <deque>
#include <list>
#include "Point.h"
#include "Color.h"
#include "Line.h"
#include "Renderer.h"
#include "Polygon.h"

const GLint sBitCodeLeft = 0x1;
const GLint sBitCodeRight = 0x2;
const GLint sBitCodeTop = 0x4;
const GLint sBitCodeBottom = 0x8;

class GraphicsAlgorithm
{
private:
    //Bresenham helpers
    static int DetermineCase(float dy, float dx);
    static void HandlePositiveSlope(Point a, Point b, int dx, int dy);
    static void HandleNegativeSlope(Point a, Point b, int dx, int dy);
    
    //Scan line helpers
    struct ScanData
    {
    public:
        ScanData(){}
        ScanData(int ymin, int ymax, float xval, float slopeinverse)
        {
            yMin = ymin;
            yMax = ymax;
            xVal = xval;
            inverseSlope = slopeinverse;
        }
        
        int yMin;
        int yMax;
        float xVal;
        float inverseSlope;
    };
    static bool InitScanLineValues(Line line, ScanData* data);
    static void FillRemainingEdges(deque<Line> edges, list<ScanData> * remainingEdges);
    static bool SortActiveEdges(const ScanData first, const ScanData second);
    static void DrawScanLine(int curY, list<ScanData> activeEdges, bool drawGreen);
    
    //Cohen-Sutherland
    static GLint Inside(GLint code);
    static GLint Reject(GLint code1, GLint code2);
    static GLint Accept(GLint code1, GLint code2);
    static GLubyte Encode(Point point, Vector2i minClip, Vector2i maxClip);
    static void SwapPoints(Point *p1, Point *p2);
    static void SwapCodes(GLubyte *c1, GLubyte *c2);
    
    //Sutherland-Hodgman
    typedef enum {Left, Right, Bottom, Top} Boundary;
    static GLint InsidePoly(Vector2i p, Boundary b, Vector2i minClip, Vector2i maxClip);
    static GLint Cross(Vector2i p1, Vector2i p2, Boundary winEdge, Vector2i minClip, Vector2i maxClip);
    static Vector2i Intersect(Vector2i p1, Vector2i p2, Boundary winEdge, Vector2i minClip, Vector2i maxClip);
    static void ClipPoint(Vector2i p, Boundary winEdge, Vector2i minClip, Vector2i maxClip, Vector2i *pOut, int *cnt, deque<Vector2i> *first, Vector2i *s);
    static void CloseClip(Vector2i minClip, Vector2i maxClip, Vector2i *pOut, GLint *cnt, deque<Vector2i> *first, Vector2i *s);

public:
    static void LineDDA(Line line, bool drawGreen = false);
    static void LineBresenham(Line line);
    static void PolyScanLine(Polygon poly, bool drawGreen = false);
    static Vector2i FindPolyCentroid(Polygon poly);
    static void LineClipCohenSutherland(Vector2i minClip, Vector2i maxClip, Line *line);
    static int PolygonClipSutherlandHodgman(Vector2i minClip, Vector2i maxClip, Polygon poly, Vector2i *pOut);
};

#endif /* defined(__Project1__GraphicsAlgorithm__) */

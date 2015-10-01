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
#include "Line.h"
#include "Renderer.h"
#include "Polygon.h"

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
    static void DrawScanLine(int curY, list<ScanData> activeEdges);
public:
    static void LineDDA(Line line);
    static void LineBresenham(Line line);
    static void PolyScanLine(Polygon poly);
};

#endif /* defined(__Project1__GraphicsAlgorithm__) */

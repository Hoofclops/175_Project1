//
//  ObjectEditor.h
//  Project1
//
//  Created by Brandon Nguyen on 9/28/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__ObjectEditor__
#define __Project1__ObjectEditor__

#include <deque>
#include <math.h>
#include "Polygon.h"
#include "Line.h"
#include "Renderer.h"
#include "Vector2i.h"

class ObjectEditor
{
private:
    static ObjectEditor* sInstance;
    static deque<Polygon> sPolyList;
    static deque<Line> sLineList;
    static int sSelectedPoly;
    static Vector2i sMinClip;
    static Vector2i sMaxClip;
    
    ObjectEditor();
public:
    static ObjectEditor *Instance()
    {
        if (!sInstance)
            sInstance = new ObjectEditor;
        return sInstance;
    }
    
    static void CreatePolygon(deque<Vector2i> vertPositions, bool drawScene);
    static void CreateLine(Line line, bool drawScene);
    
    static void TranslatePolygon(Vector2i translationVector, bool drawScene);
    static void ScalePolygon(float scaleX, float scaleY, bool drawScene);
    static void RotatePolygon(double degrees, bool drawScene);

    static deque<Polygon> GetPolygons();
    static deque<Line> GetLines();
    static Vector2i GetMinClip();
    static Vector2i GetMaxClip();
        
    static void CycleSelectedPoly(bool forward);
    
    static void ClearData();
    static void ClipScene();
    static void ClipScene(Vector2i minClip, Vector2i maxClip, bool drawScene);

};



#endif /* defined(__Project1__ObjectEditor__) */

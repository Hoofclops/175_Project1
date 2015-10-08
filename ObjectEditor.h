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
#include "Renderer.h"

class ObjectEditor
{
private:
    static ObjectEditor* sInstance;
    static deque<Polygon> sPolyList;
    static int sSelectedPoly;
    
    ObjectEditor();
public:
    static ObjectEditor *Instance()
    {
        if (!sInstance)
            sInstance = new ObjectEditor;
        return sInstance;
    }
    
    static void CreatePolygon(deque<Vector2i> vertPositions, bool drawScene);
    
    static void TranslatePolygon(int polygonID, Vector2i translationVector, bool drawScene);
    static void ScalePolygon(int polygonID, float scaleX, float scaleY, bool drawScene);
    static void RotatePolygon(int polygonID, float degrees, bool drawScene);

    static deque<Polygon> GetPolygons();
        
    static void CycleSelectedPoly(bool forward);
};



#endif /* defined(__Project1__ObjectEditor__) */

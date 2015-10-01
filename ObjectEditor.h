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
#include "Polygon.h"
#include "Renderer.h"

class ObjectEditor
{
private:
    static ObjectEditor* sInstance;
    static deque<Polygon> sPolyList;
    static int sCurrentID;
    
    ObjectEditor();
    
public:
    static ObjectEditor *Instance()
    {
        if (!sInstance)
            sInstance = new ObjectEditor;
        return sInstance;
    }
    
    static void CreatePolygon(deque<Vector2i> vertPositions);
    
    static void TranslatePolygon(int polygonID, Vector2i translationVector);
    
    deque<Polygon> GetPolygons();
};



#endif /* defined(__Project1__ObjectEditor__) */

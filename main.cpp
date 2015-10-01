//
//  main.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/25/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "Vector2i.h"
#include "Renderer.h"
#include "ObjectEditor.h"
#include "InputOutputUtility.h"

float *PixelBuffer;
Vector2i ScreenSize = Vector2i(200, 200);

int main(int argc, char *argv[])
{
    
    ///////////////////////////////////////
    //TEST CODE////////////////////////////
    InputOutputUtility::Instance()->ParsePolygonFile();
//    ObjectEditor::Instance()->TranslatePolygon(0, Vector2i(10, 10));
    //END TEST/////////////////////////////
    ///////////////////////////////////////

    //test this shit
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    Vector2i screenSize = Renderer::Instance()->GetScreenSize();
    glutInitWindowSize(screenSize.mX, screenSize.mY);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("Project 1");
    glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
    glutDisplayFunc(Renderer::DisplayPixelBuffer);
    
    glutMainLoop();//main display loop, will display until terminate
    
    return 0;
}

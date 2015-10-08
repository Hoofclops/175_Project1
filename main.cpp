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
//#include <GL/glut.h>
#include "Vector2i.h"
#include "Renderer.h"
#include "ObjectEditor.h"
#include "InputOutputUtility.h"

float *PixelBuffer;
Vector2i ScreenSize = Vector2i(200, 200);

int main(int argc, char *argv[])
{
    InputOutputUtility::QueryWindowSize();
    
    ///////////////////////////////////////
    //TEST CODE////////////////////////////
//    InputOutputUtility::Instance()->ParsePolygonFile("poly.txt");
//    ObjectEditor::Instance()->TranslatePolygon(0, Vector2i(50, 50), true);
//    ObjectEditor::Instance()->ScalePolygon(0,3.0f, 3.0f, true);
//    ObjectEditor::Instance()->RotatePolygon(0, 10, true);
    //END TEST/////////////////////////////
    ///////////////////////////////////////
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    Vector2i screenSize = Renderer::Instance()->GetScreenSize();
    glutInitWindowSize(screenSize.mX, screenSize.mY);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("Project 1");
    glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
    glutDisplayFunc(Renderer::DisplayPixelBuffer);
    glutKeyboardFunc(InputOutputUtility::DetectInput);
    
    glutMainLoop();//main display loop, will display until terminate
    
    return 0;
}

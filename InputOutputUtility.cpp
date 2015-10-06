//
//  InputOutputUtility.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/28/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//
//  Code based off of code from http://cs.dvc.edu/HowTo_Cparse.html

#include "InputOutputUtility.h"

InputOutputUtility* InputOutputUtility::sInstance;

InputOutputUtility::InputOutputUtility(){}

void InputOutputUtility::QueryWindowSize()
{
    int xDim, yDim;
    
    cout << "Enter X window dimension: ";
    cin >> xDim;
    cout << "Enter Y window dimension: ";
    cin >> yDim;
    
    Renderer::Instance()->InitWindow(xDim, yDim);
}

void InputOutputUtility::ParsePolygonFile()
{
    ifstream fin;
//   fin.open("poly.txt");
     fin.open("//Users//BrandonHome//Desktop//175//Project1//Project1//poly.txt");
    if (!fin.good())
        throw runtime_error("Error opening poly.txt");
    
    const char* tokens[MAX_TOKENS] = {}; // initialize to 0
    deque<Vector2i> vertexPositions;
    
    while (!fin.eof())
    {
        char buf[MAX_LINE_LEN];
        fin.getline(buf, MAX_LINE_LEN);
        
        int i = 0;
        tokens[0] = strtok(buf, ", ");
        if (tokens[0]) // zero if line is blank
        {
            for (i = 1; i < MAX_TOKENS; i++)
            {
                tokens[i] = strtok(0, ", ");
                if (!tokens[i])
                    break;
            }
        }
        
        if(!tokens[0])
        {
            continue;
        }
        
        //Parse strings
        if(strcmp(tokens[0], "End") == 0 || strcmp(tokens[0], "end") == 0)
        {
            ObjectEditor::Instance()->CreatePolygon(vertexPositions, true);
            vertexPositions.clear();
        }
        else
        {
            int x = atoi(tokens[0]);
            int y = atoi(tokens[1]);
            vertexPositions.push_back(Vector2i(x, y));
        }
    }
}

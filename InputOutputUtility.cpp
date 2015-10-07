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
    cin.ignore();
    
    Renderer::Instance()->InitWindow(xDim, yDim);
}

void InputOutputUtility::DetectInput(unsigned char key, int xmouse, int ymouse)
{
    switch(key)
    {
            case 'i':
                ProcessInput();
    }
    
    glutPostRedisplay();
}

void InputOutputUtility::ProcessInput()
{
    string input;
    cout << "Enter command: ";
    
    getline(cin, input);
//    input = "Polygon (0,0) (100,100) (100,0)";
//    cout << endl << input << endl;
    
    deque<string> tokens = SplitString(input, string(" "));
    string command = tokens[0];
    tokens.pop_front();
    
    //Parse strings
    if(command == "Polygon")
    {
        ProcessCommandPolygon(tokens);
    }
    else if(command == "Line")
    {
    
    }
    else if(command == "Transform")
    {
        
    }
    else if(command == "Scale")
    {
        
    }
    else if(command == "Rotate")
    {
        
    }
    else if(command == "Clip")
    {
        
    }
    else if(command == "ReadFile")
    {
        
    }
    else if(command == "SaveToFile")
    {
        
    }
    else
    {
        cout << "Invalid command, please enter another command" << endl;
        return;
    }

//    Renderer::Instance()->DisplayPixelBuffer();
//    glutPostRedisplay();
}

void InputOutputUtility::ProcessCommandPolygon(deque<string> tokens)
{
    deque<Vector2i> vertexPositions;
    
    long n = tokens.size();
    for(int i = 0; i < n; i++)
    {
        deque<string> vertex = SplitString(tokens[i], string("(),"));

        if(vertex.size() != 2)
        {
            cout << "Invalid vertex format" << endl;
            return;
        }
        
        Vector2i vertPos = Vector2i(atoi(vertex[0].c_str()), atoi(vertex[1].c_str()));
        vertexPositions.push_back(Vector2i(vertPos.mX, vertPos.mY));
    }
    
    ObjectEditor::Instance()->CreatePolygon(vertexPositions, true);
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

deque<string> InputOutputUtility::SplitString(string s, string delims)
{
    deque<string> tokens;
    const char *str = s.c_str();
    do
    {
        const char *begin = str;
        
        while(*str)//(*str != c && *str)
        {
            
            //Search delims for current char
            size_t found = delims.find(*str);
            if (found != string::npos)
                break;
            
            str++;
        }
        
        string tok = string(begin, str);
        if(tok != "")
            tokens.push_back(string(begin, str));
        
    } while (0 != *str++);
    
    return tokens;

}
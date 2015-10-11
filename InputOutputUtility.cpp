//
//  InputOutputUtility.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/28/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//
//  Parse polygon file Code based off of code from http://cs.dvc.edu/HowTo_Cparse.html

#include "InputOutputUtility.h"

void InputOutputUtility::QueryWindowSize()
{
    int xDim, yDim;
    
    cout << "Enter X window dimension: ";
    cin >> xDim;
    cout << "Enter Y window dimension: ";
    cin >> yDim;
    cin.ignore();
    
    Renderer::Instance()->InitWindow(xDim + 1, yDim + 1);
}

void InputOutputUtility::DetectInput(unsigned char key, int xmouse, int ymouse)
{
    switch(key)
    {
            case 'i':
                ProcessInput();
            break;
            case 'I':
                ProcessInput();
            break;
            case 'n':
                ObjectEditor::Instance()->CycleSelectedPoly(true);
            break;
            case 'b':
                ObjectEditor::Instance()->CycleSelectedPoly(false);
            break;
    }
    
    Renderer::Instance()->DrawScene();
    glutPostRedisplay();
}

void InputOutputUtility::ProcessInput()
{
    string input;
    cout << "Enter command: ";
    getline(cin, input);
    
    deque<string> tokens = SplitString(input, string(" "));
    
    if(tokens.size() == 0)
    {
        return;
    }
    
    string command = tokens[0];
    tokens.pop_front();
    
    //Parse strings
    if(command == "Polygon" || command == "polygon")
    {
        ProcessCommandPolygon(tokens);
    }
    else if(command == "Line" || command == "line")
    {
        ProcessCommandLine(tokens);
    }
    else if(command == "Translate" || command == "translate")
    {
        ProcessCommandTranslate(tokens);
    }
    else if(command == "Scale" || command == "scale")
    {
        ProcessCommandScale(tokens);
    }
    else if(command == "Rotate" || command == "rotate")
    {
        ProcessCommandRotate(tokens);
    }
    else if(command == "Clip" || command == "clip")
    {
        ProcessCommandClip(tokens);
    }
    else if(command == "Load" || command == "load")
    {
        ProcessCommandLoadFile(tokens);
    }
    else if(command == "Save" || command == "save")
    {
        ProcessCommandSaveFile(tokens);
    }
    else if(command == "Clear" || command == "clear")
    {
        Renderer::Instance()->ClearBuffer();
        ObjectEditor::Instance()->ClearData();
    }
    else
    {
        cout << "Invalid command, please enter another command" << endl;
        return;
    }
}

void InputOutputUtility::ProcessCommandPolygon(deque<string> tokens)
{
    deque<Vector2i> vertexPositions = ExtractVertices(tokens);
    
    if(vertexPositions.size() == 0)
    {
        cout << "Invalid command" << endl;
        return;
    }
    ObjectEditor::Instance()->CreatePolygon(vertexPositions);
}

void InputOutputUtility::ProcessCommandLine(deque<string> tokens)
{
    string algo = tokens[0];
    tokens.pop_front();
    
    deque<Vector2i> vertexPositions = ExtractVertices(tokens);
    
    if(vertexPositions.size() != 2 ||
       (algo != "Bresenham" &&
        algo != "DDA"))
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    Line line = Line(Point(vertexPositions[0].mX, vertexPositions[0].mY), Point(vertexPositions[1].mX, vertexPositions[1].mY));
    line.SetAlgorithm(algo);
    ObjectEditor::Instance()->CreateLine(line);
}

void InputOutputUtility::ProcessCommandTranslate(deque<string> tokens)
{
    deque<Vector2i> vertexPositions = ExtractVertices(tokens);
    
    if(vertexPositions.size() != 1)
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    ObjectEditor::Instance()->TranslatePolygon(vertexPositions[0]);
}

void InputOutputUtility::ProcessCommandScale(deque<string> tokens)
{
    if(tokens.size() != 2)
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    float scaleX = stof(tokens[0]);
    float scaleY = stof(tokens[1]);
    
    ObjectEditor::Instance()->ScalePolygon(scaleX, scaleY);
}
void InputOutputUtility::ProcessCommandRotate(deque<string> tokens)
{
    if(tokens.size() != 1)
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    double degrees = stod(tokens[0]);
    
    ObjectEditor::Instance()->RotatePolygon(degrees);
}

void InputOutputUtility::ProcessCommandClip(deque<string> tokens)
{
    deque<Vector2i> vertexPositions = ExtractVertices(tokens);

    if(vertexPositions.size() != 2)
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    ObjectEditor::Instance()->SetClip(vertexPositions[0], vertexPositions[1]);
}

void InputOutputUtility::ProcessCommandLoadFile(deque<string> tokens)
{
    if(tokens.size() != 1)
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    ParsePolygonFile(tokens[0]);
}

void InputOutputUtility::ProcessCommandSaveFile(deque<string> tokens)
{
    if(tokens.size() != 1)
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    SavePolygonFile(tokens[0]);
}

void InputOutputUtility::ParsePolygonFile(string fileName)
{
    ifstream fin;
//   fin.open(fileName);
     fin.open("//Users//BrandonHome//Desktop//175//Project1//Project1//" + fileName);
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
            if(vertexPositions.size() == 2)
            {
                Line l = Line(Point(vertexPositions[0].mX, vertexPositions[0].mY),
                              Point(vertexPositions[1].mX, vertexPositions[1].mY));
                l.SetAlgorithm("DDA");
                ObjectEditor::Instance()->CreateLine(l);
            }
            else
            {
                ObjectEditor::Instance()->CreatePolygon(vertexPositions);
            }
            
            vertexPositions.clear();
        }
        else
        {
            int x = atoi(tokens[0]);
            int y = atoi(tokens[1]);
            vertexPositions.push_back(Vector2i(x, y));
        }
    }
    
    fin.close();
}

void InputOutputUtility::SavePolygonFile(string fileName)
{
    ofstream fout;
//    fout.open(fileName, ofstream::out | ofstream::trunc);
    fout.open("//Users//BrandonHome//Desktop//175//Project1//Project1//" + fileName, ofstream::out | ofstream::trunc);
    
    deque<Polygon> allPolys = ObjectEditor::Instance()->GetPolygons();
    deque<Line> allLines = ObjectEditor::Instance()->GetLines();
    
    long polyCount = allPolys.size();
    for(unsigned int i = 0; i < polyCount; i++)
    {
        deque<Point> vertices = allPolys[i].GetVertices();
        
        long vertexCount = vertices.size();
        for(unsigned int j = 0; j < vertexCount; j++)
        {
            fout << vertices[j].GetX() << "," << vertices[j].GetY() << "\n";
        }
        fout << "End" << "\n" << "\n";
    }
    
    long lineCount = allLines.size();
    for(unsigned int i = 0; i < lineCount; i++)
    {
        fout << allLines[i].GetPointA().GetX() << "," << allLines[i].GetPointA().GetY()<< "\n";
        fout << allLines[i].GetPointB().GetX() << "," << allLines[i].GetPointB().GetY()<< "\n";
        fout << "End" << "\n" << "\n";
    }
    
    fout.close();
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

deque<Vector2i> InputOutputUtility::ExtractVertices(deque<string> tokens)
{
    deque<Vector2i> vertexPositions;
    
    long n = tokens.size();
    for(int i = 0; i < n; i++)
    {
        deque<string> vertex = SplitString(tokens[i], string("(),"));
        
        if(vertex.size() != 2)
        {
            cout << "Invalid vertex format" << endl;
            vertexPositions.clear();
            return vertexPositions;
        }
        
        Vector2i vertPos = Vector2i(atoi(vertex[0].c_str()), atoi(vertex[1].c_str()));
        vertexPositions.push_back(Vector2i(vertPos.mX, vertPos.mY));
    }
    
    return vertexPositions;
}

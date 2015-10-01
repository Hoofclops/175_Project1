//
//  GraphicsAlgorithm.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/27/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//
//  Code for DDA algorithm taken from text book page:
//  Code for Bresenham based off of code from text book page:
//  Scan Line Algorithm based off of one described on http://www.cs.rit.edu/~icss571/filling/index.html

#include "GraphicsAlgorithm.h"

/*TODO: 
refactor HandleNegativeSlope() and HandlePositiveSlope()
*/

/****************************
 *BRESENHAM HELPER FUNCTIONS*
 ****************************/

int GraphicsAlgorithm::DetermineCase(float dy, float dx)
{
    float m;
    
    if(dx == 0)
    {
        return 1;
    }
    
    m = dy / dx;
    if(m == 0 || m == 1 || m == -1)
    {
        return 1;
    }
    else if(m > 0)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

void GraphicsAlgorithm::HandlePositiveSlope(Point a, Point b, int dx, int dy)
{
    int x = a.GetX(), xEnd = b.GetX(), y = a.GetY(), yEnd = b.GetY();
    int p = 2 * dy - dx;
    float m = (float)dy / (float)dx;
    
    //Draw starting point
    Renderer::Instance()->DrawPoint(Point(x,y));
    
    if(m < 1)
    {
        int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
        //increment in x direction
        while(x < xEnd)
        {
            x++;
            if(p < 0)
            {
                p += twoDy;
            }
            else
            {
                y++;
                p += twoDyMinusDx;
            }
            Renderer::Instance()->DrawPoint(Point(x,y));
        }
    }
    else //flip x and y roles if m > 1
    {
        int twoDx = 2 * dx, twoDxMinusDy = 2 * (dx - dy);
        //increment in y direction
        while(y < yEnd)
        {
            y++;
            if(p < 0)
            {
                p += twoDx;
            }
            else
            {
                x++;
                p += twoDxMinusDy;
            }
            Renderer::Instance()->DrawPoint(Point(x,y));
        }
    }
}

void GraphicsAlgorithm::HandleNegativeSlope(Point a, Point b, int dx, int dy)
{
    int x = a.GetX(), xEnd = b.GetX(), y = a.GetY(), yEnd = b.GetY();
    
    //get absolute values so p is calculated correctly
    dy = fabs(dy);
    dx = fabs(dx);
    
    int p = 2 * dy - dx;
    float m = (float)dy / (float)dx;
    
    //Draw starting point
    Renderer::Instance()->DrawPoint(Point(x,y));
    
    if(m < 1)
    {
        int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
        //increment in x direction
        while(x < xEnd)
        {
            x++;
            if(p < 0)
            {
                p += twoDy;
            }
            else
            {
                y--;
                p += twoDyMinusDx;
            }
            Renderer::Instance()->DrawPoint(Point(x,y));
        }
    }
    else
    {
        int twoDx = 2 * dx, twoDxMinusDy = 2 * (dx - dy);
        //increment in y direction
        while(y > yEnd)
        {
            y--;
            if(p < 0)
            {
                p += twoDx;
            }
            else
            {
                x++;
                p += twoDxMinusDy;
            }
            Renderer::Instance()->DrawPoint(Point(x,y));
        }
    }
}

/*******************
 *SCAN LINE HELPERS*
 *******************/

bool GraphicsAlgorithm::InitScanLineValues(Line line, ScanData* data)
{
    int yMin, yMax;
    float xVal, inverseSlope;
    int x1 = line.GetPointA()->GetX(), y1 = line.GetPointA()->GetY(),
        x2 = line.GetPointB()->GetX(), y2 = line.GetPointB()->GetY();
    
    //Fill y values
    if(y1 == y2)
    {
        //dont fill values if horizontal line
        return false;
    }
    else if(y2 > y1)
    {
        yMax = y2;
        yMin = y1;
        xVal = x1;
    }
    else
    {
        yMax = y1;
        yMin = y2;
        xVal = x2;
    }

    //Find inverse slope
    inverseSlope = ((float)(x2 - x1)) / ((float)(y2 - y1));
    
    //fill values
    data->yMin = yMin;
    data->yMax = yMax;
    data->xVal = xVal;
    data->inverseSlope = inverseSlope;
    return true;
}

void GraphicsAlgorithm::FillRemainingEdges(deque<Line> edges, list<ScanData> * remainingEdges)
{
    //add first valid edge to remainingEdges
    bool foundFirst = false;
    while(!foundFirst)
    {
        ScanData data;
        if(InitScanLineValues(edges[0], &data))
        {
            foundFirst = true;
            remainingEdges->push_back(data);
        }
        edges.pop_front();
    }
    
    //Add and sort the rest to remainingEdges
    while(edges.size() != 0)
    {
        ScanData data;
        if(InitScanLineValues(edges[0], &data))
        {
            //valid, non horiontal line, find where to insert
            list<ScanData>::iterator iter = remainingEdges->begin();
            for(unsigned int i = 0; i < edges.size(); i++)
            {
                //When we've reached end of list
                if(i == remainingEdges->size())
                {
                    remainingEdges->insert(iter, data);
                    break;
                }
                
                float yMinCur = iter->yMin,
                xValCur = iter->xVal;
                
                if(data.yMin > yMinCur ||
                   (data.yMin == yMinCur &&
                    data.xVal > xValCur))
                {
                    iter++;
                }
                else
                {
                    remainingEdges->insert(iter, data);
                    break;
                }
            }
        }
        
        edges.pop_front();
    }
}

bool GraphicsAlgorithm::SortActiveEdges(const ScanData first, const ScanData second)
{
    //sort by xVal
    return first.xVal < second.xVal;
}

void GraphicsAlgorithm::DrawScanLine(int curY, list<ScanData> activeEdges)
{
    int curX = activeEdges.front().xVal;
    long totIntersections = activeEdges.size();
    int curIntersections = 0;
    bool parity = true;
    
    
    while(curIntersections != totIntersections)
    {
        //count intersections
        int intersected = 0;
        for(list<ScanData>::iterator it = activeEdges.begin(); it != activeEdges.end(); it++)
        {
            int xInt = (int)(it->xVal + 0.5f); // cast to int
            if(xInt == curX)
                intersected++;
        }
        
        //for each hit intersection: flip parity, increment curIntersections and it
        for(int i = 0; i < intersected; i++)
        {
            parity = !parity;
            
            if(!parity)
            {
                Renderer::Instance()->DrawPoint(Point(curX, curY));
            }
            
            curIntersections++;
        }
        
        if(intersected == 0)
        {
            if(!parity)
            {
                Renderer::Instance()->DrawPoint(Point(curX, curY));
            }
        }
        
        curX++;
    }
}

/**************************
 *ALGORITHM IMPLEMENTATION*
 **************************/

void GraphicsAlgorithm::LineDDA(Line line)
{
    Renderer *renderer = Renderer::Instance();
    Point a = *line.GetPointA(), b = *line.GetPointB();
    
    int dx = b.GetPos().mX - a.GetPos().mX,
        dy = b.GetPos().mY - a.GetPos().mY, steps;
    float xIncrement, yIncrement, x = a.GetPos().mX, y = a.GetPos().mY;
    
    //determine which direction steps will orient towards
    if(fabs(dx) > fabs(dy))
    {
        steps = fabs(dx);
    }
    else
    {
        steps = fabs(dy);
    }
    
    //initialize increments
    xIncrement = (float)dx / (float)steps;
    yIncrement = (float)dy / (float)steps;
    
    //draw first point
    renderer->DrawPoint(Point(nearbyint(x), nearbyint(y)));
    
    //draw each subsequent point, incrementing along the way
    for(int i = 0; i < steps; i++)
    {
        x += xIncrement;
        y += yIncrement;
        
        renderer->DrawPoint(Point(nearbyint(x), nearbyint(y)));
    }
}

void GraphicsAlgorithm::LineBresenham(Line line)
{
    Point a = *line.GetPointA(), b = *line.GetPointB();
    //Ensure a -> b goes left to right
    if(a.GetX() > b.GetX())
    {
        Point t = a;
        a = b;
        b = t;
    }
    
    float dx = (float)(b.GetX() - a.GetX()),
          dy = (float)(b.GetY() - a.GetY());

    //Determine case and draw line
    int c = DetermineCase(dy, dx);
    switch(c)
    {
        case 1:
            //horizontal, vertical, or m = 1
            LineDDA(line);
            break;
        case 2:
            //m > 0
            HandlePositiveSlope(a, b, dx, dy);
            break;
        case 3:
            //m < 0
            HandleNegativeSlope(a, b, dx, dy);
            break;
    }
}

void GraphicsAlgorithm::PolyScanLine(Polygon poly)
{
    list<ScanData> remainingEdges;
    list<ScanData> activeEdges;
    
    FillRemainingEdges(poly.GetEdges(), &remainingEdges);
    
    //initialize current Y scan value
    int curY = remainingEdges.front().yMin;
    
    while(true)
    {
        //fill and sort active edges
        list<ScanData>::iterator it = remainingEdges.begin();
        while(it != remainingEdges.end())
        {
            if(curY == it->yMin)
            {
                activeEdges.push_back((*it));
                it = remainingEdges.erase(it);
            }
            else
            {
                it++;
            }
        }
        activeEdges.sort(SortActiveEdges);
        
        //Draw Scan Line
        DrawScanLine(curY, activeEdges);
        
        //increment Y
        curY++;
        
        //increment all x values
        for(list<ScanData>::iterator it = activeEdges.begin(); it != activeEdges.end(); it++)
        {
            it->xVal += it->inverseSlope;
        }
         
        //remove all edges that have a max y value == curent scan line y value
        it = activeEdges.begin();
        while(it != activeEdges.end())
        {
            if(curY == it->yMax)
            {
                it = activeEdges.erase(it);
            }
            else
            {
                it++;
            }
        }
        
        //check for finish condition
        if(activeEdges.size() == 0)
        {
            break;
        }
    }
}

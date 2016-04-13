#pragma once
#include "OGLLine.h"
#include <Windows.h>
#include <gl/GL.h>

OGLLine::OGLLine(Color3ub color) : m_color(color), m_selectedPoint(NULL)
{
}

OGLLine::~OGLLine(void)
{
}

bool Collinear(Point2d p1, Point2d selected, Point2d p2)
{
    double threshold = 1;
    double shouldBeZero = Point2d::Distance(p1, selected) + Point2d::Distance(selected, p2) - Point2d::Distance(p1, p2);
    if(shouldBeZero < threshold)
        return true;
    else
        return false;
}


void OGLLine::Render()
{
    glColor3ub(m_color.R(), m_color.G(), m_color.B());
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    //keep previous point
    //check if selected is on the line pPrev,p
    Point2d pPrev;
    for each(Point2d p in m_pointList)
    {
        if(m_selectedPoint != NULL && Collinear(pPrev, *m_selectedPoint, p))
            glColor3ub(255 - m_color.R(), 255 - m_color.G(), 255 - m_color.B());
        else if(m_selectedPoint != NULL)
            glColor3ub(m_color.R(), m_color.G(), m_color.B());
        pPrev = p;
        glVertex2d(p.X(), p.Y());
    }
    glEnd();
}

void OGLLine::AddPoint(Point2d p)
{
    m_pointList.push_back(p);
}

void OGLLine::RemovePoint(Point2d p)
{
}


void OGLLine::SetSelected(Point2d p)
{
    if(m_selectedPoint != NULL)
    {
        delete m_selectedPoint;
        m_selectedPoint = NULL;
    }
    m_selectedPoint = new Point2d(p.X(), p.Y());
}

bool OGLLine::MouseMove(int x, int y)
{
    return true;
}

bool OGLLine::MouseLBUp(int x, int y)
{
    return true;
}

bool OGLLine::MouseLBDown(int x, int y)
{
    return true;
}
#include "OGLBar.h"
#include "Point2d.h"
#include <Windows.h>
#include <gl/GL.h>

OGLBar::OGLBar(double x, double width, double height, Color3ub color):
    m_bottomLeft(Point2d(x, 0)), m_bottomRight(Point2d(x + width, 0)), m_topRight(Point2d(x + width, height)),
    m_topLeft(Point2d(x, height)), m_color(color), m_isSelected(false)
{
}

OGLBar::OGLBar(Point2d bottomLeft, Point2d bottomRight, Point2d topRight, Point2d topLeft, Color3ub color):
    m_bottomLeft(bottomLeft), m_bottomRight(bottomRight), m_topRight(topRight), m_topLeft(topLeft), m_color(color), m_isSelected(false)
{
}


OGLBar::~OGLBar(void)
{
}

void OGLBar::Render()
{
    if(!m_isSelected)
        glColor3ub(m_color.R(), m_color.G(), m_color.B());
    else
        glColor3ub(255 - m_color.R(), 255 - m_color.G(), 255 - m_color.B());
    glBegin(GL_QUADS);
    glVertex2d(m_bottomLeft.X(), m_bottomLeft.Y());
    glVertex2d(m_bottomRight.X(), m_bottomRight.Y());
    glVertex2d(m_topRight.X(), m_topRight.Y());
    glVertex2d(m_topLeft.X(), m_topLeft.Y());
    glEnd();
    glRasterPos2i(m_bottomLeft.X(), m_bottomLeft.Y() - 12);
    if(!m_isSelected)
        glColor3ub(m_color.R(), m_color.G(), m_color.B());
    else
        glColor3ub(255 - m_color.R(), 255 - m_color.G(), 255 - m_color.B());
    // display a string:
    // indicate start of glyph display lists
    glListBase(1000);
    // now draw the characters in a string
    glCallLists(m_name.size(), GL_UNSIGNED_SHORT, m_name.c_str());
}

bool OGLBar::ContainsPoint(int x, int y)
{
    bool xValid = x >= m_bottomLeft.X() && x <= m_bottomRight.X();
    bool yValid = y >= m_bottomLeft.Y() && y <= m_topLeft.Y();
    return xValid && yValid;
}

void OGLBar::SetSelected(bool yes)
{
    m_isSelected = yes;
}
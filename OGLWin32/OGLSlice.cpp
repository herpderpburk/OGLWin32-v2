#include "OGLSlice.h"
#include "Color3ub.h"
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>


OGLSlice::OGLSlice(double radius, double p1, double p2, Color3ub color) : m_start(p1),
    m_end(p2), m_color(color), m_radius(radius), m_isSelected(false)
{
}

OGLSlice::~OGLSlice(void)
{
}

void OGLSlice::Render()
{
    if(!m_isSelected)
        glColor3ub(m_color.R(), m_color.G(), m_color.B());
    else
        glColor3ub(255 - m_color.R(), 255 - m_color.G(), 255 - m_color.B());
    int circlePoints = 500;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);
    for(double i = m_start; i < m_end; i += PI / circlePoints)
    {
        glVertex3d(cos(i) * m_radius, sin(i) * m_radius, 0.0);
    }
    glEnd();
}

bool OGLSlice::ContainsPoint(int x, int y)
{
    double radius = sqrt(pow(x, 2) + pow(y, 2));
    if(m_radius < radius)
        return false;
    double angle = atan2(y, x);
    if(angle < 0)
        angle = 2 * PI + angle;
    double angleInDegrees = angle * 180 / PI;
    if(angle >= m_start && angle <= m_end)
        return true;
    else
        return false;
}

void OGLSlice::SetSelected(bool yes)
{
    m_isSelected = yes;
}
#include "OGLChart.h"
#include <Windows.h>
#include <gl/GL.h>

using namespace std;

OGLChart::OGLChart(void)
{
    m_zoomValue = 1.0f;
}


OGLChart::~OGLChart(void)
{
}

void OGLChart::SetSize(int w, int h)
{
    m_chartWidth = w;
    m_chartHeight = h;
}

void OGLChart::DrawCoordinateAxes()
{
    float offset = 20.0f;
    glTranslatef(-m_chartWidth / 2.0f + offset, -m_chartHeight / 2 + offset, 0);
    glColor3ub(255, 255, 255);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2i(-offset, 0);
    glVertex2i(m_chartWidth, 0);
    glVertex2i(0, -offset);
    glVertex2i(0, m_chartHeight);
    glEnd();
}

void OGLChart::DrawStr(double x, double y, Color3ub color, wstring text)
{
    glColor3ub(color.R(), color.G(), color.B());
    glRasterPos2i(x, y);
    glColor3ub(color.R(), color.G(), color.B());
    glListBase(1000);
    glCallLists(text.size(), GL_UNSIGNED_SHORT, text.c_str());
}

void OGLChart::ToOGLCoordinates(int& x, int& y)
{
    double offset = 20;
    //from window to lower left corner
    x = x - offset;
    y =  -y + m_chartHeight - offset;
    //un-scale (I'm missing something here)
    double zoomedWidth = (m_chartWidth) * m_zoomValue;
    double diffWidth = (m_chartWidth) - zoomedWidth;
    x -= diffWidth / 2;
    double zoomedHeigt = (m_chartHeight) * m_zoomValue;
    double diffHeight = (m_chartHeight) - zoomedHeigt;
    y -= diffHeight / 2;
    //un-translate
    x = x - m_translateX;
    y = y - m_translateY;
}
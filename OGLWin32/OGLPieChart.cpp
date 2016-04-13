#include "OGLPieChart.h"
#include "Color3ub.h"
#include <Windows.h>
#include <gl/GL.h>
using namespace std;

OGLPieChart::OGLPieChart()
{
}


OGLPieChart::~OGLPieChart(void)
{
}

void OGLPieChart::SetSize(int width, int height)
{
    //half the screen minus some offset
    int offset = 10;
    m_radius = (width > height) ? height / 2 - offset : width / 2 - offset;
    m_chartHeight = height;
    m_chartWidth = width;
}

void OGLPieChart::GenerateSlices(std::map<std::wstring, double> *data)
{
    double firstPoint = 0.0f;
    for(auto it = data->begin(); it != data->end(); ++it)
    {
        double secondPoint = firstPoint + it->second * PI / 50;
        OGLSlice *s = new OGLSlice(m_radius, firstPoint, secondPoint, Color3ub::random());
        s->SetName(it->first);
        m_slices.push_back(s);
        firstPoint = secondPoint;
    }
}

void OGLPieChart::Render()
{
    for(auto it = m_slices.begin(); it != m_slices.end(); it++)
        (*it)->Render();
    DrawLegend();
}

void OGLPieChart::DrawLegend()
{
    //draw the legend in the upper left corner
    float startX = -m_chartWidth / 2 + 20;
    float startY =  m_chartHeight / 2 - 20;
    float rectSize = 10;
    for each(auto slice in m_slices)
    {
        //get name
        //get color
        //draw rect using the color
        //draw text
        wstring name = slice->GetName();
        Color3ub color = slice->GetColor();
        glColor3ub(color.R(), color.G(), color.B());
        glRectf(startX, startY, startX + rectSize, startY + rectSize);
        glRasterPos2i(startX + 20, startY);
        glColor3ub(color.R(), color.G(), color.B());
        // display a string:
        // indicate start of glyph display lists
        glListBase(1000);
        // now draw the characters in a string
        glCallLists(name.size(), GL_UNSIGNED_SHORT, name.c_str());
        startY -= rectSize * 2;
    }
}

void OGLPieChart::ToOGLCoordinates(int& x, int& y)
{
    x = (x - m_chartWidth / 2 - m_translateX) / m_zoomValue;
    y = (-y + m_chartHeight / 2 - m_translateY) / m_zoomValue;
}

bool OGLPieChart::MouseMove(int x, int y)
{
    return true;
}

bool OGLPieChart::MouseLBUp(int x, int y)
{
    ToOGLCoordinates(x, y);
    for each(auto slice in m_slices)
    {
        slice->SetSelected(slice->ContainsPoint(x, y));
    }
    return true;
}

bool OGLPieChart::MouseLBDown(int x, int y)
{
    return true;
}
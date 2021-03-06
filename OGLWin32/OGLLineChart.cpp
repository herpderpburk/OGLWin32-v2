#include "OGLLineChart.h"
#include <Windows.h>
#include <gl/GL.h>
#include <map>
#include <sstream>
using namespace std;

OGLLineChart::OGLLineChart()
{
    m_oxMax = 0;
    m_oyMax = 0;
    m_oxMin = 0;
    m_oyMin = 0;
    m_textColor = Color3ub(255, 0, 0);
}

OGLLineChart::~OGLLineChart(void)
{
}

void OGLLineChart::Render()
{
    DrawCoordinateAxes();
    DrawLegend();
    RenderLines();
}

void OGLLineChart::GenerateLines(map<double, double> *data)
{
    //find ox and oy max values
    //calculate plot values based on the screen size, point value and max
    m_lines.clear();
    OGLLine *line = new OGLLine(Color3ub::random());
    for(auto it = data->begin(); it != data->end(); ++it)
    {
        m_oxMax = m_oxMax < it->first ? it->first : m_oxMax;
        m_oyMax = m_oyMax < it->second ? it->second : m_oyMax;
        m_oxMin = m_oxMin >= it->first ? it->first : m_oxMin;
        m_oyMin = m_oyMin >= it->second ? it->second : m_oyMin;
    }
    for(auto it = data->begin(); it != data->end(); ++it)
    {
        Point2d p(it->first * m_chartWidth / m_oxMax, it->second * m_chartHeight / m_oyMax);
        line->AddPoint(p);
    }
    m_lines.push_back(line);
}

void OGLLineChart::RenderLines()
{
    for each(OGLLine * line in m_lines)
    {
        line->Render();
    }
}


void OGLLineChart::DrawLegend()
{
    //draw a few strings on the ox axis
    double start = 0;
    int pointCount = 5;
    double stepX = m_chartWidth / pointCount;
    for(int i = 1; i <= pointCount; i++)
    {
        double value = m_oxMax / pointCount * i;
        double positionX = start + stepX * i;
        wostringstream strs;
        strs << value;
        DrawStr(positionX, -10, m_textColor, strs.str());
    }
    //and on the oy
    start = 0;
    double stepY = m_chartHeight / pointCount;
    for(int i = 1; i <= pointCount; i++)
    {
        double value = m_oyMax / pointCount * i;
        double positionY = start + stepY * i;
        wostringstream strs;
        strs << value;
        DrawStr(-20, positionY, m_textColor, strs.str());
    }
}

bool OGLLineChart::MouseMove(int x, int y)
{
    return true;
}

bool OGLLineChart::MouseLBUp(int x, int y)
{
    ToOGLCoordinates(x, y);
    for each(OGLLine * line in m_lines)
    {
        line->SetSelected(Point2d(x, y));
    }
    return true;
}

bool OGLLineChart::MouseLBDown(int x, int y)
{
    return true;
}
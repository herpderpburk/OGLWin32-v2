#include "OGLBarChart.h"
#include "Color3ub.h"
#include "Point2d.h"
#include <Windows.h>
#include <gl/GL.h>
#include <string>
using namespace std;

OGLBarChart::OGLBarChart(void)
{
    m_hasAxes = true;
}


OGLBarChart::~OGLBarChart(void)
{
}

void OGLBarChart::GenerateBars(std::map<std::wstring, double> *data)
{
    //clear array
    //count bars to fit
    //compute the width based on the nuber of bars
    //get max height
    //calculate bar height based on window height and max height
    m_bars.clear();
    int barDistance = 10;
    int barCount = data->size();
    //double barWidth = ((this->m_chartWidth) / barCount - barDistance) > 10 ? ((this->m_chartWidth) / barCount - barDistance)  : 30;
    double barWidth = 30;
    double firstPoint = 1.0f;
    double maxBarValue = 0;
    for(auto it = data->begin(); it != data->end(); ++it)
    {
        maxBarValue = maxBarValue < it->second ? it->second : maxBarValue;
    }
    for(auto it = data->begin(); it != data->end(); ++it)
    {
        double barHeight = it->second * m_chartHeight / maxBarValue;
        OGLBar *bar = new OGLBar(firstPoint, barWidth, barHeight, Color3ub::random());
        bar->SetName(it->first);
        m_bars.push_back(bar);
        firstPoint += barWidth + barDistance;
    }
}

void OGLBarChart::Render()
{
    DrawCoordinateAxes();
    for each(auto bar in m_bars)
    {
        bar->Render();
    }
}

bool OGLBarChart::MouseMove(int x, int y)
{
    return true;
}

bool OGLBarChart::MouseLBUp(int x, int y)
{
    ToOGLCoordinates(x, y);
    for each(auto bar in m_bars)
    {
        bar->SetSelected(bar->ContainsPoint(x, y));
    }
    return true;
}
bool OGLBarChart::MouseLBDown(int x, int y)
{
    return true;
}
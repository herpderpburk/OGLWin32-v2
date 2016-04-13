#pragma once
#include "OGLChart.h"
#include "OGLLine.h"
#include <vector>
#include <map>
#include "Color3ub.h"
/*
Line Chart
• Data instances are
connected by line segments
• Visualise how an attribute
changes against another
independent attribute
• E.g. cartilage NIR
absorbance data; the
absorbance attribute is
dependent on the
wavenumber
*/

class OGLLineChart : public OGLChart
{
private:
    double m_oxMax;
    double m_oyMax;
    double m_oxMin;
    double m_oyMin;

    std::vector<OGLLine *> m_lines;

    Color3ub m_textColor;
public:
    OGLLineChart();
    ~OGLLineChart(void);

    void DrawLegend();
    void RenderLines();
    void GenerateLines(std::map<double, double> *data);
    void Render();
    bool MouseMove(int x, int y);
    bool MouseLBUp(int x, int y);
    bool MouseLBDown(int x, int y);
};


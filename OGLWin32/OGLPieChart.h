#pragma once
#include "OGLChart.h"
#include <vector>
#include <map>
#include <string>
#include "OGLSlice.h"
/*
Pie Chart
• Each sector represents the
data instances associated
with a specific category
• Sector angle is determined
by the number of
occurrence over the entire
population
• E.g. using Edu
(qualification) attribute from
the adult test data
*/


class OGLPieChart : public OGLChart
{

private:
    std::vector<OGLSlice *> m_slices;
    double m_radius;
    void DrawLegend();

public:
    OGLPieChart();
    ~OGLPieChart();
    void SetSize(int width, int height);
    void GenerateSlices(std::map<std::wstring, double> *data);

    void Render();
    bool MouseMove(int x, int y);
    bool MouseLBUp(int x, int y);
    bool MouseLBDown(int x, int y);
    void ToOGLCoordinates(int& x, int& y);
};


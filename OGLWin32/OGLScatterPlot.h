#pragma once
#include "OGLChart.h"
#include "Point2d.h"
#include <vector>
#include <map>

/*
Scatter Plot
� Each data instance
occupies a location in
space, e.g. Cartesian
coordinate system
� Data instances from different
categories can be
distinguished using different
colour and/or shapes
*/
class OGLScatterPlot : public OGLChart
{

private:
    std::vector<Point2d> m_pointList;
    int pointSize;
    double m_oxMax;
    double m_oyMax;
    double m_oxMin;
    double m_oyMin;

    Color3ub m_textColor;
    Color3ub m_color;
    Point2d *m_selectedPoint;

public:
    OGLScatterPlot(void);
    ~OGLScatterPlot(void);
    void GeneratePlots(std::map<double, double> *data);
    void Render();
    void DrawLegend();
    bool MouseMove(int x, int y);
    bool MouseLBUp(int x, int y);
    bool MouseLBDown(int x, int y);
};


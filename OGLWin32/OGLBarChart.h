#pragma once
#include "OGLChart.h"
#include "OGLBar.h"
#include <vector>
#include <map>

/*
Bar Chart
• Each bar represents data
instances associated with a
specific category
• Visualise the number of
occurrence
• Bar height is determined by
the instance count
• Commonly used as
histogram
*/

class OGLBarChart : public OGLChart
{
private:
    std::vector<OGLBar *> m_bars;
public:
    OGLBarChart(void);
    ~OGLBarChart(void);
    void GenerateBars(std::map<std::wstring, double> *data);
    void Render();
    bool MouseMove(int x, int y);
    bool MouseLBUp(int x, int y);
    bool MouseLBDown(int x, int y);
};


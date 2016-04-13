#pragma once
#include "Renderable.h"
#include "Listener.h"
#include "Color3ub.h"
#include <string>
class OGLChart :
    public Renderable, public Listener
{
protected:
    int m_chartWidth;
    int m_chartHeight;
    bool m_hasAxes;
    double m_zoomValue;
    double m_translateX, m_translateY;

public:
    OGLChart(void);
    ~OGLChart(void);
    virtual void SetSize(int w, int h);
    void DrawCoordinateAxes();

    //from windows to our coordinate system (lower left corner is zero)
    void ToOGLCoordinates(int& x, int& y);

    void DrawStr(double x, double y, Color3ub color, std::wstring text);
    void setZoom(double by)
    {
        m_zoomValue = by;
    }
    void setTranslate(double x, double y)
    {
        m_translateX = x;
        m_translateY = y;
    }
};


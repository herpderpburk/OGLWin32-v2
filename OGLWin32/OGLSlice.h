#pragma once
#include "Renderable.h"
#include "Color3ub.h"
#include <string>
#define PI 3.1415926535898


class OGLSlice : public Renderable
{
private:
    double m_start; //point on the circle having radius one (2*PI/3)
    double m_end; //point on the circle having radius one  (2*PI)
    Color3ub m_color;
    double m_radius;
    std::wstring m_name;
    bool m_isSelected;
public:
    OGLSlice(double radius, double p1, double p2, Color3ub color);
    ~OGLSlice(void);

    void SetName(std::wstring name)
    {
        m_name = name;
    }

    std::wstring GetName()
    {
        return m_name;
    }

    Color3ub GetColor()
    {
        return m_color;
    }

    void			Render();
    bool ContainsPoint(int x, int y);
    void SetSelected(bool yes);
};


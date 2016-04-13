#pragma once
#include "renderable.h"
#include "Point2d.h"
#include "Color3ub.h"
#include <string>

class OGLBar : public Renderable
{
    Point2d m_bottomLeft;
    Point2d m_bottomRight;
    Point2d m_topRight;
    Point2d m_topLeft;
    Color3ub m_color;
    std::wstring m_name;
    bool m_isSelected;
public:
    OGLBar(double x, double width, double height, Color3ub color);
    OGLBar(Point2d, Point2d, Point2d, Point2d, Color3ub);
    ~OGLBar(void);
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
    void Render();
    bool ContainsPoint(int x, int y);
    void SetSelected(bool yes);

};


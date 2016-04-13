#pragma once
#include "renderable.h"
#include "Listener.h"
#include "Point2d.h"
#include "Color3ub.h"
#include <vector>

class OGLLine :
    public Renderable, public Listener
{
private:
    std::vector<Point2d> m_pointList;
    void SortPoints();
    Color3ub m_color;
    Point2d *m_selectedPoint;

public:
    OGLLine(Color3ub);
    ~OGLLine(void);
    void AddPoint(Point2d p);
    void RemovePoint(Point2d p);


    void SetSelected(Point2d p);
    void Render();
    bool MouseMove(int x, int y);
    bool MouseLBUp(int x, int y);
    bool MouseLBDown(int x, int y);
};


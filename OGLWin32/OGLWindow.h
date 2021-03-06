#pragma once

#include <Windows.h>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "OGLRectangle.h"
#include "OGLData.h"
#include "OGLChart.h"


class OGLWindow
{
    HWND m_hwnd;				//handle to a window
    HWND m_hParent;
    HDC	m_hdc;				//handle to a device context
    HGLRC m_hglrc;			//handle to a gl rendering context

    int	m_width;
    int	m_height;

    double m_zoomValue;

    double m_panX, m_panY;
    double m_oldX, m_oldY;

    OGLChart *m_chart;
    OGLWindow();

protected:
    HGLRC CreateOGLContext(HDC hdc);
    BOOL DestroyOGLContext();
    void InitOGLState();
public:

    OGLWindow(HINSTANCE hInstance, int width, int height);
    ~OGLWindow();
    BOOL InitWindow(HINSTANCE hInstance, HWND hParent);
    void SetVisible(BOOL visible);
    void DestroyOGLWindow();

    HWND GetHWND()
    {
        return m_hwnd;
    }

    void DisplayPie(std::map<std::wstring, double> *);
    void DisplayBar(std::map<std::wstring, double> *data);
    void DisplayLine(std::map<double, double> *data);
    void DisplayScatterPlot(std::map<double, double> *data);

    void SetViewport(int width, int height);
    void SetPosition(int x, int y, int width, int height);
    void Render();
    void Resize(int width, int height);

    BOOL MouseLBDown(int x, int y);
    BOOL MouseLBUp(int x, int y);
    BOOL MouseMove(int x, int y, WPARAM wparam);
    BOOL MouseWheel(int x, int y, int scroll);

private:
    void ResetZoomPan(void);
    void Zoom(double factor);
    void Pan(double dx, double dy);
    void ZoomAt(double x, double y, double factor);
};
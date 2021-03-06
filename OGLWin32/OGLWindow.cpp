#include "OGLWindow.h"
#include "OGLApplication.h"
#include "Resource.h"
#include "OGLScatterPlot.h"
#include "OGLPieChart.h"
#include "OGLBarChart.h"
#include "OGLLineChart.h"
#include <string>
#include <math.h>
#include <iostream>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <CommCtrl.h>
using namespace std;

OGLWindow::OGLWindow()
{
}

OGLWindow::~OGLWindow()
{
}

OGLWindow::OGLWindow(HINSTANCE hInstance, int width, int height) : m_width(width), m_height(height), m_chart(NULL)
{
}

HGLRC OGLWindow::CreateOGLContext(HDC hdc)
{
    unsigned int pixelformat;
    HGLRC hglrc;
    static PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
        1,											// Version Number
        PFD_DRAW_TO_WINDOW |						// Format Support Window
        PFD_SUPPORT_OPENGL |						// Format Support OpenGL
        PFD_DOUBLEBUFFER,							// Must Support Double Buffering
        PFD_TYPE_RGBA,								// Request RGBA Format
        32,											// Color Depth
        0, 0, 0, 0, 0, 0,							// Color Bits mask
        0,											// No Alpha Buffer
        0,											// Shift Bit Ignored
        0,											// No Accumulation Buffer
        0, 0, 0, 0,									// Accumulation Bits Ignored
        16,											// Z-Buffer depth
        0,											// Stencil Buffer
        0,											// Auxiliary Buffer
        PFD_MAIN_PLANE,								// Main Drawing Layer
        0,											// Reserved
        0, 0, 0										// Layer Masks Ignored
    };
    if(!(pixelformat = ChoosePixelFormat(hdc, &pfd)))
    {
        return 0;
    }
    if(!SetPixelFormat(hdc, pixelformat, &pfd))
    {
        return 0;
    }
    if(!(hglrc = wglCreateContext(hdc)))
    {
        return 0;
    }
    if(!wglMakeCurrent(hdc, hglrc))
    {
        return 0;
    }
    return hglrc;
}

void OGLWindow::DestroyOGLWindow()
{
    DestroyOGLContext();
    DestroyWindow(m_hwnd);
    m_hwnd = NULL;
    m_hdc = NULL;
}

BOOL OGLWindow::DestroyOGLContext()
{
    if(m_chart != NULL)
    {
        delete m_chart;
        m_chart = NULL;
    }
    if(m_hglrc)
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(m_hglrc);
        m_hglrc = NULL;
    }
    if(!ReleaseDC(m_hwnd, m_hdc))
        return FALSE;
    return TRUE;
}

BOOL OGLWindow::InitWindow(HINSTANCE hInstance, HWND hParent)
{
    m_hParent = hParent;
    m_hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
                            L"OGLWindow", L"OGLWindow", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                            0, 0, m_width, m_height, m_hParent, NULL, hInstance, NULL);
    if(! m_hwnd)
        return FALSE;
    m_hdc = GetDC(m_hwnd);
    if(!(m_hglrc = CreateOGLContext(m_hdc)))
        return FALSE;
    SetViewport(m_width, m_height);
    // make the system font the device context's selected font
    SelectObject(m_hdc, GetStockObject(SYSTEM_FIXED_FONT));
    // create the bitmap display lists
    // we're making images of glyphs 0 thru 254
    // the display list numbering starts at 1000, an arbitrary choice
    BOOL res = wglUseFontBitmaps(m_hdc, 0, 255, 1000);
    while(res == FALSE)
    {
        DWORD err = GetLastError();
        wcout << "wglUseFontBitmaps last error " << err << endl;
        res = wglUseFontBitmaps(m_hdc, 0, 255, 1000);
    }
    ResetZoomPan();
    return TRUE;
}

void OGLWindow::SetPosition(int x, int y, int width, int height)
{
    ::SetWindowPos(m_hwnd, 0, x, y, width, height, SWP_NOZORDER);
    if(m_chart)
        m_chart->SetSize(width, height);
}

void OGLWindow::SetVisible(BOOL visible)
{
    ShowWindow(m_hwnd, visible ? SW_SHOW : SW_HIDE);
}

void OGLWindow::DisplayPie(std::map<std::wstring, double> *data)
{
    if(m_chart != NULL)
    {
        delete m_chart;
        m_chart = NULL;
    }
    //Instantiate a Renderable as OGLRectangle
    m_chart = new OGLPieChart();
    m_chart->SetSize(m_width, m_height);
    ResetZoomPan();
    ((OGLPieChart *)m_chart)->GenerateSlices(data);
}

void OGLWindow::DisplayBar(std::map<std::wstring, double> *data)
{
    if(m_chart != NULL)
    {
        delete m_chart;
        m_chart = NULL;
    }
    //Instantiate a Renderable as OGLRectangle
    m_chart = new OGLBarChart();
    m_chart->SetSize(m_width, m_height);
    ResetZoomPan();
    ((OGLBarChart *)m_chart)->GenerateBars(data);
}

void OGLWindow::DisplayLine(std::map<double, double> *data)
{
    if(m_chart != NULL)
    {
        delete m_chart;
        m_chart = NULL;
    }
    //Instantiate a Renderable as OGLRectangle
    m_chart = new OGLLineChart();
    m_chart->SetSize(m_width, m_height);
    ResetZoomPan();
    ((OGLLineChart *)m_chart)->GenerateLines(data);
}

void OGLWindow::DisplayScatterPlot(std::map<double, double> *data)
{
    if(m_chart != NULL)
    {
        delete m_chart;
        m_chart = NULL;
    }
    //Instantiate a Renderable as OGLRectangle
    m_chart = new OGLScatterPlot();
    m_chart->SetSize(m_width, m_height);
    ResetZoomPan();
    ((OGLScatterPlot *)m_chart)->GeneratePlots(data);
}


void OGLWindow::SetViewport(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-0.5 * width, 0.5 * width, -0.5 * height, 0.5 * height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGLWindow::Resize(int width, int height)
{
    SetViewport(width, height);
    m_height = height;
    m_width = width;
}

void OGLWindow::InitOGLState()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void OGLWindow::Render()
{
    Renderable *prenderable = static_cast<Renderable *>(m_chart);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(m_panX, m_panY, 1.0f);
    glScalef(m_zoomValue, m_zoomValue, 1.0);
    if(m_chart)
    {
        m_chart->setTranslate(m_panX, m_panY);
        m_chart->setZoom(m_zoomValue);
        prenderable->Render();
    }
    glFlush();
    SwapBuffers(m_hdc);
    return;
}

void OGLWindow::ResetZoomPan(void)
{
    m_zoomValue = 1.0;
    m_panX = 1.0;
    m_panY = 1.0;
    if(m_chart)
    {
        m_chart->setTranslate(m_panX, m_panY);
        m_chart->setZoom(m_zoomValue);
    }
}

void OGLWindow::Zoom(double factor)
{
    m_zoomValue *= factor;
    m_panX *= factor;
    m_panY *= factor;
}

void OGLWindow::Pan(double dx, double dy)
{
    m_panX += dx;
    m_panY += dy;
}

void OGLWindow::ZoomAt(double x, double y, double factor)
{
    Pan(-x, -y);
    Zoom(factor);
    Pan(x, y);
}

BOOL OGLWindow::MouseLBDown(int x, int y)
{
    if(!m_chart)
        return FALSE;
    Listener *plistener = static_cast<Listener *>(m_chart);
    plistener->MouseLBDown(x, y);
    return TRUE;
}

BOOL OGLWindow::MouseLBUp(int x, int y)
{
    if(!m_chart)
        return FALSE;
    Listener *plistener = static_cast<Listener *>(m_chart);
    plistener->MouseLBUp(x, y);
    return TRUE;
}

BOOL OGLWindow::MouseMove(int x, int y, WPARAM wparam)
{
    if(!m_chart)
        return FALSE;
    if(wparam == MK_LBUTTON && m_oldX != 0 && m_oldY != 0)
    {
        double dX = -m_oldX + x;
        double dY = m_oldY - y;
        Pan(dX, dY);
        m_oldX = x;
        m_oldY = y;
    }
    else if(wparam == MK_LBUTTON)
    {
        m_oldX = x;
        m_oldY = y;
    }
    else
    {
        m_oldX = 0;
        m_oldY = 0;
    }
    Listener *plistener = static_cast<Listener *>(m_chart);
    plistener->MouseMove(x, y);
    return TRUE;
}

BOOL OGLWindow::MouseWheel(int x, int y, int scroll)
{
    if(!m_chart)
        return FALSE;
    const double factor = 1.5;
    bool zoomIn = scroll > 0 ? true : false;
    //x, y when 0 is in the center
    x = -m_width / 2 + x;
    y = m_height / 2 - y;
    if(zoomIn)
        //ZoomAt(x, y, factor);
        Zoom(factor);
    else
        //ZoomAt(x, y, 1/factor);
        Zoom(1 / factor);
    return TRUE;
}
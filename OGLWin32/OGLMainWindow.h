#pragma once
#include <Windows.h>
#include "OGLData.h"
#include "OGLDialogWindow.h"
#include "OGLWindow.h"

class OGLMainWindow
{
    HWND		m_hwnd;
    int			m_width;
    int			m_height;

    OGLDialogWindow *m_oglDialog;
    OGLWindow *m_oglWindow;

    OGLMainWindow(void);

    void LoadData(std::wstring fileName);
    OGLData *m_data;

public:
    OGLMainWindow(HINSTANCE hInstance, int width, int height);
    ~OGLMainWindow(void);

    HWND GetHWND()
    {
        return m_hwnd;
    }

    BOOL InitWindow(HINSTANCE hInstance);
    void DestroyWindow();

    void SetVisible(BOOL visible);

    void Resize(int width, int height, HWND hWnd);
    BOOL MouseLBDown(int x, int y);
    BOOL MouseLBUp(int x, int y);
    BOOL MouseMove(int x, int y, WPARAM wparam);
    BOOL MouseWheel(int x, int y, int scroll);
    BOOL FileOpen();

    BOOL InitPiePropertiesDialog(HWND hDlg);
    BOOL InitBarPropertiesDialog(HWND hDlg);
    BOOL InitLineChartPropertiesDialog(HWND hDlg);
    BOOL InitScatterPlotPropertiesDialog(HWND hDlg);

    void DisplayPie(int categoryCol, int dataCol);
    void DisplayBar(int firstCol, int secondCol);
    void DisplayLine(int firstCol, int secondCol);
    void DisplayScatterPlot(int firstCol, int secondCol);
    void DisplayListViewData();
    void ClearDataList();
    void Render();

};


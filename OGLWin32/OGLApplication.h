#pragma once

#include <Windows.h>

class OGLMainWindow;

//Define OGLApplication as a singleton
class OGLApplication
{
private:
    OGLMainWindow					*m_appwnd;

    BOOL						m_terminate;
    static OGLApplication		*s_oglapp;

    OGLApplication();
    virtual						~OGLApplication();
    void						CreateApplicationWindow(int width, int height);
    BOOL						MyRegisterClass(HINSTANCE hinst);

public:

    HINSTANCE					m_hInst;

    static OGLApplication		*CreateApplication(HINSTANCE hInst);
    static void					DestroyApplication();
    static OGLApplication		*GetApplication();


    int							Run();

    void						Kill();


    inline OGLMainWindow			*GetApplicationWindow()
    {
        return m_appwnd;
    }

    static	LRESULT CALLBACK	WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
    static  INT_PTR CALLBACK	DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static  INT_PTR CALLBACK	PiePropertiesDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static  INT_PTR CALLBACK	BarPropertiesDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static  INT_PTR CALLBACK	LineChartPropertiesDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static  INT_PTR CALLBACK	ScatterPlotPropertiesDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

};
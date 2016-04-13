#pragma once
#include <Windows.h>
class OGLData;
class OGLDialogWindow
{
    HWND m_hwnd;
    HWND m_hwndParent;
    int			m_width;
    int			m_height;
    OGLDialogWindow(void);

public:
    ~OGLDialogWindow(void);
    BOOL InitWindow(HINSTANCE hInstance, HWND hParent);
    void DestroyDialog();
    OGLDialogWindow(HINSTANCE hInstance, int width, int height);
    void Resize(int width, int height);
    HWND GetHWND()
    {
        return m_hwnd;
    }
    BOOL MouseLBDown(int x, int y);
    BOOL MouseLBUp(int x, int y);
    BOOL MouseMove(int x, int y);
    void SetPosition(int x, int y, int width, int height);
    void SetVisible(BOOL visible);
    void ClearList();
    void DisplayData(OGLData *data);

};


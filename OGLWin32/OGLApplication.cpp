#include "OGLApplication.h"
#include "OGLMainWindow.h"
#include "Resource.h"
#include <Windowsx.h>
#include <iostream>
using namespace std;

OGLApplication *OGLApplication::s_oglapp = NULL;

OGLApplication::OGLApplication()
{
    m_appwnd = NULL;
    m_hInst = 0;
    m_terminate = FALSE;
}

OGLApplication::~OGLApplication()
{
    if(m_appwnd)
        delete m_appwnd;
}

BOOL OGLApplication::MyRegisterClass(HINSTANCE hinst)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= this->WndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hinst;
    wcex.hIcon			= LoadIcon(hinst, MAKEINTRESOURCE(IDI_OGLWIN32));
    wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_OGLWIN32);
    wcex.lpszClassName	= L"OGLWindow";
    wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    if(!RegisterClassEx(&wcex))
        return FALSE;
    return TRUE;
}

OGLApplication *OGLApplication::CreateApplication(HINSTANCE hinst)
{
    if(! s_oglapp)
    {
        s_oglapp = new OGLApplication();
        s_oglapp->m_hInst = hinst;
        s_oglapp->MyRegisterClass(hinst);
        //Now create an OGLWindow for this application
        s_oglapp->CreateApplicationWindow(1024, 768);
    }
    return s_oglapp;
}

void OGLApplication::DestroyApplication()
{
    if(s_oglapp)
        delete s_oglapp;
}

OGLApplication *OGLApplication::GetApplication()
{
    return s_oglapp;
}

void OGLApplication::CreateApplicationWindow(int width, int height)
{
    if(!m_appwnd)
    {
        m_appwnd = new OGLMainWindow(m_hInst, width, height);
        m_appwnd->InitWindow(m_hInst);
    }
}

int OGLApplication::Run()
{
    MSG msg;
    while(!m_terminate)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            //peek for windows message
            if(msg.message == WM_QUIT)
            {
                Kill();
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            //don't eat all cpu
            ::Sleep(10);
            //get the OGLWindow to render stuff;
            m_appwnd->Render();
        }
    }
    return (int) msg.wParam;
}

void OGLApplication::Kill()
{
    m_terminate = TRUE;
}

INT_PTR CALLBACK OGLApplication::PiePropertiesDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
        s_oglapp->GetApplicationWindow()->InitPiePropertiesDialog(hwndDlg); //populate the comboboxes
        return TRUE;
    case WM_COMMAND:
        switch(wParam)
        {
        case IDOK:
            //get selections and setup Pie
        {
            HWND hFirstCombo = GetDlgItem(hwndDlg, IDC_COMBO_CATEGORY);
            HWND hSecondCombo = GetDlgItem(hwndDlg, IDC_COMBO_DATA);
            int categoryCol = ComboBox_GetCurSel(hFirstCombo);
            int dataCol = ComboBox_GetCurSel(hSecondCombo);
            s_oglapp->GetApplicationWindow()->DisplayPie(categoryCol, dataCol);
        }
        case IDCANCEL:
            EndDialog(hwndDlg, wParam);
            return TRUE;
        }
    default:
        return FALSE;
    }
    return FALSE;
}

INT_PTR CALLBACK OGLApplication::BarPropertiesDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
        s_oglapp->GetApplicationWindow()->InitBarPropertiesDialog(hwndDlg); //populate the comboboxes
        return TRUE;
    case WM_COMMAND:
        switch(wParam)
        {
        case IDOK:
            //get selections and setup BarChart
        {
            HWND hFirstCombo = GetDlgItem(hwndDlg, IDC_COMBO_CATEGORY);
            HWND hSecondCombo = GetDlgItem(hwndDlg, IDC_COMBO_DATA);
            int firstCol = ComboBox_GetCurSel(hFirstCombo);
            int secondCol = ComboBox_GetCurSel(hSecondCombo);
            s_oglapp->GetApplicationWindow()->DisplayBar(firstCol, secondCol);
        }
        case IDCANCEL:
            EndDialog(hwndDlg, wParam);
            return TRUE;
        }
    default:
        return FALSE;
    }
    return FALSE;
}

INT_PTR CALLBACK OGLApplication::LineChartPropertiesDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
        s_oglapp->GetApplicationWindow()->InitLineChartPropertiesDialog(hwndDlg); //populate the comboboxes
        return TRUE;
    case WM_COMMAND:
        switch(wParam)
        {
        case IDOK:
            //get selections and setup line chart
        {
            HWND hFirstCombo = GetDlgItem(hwndDlg, IDC_COMBO_CATEGORY);
            HWND hSecondCombo = GetDlgItem(hwndDlg, IDC_COMBO_DATA);
            int firstCol = ComboBox_GetCurSel(hFirstCombo);
            int secondCol = ComboBox_GetCurSel(hSecondCombo);
            s_oglapp->GetApplicationWindow()->DisplayLine(firstCol, secondCol);
        }
        case IDCANCEL:
            EndDialog(hwndDlg, wParam);
            return TRUE;
        }
    default:
        return FALSE;
    }
    return FALSE;
}

INT_PTR CALLBACK OGLApplication::ScatterPlotPropertiesDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
        s_oglapp->GetApplicationWindow()->InitScatterPlotPropertiesDialog(hwndDlg); //populate the comboboxes
        return TRUE;
    case WM_COMMAND:
        switch(wParam)
        {
        case IDOK:
            //get selections and setup scatter plot
        {
            HWND hFirstCombo = GetDlgItem(hwndDlg, IDC_COMBO_CATEGORY);
            HWND hSecondCombo = GetDlgItem(hwndDlg, IDC_COMBO_DATA);
            int firstCol = ComboBox_GetCurSel(hFirstCombo);
            int secondCol = ComboBox_GetCurSel(hSecondCombo);
            s_oglapp->GetApplicationWindow()->DisplayScatterPlot(firstCol, secondCol);
        }
        case IDCANCEL:
            EndDialog(hwndDlg, wParam);
            return TRUE;
        }
    default:
        return FALSE;
    }
    return FALSE;
}

INT_PTR CALLBACK OGLApplication::DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_COMMAND:
        switch(wParam)
        {
        case IDC_BUTTON_PIE:
            if(DialogBox(GetApplication()->m_hInst,
                         MAKEINTRESOURCE(IDD_PIE_CHART),
                         hwndDlg,
                         (DLGPROC)PiePropertiesDialogProc) == IDOK)
            {
                //TODO: stuff
                return TRUE;
            }
            break;
        case IDC_BUTTON_BAR:
            if(DialogBox(GetApplication()->m_hInst,
                         MAKEINTRESOURCE(IDD_BAR_CHART),
                         hwndDlg,
                         (DLGPROC)BarPropertiesDialogProc) == IDOK)
            {
                return TRUE;
            }
            break;
        case IDC_BUTTON_SCATTER:
            if(DialogBox(GetApplication()->m_hInst,
                         MAKEINTRESOURCE(IDD_BAR_CHART),
                         hwndDlg,
                         (DLGPROC)ScatterPlotPropertiesDialogProc) == IDOK)
            {
                return TRUE;
            }
            break;
        case IDC_BUTTON_LINE:
            if(DialogBox(GetApplication()->m_hInst,
                         MAKEINTRESOURCE(IDD_BAR_CHART),
                         hwndDlg,
                         (DLGPROC)LineChartPropertiesDialogProc) == IDOK)
            {
                return TRUE;
            }
            break;
        case IDC_VIEW_DATA:
        {
            HWND hCheck = GetDlgItem(hwndDlg, IDC_VIEW_DATA);
            if(Button_GetCheck(hCheck) == TRUE)
                s_oglapp->GetApplicationWindow()->DisplayListViewData();
            else
                s_oglapp->GetApplicationWindow()->ClearDataList();
        }
        }
        break;
    case WM_SIZE:
        s_oglapp->GetApplicationWindow()->Resize(LOWORD(lParam), HIWORD(lParam), hwndDlg);
        break;
    default:
        return FALSE;
    }
    return FALSE;
}

LRESULT CALLBACK OGLApplication::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    int wmId, wmEvent;
    switch(msg)
    {
    case WM_COMMAND:
        wmId    = LOWORD(wparam);
        wmEvent = HIWORD(wparam);
        // Parse the menu selections:
        switch(wmId)
        {
        case IDM_ABOUT:
            break;
        case IDM_EXIT:
            s_oglapp->GetApplicationWindow()->DestroyWindow();
            break;
        case ID_FILE_OPEN:
            s_oglapp->GetApplicationWindow()->FileOpen();
            break;
        default:
            return DefWindowProc(hwnd, msg, wparam, lparam);
        }
        break;
    case WM_SIZE:
        s_oglapp->GetApplicationWindow()->Resize(LOWORD(lparam), HIWORD(lparam), hwnd);
        break;
    case WM_CLOSE:
        s_oglapp->GetApplicationWindow()->DestroyWindow();
        break;
    case WM_MOUSEMOVE:
        //inform the cursor position to OGLWindow
        //TODO: add button pressed info
        s_oglapp->GetApplicationWindow()->MouseMove(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam), wparam);
        break;
    case WM_LBUTTONUP:
        s_oglapp->GetApplicationWindow()->MouseLBUp(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
        break;
    case WM_LBUTTONDOWN:
        s_oglapp->GetApplicationWindow()->MouseLBDown(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
        break;
    case WM_MOUSEWHEEL:
        s_oglapp->GetApplicationWindow()->MouseWheel(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam), GET_WHEEL_DELTA_WPARAM(wparam));
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
    return 0;
}
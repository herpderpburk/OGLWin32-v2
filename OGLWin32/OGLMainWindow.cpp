#include "OGLMainWindow.h"
#include "OGLApplication.h"
#include "resource.h"
#include <Windowsx.h>


OGLMainWindow::OGLMainWindow(HINSTANCE hInstance, int width, int height) : m_width(width), m_height(height)
{
    m_data = new OGLData();
    m_oglDialog = new OGLDialogWindow(hInstance, 0, 0);
    m_oglWindow = new OGLWindow(hInstance, 0, 0);
}

OGLMainWindow::~OGLMainWindow(void)
{
}

BOOL OGLMainWindow::InitWindow(HINSTANCE hInstance)
{
    //main
    m_hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
                            L"OGLWindow", L"OGLWindow", WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                            0, 0, m_width, m_height, NULL, NULL, hInstance, NULL);
    if(! m_hwnd)
        return FALSE;
    m_oglDialog->InitWindow(hInstance, m_hwnd);
    m_oglWindow->InitWindow(hInstance, m_hwnd);
    m_oglDialog->SetPosition(0, 2 / 3 * m_height, m_width, m_height / 3);
    m_oglWindow->SetPosition(0, 0, m_width, 2 * m_height / 3);
    Resize(m_width, m_height, m_hwnd);
    SetVisible(TRUE);
    return TRUE;
}

BOOL OGLMainWindow::InitPiePropertiesDialog(HWND hDlg)
{
    HWND hFirstCombo = GetDlgItem(hDlg, IDC_COMBO_CATEGORY);
    HWND hSecondCombo = GetDlgItem(hDlg, IDC_COMBO_DATA);
    for(int i = 0; i < m_data->ColumnCount(); i++)
    {
        ComboBox_AddString(hFirstCombo, m_data->GetStringAt(0, i).c_str());
        ComboBox_AddString(hSecondCombo, m_data->GetStringAt(0, i).c_str());
    }
    return TRUE;
}

BOOL OGLMainWindow::InitBarPropertiesDialog(HWND hDlg)
{
    HWND hFirstCombo = GetDlgItem(hDlg, IDC_COMBO_CATEGORY);
    HWND hSecondCombo = GetDlgItem(hDlg, IDC_COMBO_DATA);
    for(int i = 0; i < m_data->ColumnCount(); i++)
    {
        ComboBox_AddString(hFirstCombo, m_data->GetStringAt(0, i).c_str());
        ComboBox_AddString(hSecondCombo, m_data->GetStringAt(0, i).c_str());
    }
    return TRUE;
}

BOOL OGLMainWindow::InitLineChartPropertiesDialog(HWND hDlg)
{
    HWND hFirstCombo = GetDlgItem(hDlg, IDC_COMBO_CATEGORY);
    HWND hSecondCombo = GetDlgItem(hDlg, IDC_COMBO_DATA);
    for(int i = 0; i < m_data->ColumnCount(); i++)
    {
        ComboBox_AddString(hFirstCombo, m_data->GetStringAt(0, i).c_str());
        ComboBox_AddString(hSecondCombo, m_data->GetStringAt(0, i).c_str());
    }
    return TRUE;
}

BOOL OGLMainWindow::InitScatterPlotPropertiesDialog(HWND hDlg)
{
    HWND hFirstCombo = GetDlgItem(hDlg, IDC_COMBO_CATEGORY);
    HWND hSecondCombo = GetDlgItem(hDlg, IDC_COMBO_DATA);
    for(int i = 0; i < m_data->ColumnCount(); i++)
    {
        ComboBox_AddString(hFirstCombo, m_data->GetStringAt(0, i).c_str());
        ComboBox_AddString(hSecondCombo, m_data->GetStringAt(0, i).c_str());
    }
    return TRUE;
}

void OGLMainWindow::DestroyWindow()
{
    m_oglDialog->DestroyDialog();
    m_oglWindow->DestroyOGLWindow();
    ::DestroyWindow(m_hwnd);
}

void OGLMainWindow::SetVisible(BOOL visible)
{
    m_oglDialog->SetVisible(visible);
    m_oglWindow->SetVisible(visible);
    ShowWindow(m_hwnd, visible ? SW_SHOW : SW_HIDE);
}

void OGLMainWindow::Resize(int width, int height, HWND hWnd)
{
    //route the event to the window it is adressed
    if(hWnd == m_hwnd)
    {
        m_oglDialog->SetPosition(0, 2 * height / 3, width, height / 3);
        m_oglWindow->SetPosition(0, 0, width, 2 * height / 3);
    }
    else if(hWnd == m_oglDialog->GetHWND())
        m_oglDialog->Resize(width, height);
    else if(hWnd == m_oglWindow->GetHWND())
        m_oglWindow->Resize(width, height);
}

BOOL OGLMainWindow::FileOpen()
{
    OPENFILENAME ofn;       // common dialog box structure
    wchar_t szFile[260];       // buffer for file name
    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_hwnd;
    ofn.lpstrFile = szFile;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Csv\0*.CSV\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    // Display the Open dialog box.
    if(GetOpenFileName(&ofn) == TRUE)
    {
        wstring result(ofn.lpstrFile);
        LoadData(result);
        return TRUE;
    }
    return FALSE;
}

void OGLMainWindow::LoadData(wstring fileName)
{
    if(fileName == L"")
        return;
    m_data->ParseData(fileName);
}

void OGLMainWindow::DisplayListViewData()
{
    m_oglDialog->DisplayData(m_data);
}

void OGLMainWindow::ClearDataList()
{
    m_oglDialog->ClearList();
}

void OGLMainWindow::Render()
{
    m_oglWindow->Render();
}

void OGLMainWindow::DisplayPie(int categoryCol, int dataCol)
{
    std::map<std::wstring, double> *result;
    result = m_data->CalculatePieSlices(categoryCol, dataCol);
    m_oglWindow->DisplayPie(result);
    delete result;
}

void OGLMainWindow::DisplayBar(int firstCol, int secondCol)
{
    std::map<std::wstring, double> *result;
    result = m_data->CalculateBars(firstCol, secondCol);
    m_oglWindow->DisplayBar(result);
}

void OGLMainWindow::DisplayLine(int firstCol, int secondCol)
{
    std::map<double, double> *result;
    result = m_data->CalculatePlots(firstCol, secondCol);
    m_oglWindow->DisplayLine(result);
}

void OGLMainWindow::DisplayScatterPlot(int firstCol, int secondCol)
{
    std::map<double, double> *result;
    result = m_data->CalculatePlots(firstCol, secondCol);
    m_oglWindow->DisplayScatterPlot(result);
}

BOOL OGLMainWindow::MouseLBDown(int x, int y)
{
    return m_oglWindow->MouseLBDown(x, y);
}

BOOL OGLMainWindow::MouseLBUp(int x, int y)
{
    return 	m_oglWindow->MouseLBUp(x, y);
}

BOOL OGLMainWindow::MouseMove(int x, int y, WPARAM wparam)
{
    return m_oglWindow->MouseMove(x, y, wparam);
}

BOOL OGLMainWindow::MouseWheel(int x, int y, int scroll)
{
    return m_oglWindow->MouseWheel(x, y, scroll);
}
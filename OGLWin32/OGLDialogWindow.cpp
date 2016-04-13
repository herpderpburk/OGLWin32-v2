#include <Windows.h>
#include <CommCtrl.h>
#include "OGLDialogWindow.h"
#include "OGLData.h"
#include "OGLApplication.h"
#include "resource.h"

OGLDialogWindow::OGLDialogWindow(HINSTANCE hInstance, int width, int height) : m_height(height), m_width(width)
{
}


OGLDialogWindow::~OGLDialogWindow(void)
{
}

void OGLDialogWindow::SetPosition(int x, int y, int width, int height)
{
    ::SetWindowPos(m_hwnd, 0, x, y, width, height, SWP_NOZORDER);
}

void OGLDialogWindow::SetVisible(BOOL visible)
{
    ShowWindow(m_hwnd, visible ? SW_SHOW : SW_HIDE);
}

BOOL OGLDialogWindow::InitWindow(HINSTANCE hInstance, HWND hParent)
{
    m_hwndParent = hParent;
    //controls
    m_hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_FORM_DIALOG), m_hwndParent, OGLApplication::DialogProc);
    //place the list after the buttons
    HWND hButton = GetDlgItem(m_hwnd, IDC_BUTTON_BAR);
    RECT rect;
    GetWindowRect(hButton, &rect);
    int listX = rect.right - rect.left;
    HWND hwndList = GetDlgItem(m_hwnd, IDC_DATA_LIST);
    ListView_SetExtendedListViewStyle(hwndList, LVS_EX_FULLROWSELECT);
    return TRUE;
}

void OGLDialogWindow::DestroyDialog()
{
    ::DestroyWindow(m_hwnd);
    m_hwnd = NULL;
}

void OGLDialogWindow::Resize(int width, int height)
{
    m_width = width;
    m_height = height;
    HWND hwndRadioButton = GetDlgItem(m_hwnd, IDC_BUTTON_BAR);
    RECT radioRect;
    GetWindowRect(hwndRadioButton, &radioRect);
    int listX = radioRect.right - radioRect.left + 20;
    HWND hwndList = GetDlgItem(m_hwnd, IDC_DATA_LIST);
    ::SetWindowPos(hwndList, m_hwnd,  listX, 0, width - listX - 1, height, SWP_NOZORDER);
}

void OGLDialogWindow::ClearList()
{
    HWND hwndList = GetDlgItem(m_hwnd, IDC_DATA_LIST);
    HWND hwndHeader = ListView_GetHeader(hwndList);
    int count = Header_GetItemCount(hwndHeader);
    for(int i = 1; i <= count; i++)
        ListView_DeleteColumn(hwndList, 0);
    SendMessage(hwndList, LVM_DELETEALLITEMS, 0, 0);
}

//TODO: some cleanup
void OGLDialogWindow::DisplayData(OGLData *data)
{
    ClearList();
    HWND hwndList = GetDlgItem(m_hwnd, IDC_DATA_LIST);
    //create the colums
    LVCOLUMN lvColumn;
    int columnSize = (m_width / data->ColumnCount() > 10) ? (m_width / data->ColumnCount()) : (50) ;
    for(int i = 0; i < data->ColumnCount() ; i++)
    {
        lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
        lvColumn.fmt = LVCFMT_CENTER;
        lvColumn.cx = columnSize;
        lvColumn.pszText = data->GetAt(0, i);
        ListView_InsertColumn(hwndList, i, &lvColumn);
    }
    //populate the rows
    LVITEM item;
    memset(&item, 0, sizeof(item));
    item.mask = LVIF_TEXT;
    item.cchTextMax = 100;
    for(int row = 0; row < data->RowCount() - 1; row++)
    {
        item.iSubItem = 0;
        item.pszText = data->GetAt(row + 1, 0);
        item.iItem = row;
        ListView_InsertItem(hwndList, &item);
        for(int column = 1; column  < data->ColumnCount(); column++)
        {
            ListView_SetItemText(hwndList, row, column, data->GetAt(row + 1, column));
        }
    }
}
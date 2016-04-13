#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <Windows.h>
#include "OGLAttribute.h"

//TODO: read only what is needed
//TODO: mean/median/mode
//TODO: variance, frequency, normalization

using namespace std;

class OGLData
{
public:
    OGLData();
    virtual ~OGLData(void);
    bool ParseData(std::wstring dataFileName);

    wchar_t *GetAt(const int row, const int column);
    wstring GetStringAt(int row, int col);
    OGLAttribute *getAttributeValueAt(int row, int col);
    shared_ptr<vector<shared_ptr<OGLAttribute>>> getColumn(int colum);

    int RowCount();
    int ColumnCount();

    void ClearData();

    //compute a map where the first is the name of the category and the second is it's percentage
    std::map<std::wstring, double> *CalculatePieSlices(int categoryCol, int dataCol);

    //compute a map where the first is the name of the category and the second is it's total ammount
    std::map<std::wstring, double> *CalculateBars(int firstCol, int secondCol);

    //compute a map with coordinates for the plots
    std::map<double, double> *CalculatePlots(int firstCol, int secondCol);

private:
    static shared_ptr<map<int, vector<shared_ptr<OGLAttribute>>>> m_dataSet;//(line number, vector with line data)
    static DWORD WINAPI LoadDataThreadProc(LPVOID lpParam);
    HANDLE m_readingThread;
};


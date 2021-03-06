#include "OGLData.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <mutex>
using namespace std;

mutex mtx;
shared_ptr<map<int, vector<shared_ptr<OGLAttribute>>>> OGLData::m_dataSet = make_shared<map<int, vector<shared_ptr<OGLAttribute>>>> ();
OGLData::OGLData()
{
}


OGLData::~OGLData(void)
{
}

DWORD WINAPI OGLData::LoadDataThreadProc(LPVOID lpParam)
{
    wstringstream *stringContent = (wstringstream *) lpParam;
    int lineNumber = 0;
    wstring line;
    while(getline(*stringContent, line))
    {
        vector<shared_ptr<OGLAttribute>> lineVector;
        wchar_t *token = wcstok(const_cast<wchar_t *>(line.c_str()), L",;");
        wstring field;
        while(token != NULL)
        {
            lineVector.push_back(OGLAttribute::makeAttribute(token));
            token = wcstok(NULL, L",;");
        }
        auto p = pair<int, vector<shared_ptr<OGLAttribute>>>(lineNumber++, lineVector) ;
        mtx.lock();
        OGLData::m_dataSet->insert(p);
        mtx.unlock();
    }
    wcout << "Total line count: " << lineNumber << endl;
    if(stringContent != nullptr)
        delete stringContent;
    return true;
}

bool OGLData::ParseData(wstring dataFileName)
{
    wifstream fileStream(dataFileName, ios::in);
    if(!fileStream)
    {
        wcout << "Unable to open file";
        return false;
    }
    wstringstream *stringContent = new wstringstream;
    const int LEN = 8192;
    wchar_t buffer_in[LEN];
    wchar_t buffer_out[LEN];
    if(LEN)
    {
        fileStream.rdbuf()->pubsetbuf(buffer_in, LEN);
        stringContent->rdbuf()->pubsetbuf(buffer_out, LEN);
    }
    else
    {
        fileStream.rdbuf()->pubsetbuf(NULL, 0);
        stringContent->rdbuf()->pubsetbuf(NULL, 0);
    }
    *stringContent << fileStream.rdbuf();
    fileStream.close();
    TerminateThread(m_readingThread, 0);
    ClearData();
    m_readingThread = CreateThread(NULL, 0,
                                   LoadDataThreadProc, stringContent, 0, NULL);
    return true;
}

wchar_t *OGLData::GetAt(const int row, const int column)
{
    int row_count = OGLData::m_dataSet->size();
    int column_count = (*OGLData::m_dataSet)[row].size();
    if(row >= row_count || column >= column_count)
    {
        wcout << "Requested data at row " << row << " column " << column << " not available." << endl;
        return L"???";
    }
    wstring stringRes;
    stringRes = (*OGLData::m_dataSet)[row].at(column)->stringValue();
    wchar_t *result = new wchar_t[stringRes.size()];
    wcscpy(result, stringRes.c_str());
    return result;
}

wstring OGLData::GetStringAt(int row, int col)
{
    int row_count = OGLData::m_dataSet->size();
    int column_count = (*OGLData::m_dataSet)[row].size();
    if(row >= row_count || col >= column_count)
    {
        return L"";
    }
    wstring result((*OGLData::m_dataSet)[row].at(col)->stringValue());
    return result;
}

OGLAttribute *OGLData::getAttributeValueAt(int row, int col)
{
    int row_count = OGLData::m_dataSet->size();
    int column_count = (*OGLData::m_dataSet)[row].size();
    if(row >= row_count || col >= column_count)
        return NULL;
    OGLAttribute *res = ((*OGLData::m_dataSet)[row]).at(col).get();
    return res;
}


void OGLData::ClearData()
{
    mtx.lock();
    OGLData::m_dataSet->clear();
    mtx.unlock();
}

int OGLData::RowCount()
{
    int rowCount = OGLData::m_dataSet->size();
    return rowCount;
}

int OGLData::ColumnCount()
{
    int colCount = OGLData::m_dataSet->at(0).size();
    return colCount;
}

//compute a map where the first is the name of the category and the second is it's percentage
map<wstring, double> *OGLData::CalculatePieSlices(int categoryCol, int dataCol)
{
    auto *result = new map<wstring, double>;
    double total = 0;
    mtx.lock();
    for(const auto& kv : *OGLData::m_dataSet)
    {
        if(kv.first == 0)
            continue; //skip column names
        wstring categoryName = kv.second.at(categoryCol)->stringValue();
        double attributeValue = 0;
        if(dynamic_cast<OGLIntegerAttribute *>(kv.second.at(dataCol).get()))
            attributeValue = ((OGLIntegerAttribute *)(kv.second.at(dataCol).get()))->get();
        else if(dynamic_cast<OGLFloatingPointAttribute *>(kv.second.at(dataCol).get()))
            attributeValue = ((OGLFloatingPointAttribute *)(kv.second.at(dataCol).get()))->get();
        auto searchResultIt = result->find(categoryName);
        if(searchResultIt != result->end())
            searchResultIt->second += attributeValue;
        else
        {
            result->insert(make_pair(categoryName, attributeValue));
        }
        total += attributeValue;
    }
    mtx.unlock();
    //now we have the sums in the result map and the number of occurences in the occurences map
    //compute averages:
    for(auto& it : *result)
    {
        it.second = it.second / total * 100;
    }
    return result;
}

//compute a map where the first is the name of the category and the second is it's percentage
map<wstring, double> *OGLData::CalculateBars(int firstCol, int secondCol)
{
    auto *result = new map<wstring, double>;
    mtx.lock();
    for(const auto& kv : *OGLData::m_dataSet)
    {
        if(kv.first == 0)
            continue; //skip column names
        wstring categoryName = kv.second.at(firstCol)->stringValue();
        double attributeValue = 0;
        if(dynamic_cast<OGLIntegerAttribute *>(kv.second.at(secondCol).get()))
            attributeValue = ((OGLIntegerAttribute *)(kv.second.at(secondCol).get()))->get();
        else if(dynamic_cast<OGLFloatingPointAttribute *>(kv.second.at(secondCol).get()))
            attributeValue = ((OGLFloatingPointAttribute *)(kv.second.at(secondCol).get()))->get();
        auto searchResultIt = result->find(categoryName);
        if(searchResultIt != result->end())
            searchResultIt->second += attributeValue;
        else
        {
            result->insert(make_pair(categoryName, attributeValue));
        }
    }
    mtx.unlock();
    return result;
}

map<double, double> *OGLData::CalculatePlots(int firstCol, int secondCol)
{
    auto *result = new map<double, double>;
    mtx.lock();
    for(const auto& kv : *OGLData::m_dataSet)
    {
        if(kv.first == 0)
            continue; //skip column names
        double oxColumn = 0;
        if(dynamic_cast<OGLIntegerAttribute *>(kv.second.at(firstCol).get()))
            oxColumn = ((OGLIntegerAttribute *)(kv.second.at(firstCol).get()))->get();
        else if(dynamic_cast<OGLFloatingPointAttribute *>(kv.second.at(firstCol).get()))
            oxColumn = ((OGLFloatingPointAttribute *)(kv.second.at(firstCol).get()))->get();
        double oyColumn = 0;
        if(dynamic_cast<OGLIntegerAttribute *>(kv.second.at(secondCol).get()))
            oyColumn = ((OGLIntegerAttribute *)(kv.second.at(secondCol).get()))->get();
        else if(dynamic_cast<OGLFloatingPointAttribute *>(kv.second.at(secondCol).get()))
            oyColumn = ((OGLFloatingPointAttribute *)(kv.second.at(secondCol).get()))->get();
        result->insert(make_pair(oxColumn, oyColumn));
    }
    mtx.unlock();
    return result;
}


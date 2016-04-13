#pragma once
#include <string>
#include <sstream>
#include <regex>
//#include <algorithm>
#include "OGLAttribute.h"

using namespace std;

bool is_digits(wstring& str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

bool has_digits(wstring& str)
{
    return std::any_of(str.begin(), str.end(), ::isdigit);
}
shared_ptr<OGLAttribute> OGLAttribute::makeAttribute(wstring value)
{
    wstringstream ss;
    if((value.find(':') != std::wstring::npos || value.find('/') != std::wstring::npos) &&
            (!is_digits(value) && has_digits(value)))
    {
        //string contains more than just digits => check if it's a date or time
        //check if date first
        wregex rgx(L"^([0]?[1-9]|[1|2][0-9]|[3][0|1])[./-]([0]?[1-9]|[1][0-2])[./-]([0-9]{4}|[0-9]{2})$");
        wsmatch match;
        if(regex_search(value, match, rgx))
        {
            int day, month, year;
            ss.clear();
            ss << match[1];
            ss >> day;
            ss.clear();
            ss << match[2];
            ss >> month;
            ss.clear();
            ss << match[3];
            ss >> year;
            return make_shared<OGLDateAttribute>(value, day, month, year);
        }
        //check if time
        wregex rgxTime(L"(([0-1][0-9])|([2][0-3])):([0-5][0-9]):([0-5][0-9])");
        if(regex_search(value, match, rgxTime))
        {
            int hour, minute, second;
            ss.clear();
            ss << match[1];
            ss >> hour;
            ss.clear();
            ss << match[4];
            ss >> minute;
            ss.clear();
            ss << match[5];
            ss >> second;
            return make_shared<OGLTimeAttribute>(value, hour, minute, second);
        }
    }
    ss << value;
    if(value.find('.') != std::wstring::npos)
    {
        double double_val;
        ss >> double_val;
        if(!ss.fail())
            //store as double
            return make_shared<OGLFloatingPointAttribute>(double_val);
    }
    int int_val;
    ss >> int_val;
    if(!ss.fail())
        //as integer
        return make_shared<OGLIntegerAttribute>(int_val);
    return make_shared<OGLTextAttribute>(value);
}


OGLIntegerAttribute::OGLIntegerAttribute(int value) : m_value(value)
{
}

OGLIntegerAttribute::~OGLIntegerAttribute(void)
{
}

AttributeType OGLIntegerAttribute::getType()
{
    return AttributeType::INTEGER;
}

wstring OGLIntegerAttribute::stringValue()
{
    return std::to_wstring(m_value);
}

void OGLIntegerAttribute::set(int val)
{
    this->m_value = val;
}

int OGLIntegerAttribute::get()
{
    return this->m_value;
}

OGLFloatingPointAttribute::OGLFloatingPointAttribute(double value) : m_value(value)
{
}

OGLFloatingPointAttribute::~OGLFloatingPointAttribute(void)
{
}

AttributeType OGLFloatingPointAttribute::getType()
{
    return AttributeType::FLOATING_POINT;
}

wstring OGLFloatingPointAttribute::stringValue()
{
    return std::to_wstring(m_value);
}

void OGLFloatingPointAttribute::set(double val)
{
    this->m_value = val;
}

double OGLFloatingPointAttribute::get()
{
    return this->m_value;
}

OGLTextAttribute::OGLTextAttribute(wstring value): m_value(value)
{
}

OGLTextAttribute::~OGLTextAttribute(void)
{
}

AttributeType OGLTextAttribute::getType()
{
    return AttributeType::TEXT;
}
wstring OGLTextAttribute::stringValue()
{
    return m_value;
}

void OGLTextAttribute::set(wstring val)
{
    this->m_value = val;
}

wstring OGLTextAttribute::get()
{
    return m_value;
}

OGLDateAttribute::OGLDateAttribute(wstring value, int day, int month, int year): OGLTextAttribute(value), m_day(day), m_month(month), m_year(year)
{
}

OGLDateAttribute::~OGLDateAttribute(void)
{
}

AttributeType OGLDateAttribute::getType()
{
    return AttributeType::DATE_;
}



bool operator> (OGLDateAttribute& d1, OGLDateAttribute& d2)
{
    if(d1.m_year > d2.m_year)
        return true;
    if(d1.m_year == d2.m_year && d1.m_month > d2.m_month)
        return true;
    if(d1.m_year == d2.m_year && d1.m_month == d2.m_month && d1.m_day > d2.m_day)
        return true;
    return false;
}

bool operator<= (OGLDateAttribute& d1, OGLDateAttribute& d2)
{
    return !(d1 > d2);
}

bool operator< (OGLDateAttribute& d1, OGLDateAttribute& d2)
{
    if(d1.m_year < d2.m_year)
        return true;
    if(d1.m_year == d2.m_year && d1.m_month < d2.m_month)
        return true;
    if(d1.m_year == d2.m_year && d1.m_month == d2.m_month && d1.m_day < d2.m_day)
        return true;
    return false;
}

bool operator>= (OGLDateAttribute& d1, OGLDateAttribute& d2)
{
    return !(d1 < d2);
}

OGLTimeAttribute::OGLTimeAttribute(wstring value, int hour, int minute, int second): OGLTextAttribute(value), m_hour(hour), m_minute(minute), m_second(second)
{
}

OGLTimeAttribute::~OGLTimeAttribute(void)
{
}

AttributeType OGLTimeAttribute::getType()
{
    return AttributeType::TIME;
}



bool operator> (OGLTimeAttribute& h1, OGLTimeAttribute& h2)
{
    if(h1.m_hour > h2.m_hour)
        return true;
    if(h1.m_hour == h2.m_hour && h1.m_minute > h2.m_minute)
        return true;
    if(h1.m_hour == h2.m_hour && h1.m_minute == h2.m_minute && h1.m_second > h2.m_second)
        return true;
    return false;
}

bool operator<= (OGLTimeAttribute& h1, OGLTimeAttribute& h2)
{
    return !(h1 > h2);
}

bool operator< (OGLTimeAttribute& h1, OGLTimeAttribute& h2)
{
    if(h1.m_hour < h2.m_hour)
        return true;
    if(h1.m_hour == h2.m_hour && h1.m_minute < h2.m_minute)
        return true;
    if(h1.m_hour == h2.m_hour && h1.m_minute == h2.m_minute && h1.m_second < h2.m_second)
        return true;
    return false;
}

bool operator>= (OGLTimeAttribute& h1, OGLTimeAttribute& h2)
{
    return !(h1 < h2);
}
#pragma once
#include <string>
#include <memory>
using namespace std;
//TODO: floating point
//TODO: text, ordinal nominal
//TODO: datetime

enum AttributeType
{
    INTEGER,
    FLOATING_POINT,
    TEXT,
    ORDINAL,
    NOMINAL,
    DATE_,
    TIME
};

class OGLAttribute
{
public:
    virtual AttributeType getType() = 0;
    virtual wstring stringValue() = 0;
    static shared_ptr<OGLAttribute> makeAttribute(wstring value);
};

class OGLIntegerAttribute : public OGLAttribute
{
public:

    OGLIntegerAttribute(int value);
    virtual ~OGLIntegerAttribute(void);
    virtual AttributeType getType();
    virtual wstring stringValue();
    virtual void set(int newValue);
    virtual int get();
private:
    int m_value;
};

class OGLFloatingPointAttribute : public OGLAttribute
{
public:

    OGLFloatingPointAttribute(double value);
    virtual ~OGLFloatingPointAttribute(void);
    virtual AttributeType getType();
    virtual wstring stringValue();
    virtual void set(double newValue);
    virtual double get();

private:
    double m_value;
};

class OGLTextAttribute : public OGLAttribute
{
public:
    OGLTextAttribute(wstring value);

    virtual ~OGLTextAttribute(void);
    virtual AttributeType getType();
    virtual wstring stringValue();
    virtual void set(wstring newValue);
    virtual wstring get();
private:
    wstring m_value;
};

class OGLDateAttribute : public OGLTextAttribute
{
public:
    OGLDateAttribute(wstring value, int day, int month, int year);

    virtual ~OGLDateAttribute(void);
    virtual AttributeType getType();
    int getDay()
    {
        return m_day;
    }
    int getMonth()
    {
        return m_month;
    }
    int getYear()
    {
        return m_year;
    }

    friend bool operator> (OGLDateAttribute& d1, OGLDateAttribute& d2);
    friend bool operator<= (OGLDateAttribute& d1, OGLDateAttribute& d2);

    friend bool operator< (OGLDateAttribute& d1, OGLDateAttribute& d2);
    friend bool operator>= (OGLDateAttribute& d1, OGLDateAttribute& d2);
private:
    int m_month;
    int m_day;
    int m_year;
};

bool operator> (OGLDateAttribute& d1, OGLDateAttribute& d2);
bool operator<= (OGLDateAttribute& d1, OGLDateAttribute& d2);

bool operator< (OGLDateAttribute& d1, OGLDateAttribute& d2);
bool operator>= (OGLDateAttribute& d1, OGLDateAttribute& d2);

class OGLTimeAttribute : public OGLTextAttribute
{
public:
    OGLTimeAttribute(wstring value, int hour, int minute, int second);

    virtual ~OGLTimeAttribute(void);
    virtual AttributeType getType();
    int getHour()
    {
        return m_hour;
    }
    int getMinute()
    {
        return m_minute;
    }
    int getSecond()
    {
        return m_second;
    }

    friend bool operator> (OGLTimeAttribute& d1, OGLTimeAttribute& d2);
    friend bool operator<= (OGLTimeAttribute& d1, OGLTimeAttribute& d2);

    friend bool operator< (OGLTimeAttribute& d1, OGLTimeAttribute& d2);
    friend bool operator>= (OGLTimeAttribute& d1, OGLTimeAttribute& d2);
private:
    int m_hour;
    int m_minute;
    int m_second;
};

bool operator> (OGLTimeAttribute& d1, OGLTimeAttribute& d2);
bool operator<= (OGLTimeAttribute& d1, OGLTimeAttribute& d2);

bool operator< (OGLTimeAttribute& d1, OGLTimeAttribute& d2);
bool operator>= (OGLTimeAttribute& d1, OGLTimeAttribute& d2);

#pragma once
#include <random>
#include <iostream>
class Color3ub
{
private:
    unsigned char m_R;
    unsigned char m_G;
    unsigned char m_B;
public:
    Color3ub(unsigned char r, unsigned char g, unsigned char b): m_R(r), m_G(g), m_B(b) {}
    Color3ub(void) {}
    ~Color3ub(void) {}
    unsigned char R()
    {
        return m_R;
    }
    unsigned char G()
    {
        return m_G;
    }
    unsigned char B()
    {
        return m_B;
    }
    static Color3ub random()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 255);
        unsigned char  r = dist(gen);
        unsigned char  g = dist(gen);
        unsigned char  b = dist(gen);
        return Color3ub(r, g, b);
    }
};


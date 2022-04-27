#pragma once

#include "..\AddHotKey\Logger.h"

template <class T> class Cycler
{
public:
    Cycler(const std::vector<T>& theV) : v(theV), currentIndex(0)
    {
    }
    T forward(void);
    T backward(void);
    void setCurrentIndex(const T srcValue)
    {
        currentIndex = getIndex(srcValue);

        Logger::getInstance().logln(_T("Cycler.setCurrentIndex()"));
        Logger::getInstance().log(_T("srcValue: "));
        Logger::getInstance().logln(srcValue);
        Logger::getInstance().log(_T("currentIndex: "));
        Logger::getInstance().logln(currentIndex);
    }
private:
    std::vector<T> v;
    int currentIndex;
    const int getIndex(const T srcValue);
};

template <class T> T Cycler<T>::forward(void)
{
    currentIndex++;
    if (currentIndex >= static_cast<int>(v.size()))
    {
        currentIndex = 0;
    }

    Logger::getInstance().logln(_T("Cycler.forward()"));
    Logger::getInstance().logln(_T("v:"));
    Logger::getInstance().logln(v);
    Logger::getInstance().log(_T("currentIndex: "));
    Logger::getInstance().logln(currentIndex);
    Logger::getInstance().log(_T("v[currentIndex]: "));
    Logger::getInstance().logln(v[currentIndex]);

    return v[currentIndex];
};

template <class T> T Cycler<T>::backward(void)
{
    currentIndex--;
    if (currentIndex < 0)
    {
        currentIndex = static_cast<int>(v.size()) - 1;
    }

    Logger::getInstance().logln(_T("Cycler.backward()"));
    Logger::getInstance().logln(_T("v:"));
    Logger::getInstance().logln(v);
    Logger::getInstance().log(_T("currentIndex: "));
    Logger::getInstance().logln(currentIndex);
    Logger::getInstance().log(_T("v[currentIndex]: "));
    Logger::getInstance().logln(v[currentIndex]);

    return v[currentIndex];
};

template <class T> const int Cycler<T>::getIndex(const T srcValue)
{
    for (int i = 0; i < static_cast<int>(v.size()); i++)
    {
        T& value = v[i];
        if (srcValue == value)
        {
            return i;
        }
    }
    return -1;
};

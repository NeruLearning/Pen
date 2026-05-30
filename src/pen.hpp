#pragma once
#include <windows.h>
#include <iostream>
#include <vector>

using namespace std;

struct PenInfo
{
    UINT32 penId;
    UINT32 count;
    vector<POINTER_PEN_INFO> history;

    // Konstruktor
    PenInfo(UINT32 id) : penId(id), count(0) {}

    bool fetchHistory()
    {
        GetPointerPenInfoHistory(penId, &count, nullptr);

        if (count == 0)
            return false;

        history.resize(count);
        return GetPointerPenInfoHistory(penId, &count, history.data());
    }

    void print()
    {
        for (const auto &info : history)
        {
            cout << "X: " << info.pointerInfo.ptPixelLocation.x
                 << ", Y: " << info.pointerInfo.ptPixelLocation.y
                 << ", Druck: " << info.pressure
                 << ", TiltX: " << info.tiltX
                 << ", TiltY: " << info.tiltY
                 << endl;
        }
    }
};
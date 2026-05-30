#define _WIN32_WINNT 0x0A00

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

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_POINTERUPDATE:
    {
        UINT32 pointerId = GET_POINTERID_WPARAM(wParam);

        // Nur Stift-Events verarbeiten
        POINTER_INPUT_TYPE pointerType;
        GetPointerType(pointerId, &pointerType);
        if (pointerType != PT_PEN)
            break;

        PenInfo pen(pointerId);
        if (pen.fetchHistory())
        {
            pen.print();
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int main()
{
    // Fenster registrieren
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "PenWindow";
    RegisterClass(&wc);

    // Fenster erstellen (unsichtbar ist ok)
    HWND hwnd = CreateWindowEx(
        0, "PenWindow", "Pen Input",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, GetModuleHandle(nullptr), nullptr);

    ShowWindow(hwnd, SW_SHOW);

    // Event Loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
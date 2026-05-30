// #define UNICODE 0
// #define _UNICODE 0
#define _WIN32_WINNT 0x0A00
#include <windows.h>
#include "window.hpp"
#include "pen.hpp"

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
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int main()
{
    // Fensterklasse registrieren
    Window window;

    HWND hwnd = (HWND)window.getHWND();
    SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

    while (!window.shouldClose())
    {
        window.pollEvents();
    }

    return 0;
}
#define _WIN32_WINNT 0x0A00
#include <windows.h>
#include "window.hpp"
#include "pen.hpp"
#include "Canvas/canvas.hpp"

Canvas *canvas = nullptr;
Window *w = nullptr;
int monitorOffsetX = 0;
int monitorOffsetY = 0;
WNDPROC originalWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_POINTERDOWN:
    {
        UINT32 pointerId = GET_POINTERID_WPARAM(wParam);
        POINTER_PEN_INFO info;
        GetPointerPenInfo(pointerId, &info);
        canvas->beginStroke(
            info.pointerInfo.ptPixelLocation.x - monitorOffsetX, // ← Offset
            info.pointerInfo.ptPixelLocation.y - monitorOffsetY, // ← Offset
            info.pressure / 1024.0f);
        break;
    }
    case WM_POINTERUPDATE:
    {
        UINT32 pointerId = GET_POINTERID_WPARAM(wParam);
        POINTER_INPUT_TYPE pointerType;
        GetPointerType(pointerId, &pointerType);
        if (pointerType != PT_PEN)
            break;

        POINTER_PEN_INFO penInfo;
        GetPointerPenInfo(pointerId, &penInfo);
        if (!(penInfo.pointerInfo.pointerFlags & POINTER_FLAG_INCONTACT))
            break; // ← neu

        PenInfo pen(pointerId);
        if (pen.fetchHistory())
        {
            for (const auto &info : pen.history)
            {
                canvas->addToStroke(
                    info.pointerInfo.ptPixelLocation.x - monitorOffsetX,
                    info.pointerInfo.ptPixelLocation.y - monitorOffsetY,
                    info.pressure / 1024.0f,
                    info.tiltX,
                    info.tiltY);
            }
        }
        break;
    }
    case WM_POINTERUP:
    {
        std::cout << "Stift abgehoben!" << std::endl;
        canvas->endStroke();
        break;
    }
    }
    return CallWindowProc(originalWndProc, hwnd, msg, wParam, lParam);
}
int main()
{
    // 1. Zuerst Window (initialisiert GLFW)
    Window window;
    w = &window;

    // 2. Dann Monitor-Infos holen
    int monitorCount;
    GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);
    GLFWmonitor *activeMonitor = monitors[monitorCount > 1 ? 1 : 0];

    int mx, my;
    glfwGetMonitorPos(activeMonitor, &mx, &my);
    monitorOffsetX = mx;
    monitorOffsetY = my;

    const GLFWvidmode *mode = glfwGetVideoMode(activeMonitor);

    // 3. Canvas mit echter Auflösung
    Canvas c(mode->width, mode->height);
    canvas = &c;

    HWND hwnd = (HWND)window.getHWND();
    originalWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

    while (!window.shouldClose())
    {
        window.pollEvents();
        window.renderCanvas(canvas->getPixels(), canvas->getWidth(), canvas->getHeight());
    }

    return 0;
}
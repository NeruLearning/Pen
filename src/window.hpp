#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

class Window
{
public:
    Window();
    ~Window();

    bool shouldClose();
    void pollEvents();
    void *getHWND() { return glfwGetWin32Window(window); }

private:
    GLFWwindow *window;
    GLFWmonitor *monitor;
};
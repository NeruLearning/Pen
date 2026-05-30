#pragma once
#include <GLFW/glfw3.h>

class Window
{
public:
    Window();
    ~Window();

    bool shouldClose();
    void pollEvents();

private:
    GLFWwindow *window;
    GLFWmonitor *monitor;
};
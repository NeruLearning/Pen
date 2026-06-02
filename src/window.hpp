#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

class Window
{
public:
    Window();
    ~Window();
    void renderCanvas(const uint8_t *pixels, int width, int height);
    bool shouldClose();
    void pollEvents();
    void *getHWND() { return glfwGetWin32Window(window); }

private:
    GLFWwindow *window;
    GLuint canvasTexture = 0;
    GLFWmonitor *monitor;
};

#include "window.hpp"
#include <iostream>

Window::Window()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    // Get the primary monitor
    // monitor = glfwGetPrimaryMonitor();
    int monitorCount;
    GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);
    monitor = monitors[monitorCount > 1 ? 1 : 0]; // Verwende den ersten Monitor

    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    window = glfwCreateWindow(
        mode->width, mode->height, "Pen Input", monitor, NULL);
    glfwMakeContextCurrent(window);

    if (!window)
    {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::pollEvents()
{
    glfwPollEvents();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // dunkles Grau
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}
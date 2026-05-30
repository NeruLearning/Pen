
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
    monitor = glfwGetPrimaryMonitor();
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
}

#include "window.hpp"
#include <iostream>

#include <GLFW/glfw3.h>

void Window::renderCanvas(const uint8_t *pixels, int width, int height)
{
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2f(-1, -1);
    glTexCoord2f(1, 1);
    glVertex2f(1, -1);
    glTexCoord2f(1, 0);
    glVertex2f(1, 1);
    glTexCoord2f(0, 0);
    glVertex2f(-1, 1);
    glEnd();

    glDeleteTextures(1, &texture);
    glfwSwapBuffers(window);
}

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
}
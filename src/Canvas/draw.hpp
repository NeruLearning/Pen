#pragma once
#include "color.hpp"
#include <vector>
#include <cmath>
#include <cstdint>

class Brush
{
public:
    // Kreis an Position malen
    static void drawCircle(std::vector<uint8_t> &pixels,
                           int width, int height,
                           int cx, int cy, int radius, Color color)
    {
        for (int dy = -radius; dy <= radius; dy++)
            for (int dx = -radius; dx <= radius; dx++)
                if (dx * dx + dy * dy <= radius * radius)
                    setPixel(pixels, width, height, cx + dx, cy + dy, color);
    }

    // Bresenham Linie
    static void drawLine(std::vector<uint8_t> &pixels,
                         int width, int height,
                         int x0, int y0, int x1, int y1, float brushWidth, Color color)
    {
        int radius = (int)(brushWidth * 0.5f);
        int dx = abs(x1 - x0), dy = abs(y1 - y0);
        int sx = x0 < x1 ? 1 : -1;
        int sy = y0 < y1 ? 1 : -1;
        int err = dx - dy;

        while (true)
        {
            drawCircle(pixels, width, height, x0, y0, radius, color);
            if (x0 == x1 && y0 == y1)
                break;
            int e2 = 2 * err;
            if (e2 > -dy)
            {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dx)
            {
                err += dx;
                y0 += sy;
            }
        }
    }

private:
    static void setPixel(std::vector<uint8_t> &pixels,
                         int width, int height, int x, int y, Color color)
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return;
        int idx = (y * width + x) * 4;
        pixels[idx + 0] = color.r;
        pixels[idx + 1] = color.g;
        pixels[idx + 2] = color.b;
        pixels[idx + 3] = color.a;
    }
};
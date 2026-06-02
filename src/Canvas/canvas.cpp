#include "canvas.hpp"
#include "draw.hpp"
#include <iostream>

using namespace std;

Canvas::Canvas(int width, int height)
    : width(width), height(height), pixels(width * height * 4, 255)
{
    Brush::drawLine(pixels, width, height,
                    100, 100, 500, 500, 10.0f, {255, 0, 0, 255});
}

void Canvas::clear()
{
    fill(pixels.begin(), pixels.end(), 255);
}
void Canvas::beginStroke(int x, int y, float pressure)
{
    cout << "beginStroke!" << endl;
    currentStroke = Stroke();
    currentStroke.begin(x, y, pressure);
}

void Canvas::addToStroke(int x, int y, float pressure, float tiltX, float tiltY)
{
    if (!currentStroke.active)
        return;

    int lastX = x, lastY = y;
    if (!currentStroke.isEmpty())
    {
        auto &pts = currentStroke.getPoints();
        lastX = pts.back().x;
        lastY = pts.back().y;
    }

    currentStroke.addPoint(x, y, pressure, tiltX, tiltY);

    float thickness = pressure * 15.0f + 1.0f; // ← Druck = Dicke
    Brush::drawLine(pixels, width, height,
                    lastX, lastY, x, y, thickness, {0, 0, 0, 255});
}

void Canvas::endStroke()
{
    //     currentStroke.end();
    //     // Strich in Pixel malen
    //     std::vector<std::pair<int, int>> points;
    //     for (const auto &p : currentStroke.getPoints())
    //     //     points.push_back({p.x, p.y});
    //     // drawStroke(points, {0, 0, 0, 255}, 3.0f);
}

void Canvas::drawStroke(vector<pair<int, int>> points,
                        Color color, float thickness)
{
    if (points.size() < 2)
        return;

    if (!smooth)
    {
        for (int i = 0; i + 1 < (int)points.size(); i++)

            Brush::drawLine(pixels, width, height, points[i].first, points[i].second, points[i + 1].first, points[i + 1].second, thickness, color);
    }
    else
    {
        for (int i = 0; i + 1 < (int)points.size(); i++)
        {
            auto [x0, y0] = points[i];
            auto [x1, y1] = points[i + 1];
            float cx0 = x0 + (x1 - x0) * 0.33f;
            float cy0 = y0 + (y1 - y0) * 0.33f;
            float cx1 = x0 + (x1 - x0) * 0.66f;
            float cy1 = y0 + (y1 - y0) * 0.66f;

            int steps = 20;
            int px = x0, py = y0;
            for (int s = 1; s <= steps; s++)
            {
                float t = (float)s / steps;
                float u = 1.0f - t;
                int nx = (int)(u * u * u * x0 + 3 * u * u * t * cx0 + 3 * u * t * t * cx1 + t * t * t * x1);
                int ny = (int)(u * u * u * y0 + 3 * u * u * t * cy0 + 3 * u * t * t * cy1 + t * t * t * y1);
                Brush::drawLine(pixels, width, height,
                                px, py, nx, ny, thickness, color);
                px = nx;
                py = ny;
            }
        }
    }
}
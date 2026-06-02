#pragma once
#include <vector>
#include <utility>

struct StrokePoint
{
    int x, y;
    float pressure;
    float tiltX, tiltY;
};

class Stroke
{
public:
    bool active = false;

    void begin(int x, int y, float pressure)
    {
        points.clear();
        active = true;
        addPoint(x, y, pressure);
    }

    void addPoint(int x, int y, float pressure, float tiltX = 0, float tiltY = 0)
    {
        if (!active)
            return;
        points.push_back({x, y, pressure, tiltX, tiltY});
    }
    void end()
    {
        active = false;
    }

    bool isEmpty() const
    {
        return points.empty();
    }
    const std::vector<StrokePoint> &getPoints() const
    {
        return points;
    }

private:
    std::vector<StrokePoint> points;
};
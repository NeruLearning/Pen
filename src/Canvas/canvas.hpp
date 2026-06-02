#pragma once
#include "color.hpp"
#include "draw.hpp"
#include "stroke.hpp"
#include <vector>
#include <utility>

using namespace std;

class Canvas
{
public:
    void beginStroke(int x, int y, float pressure);
    void addToStroke(int x, int y, float pressure, float tiltX, float tiltY);
    void endStroke();

    Canvas(int width, int height);

    void drawStroke(vector<pair<int, int>> points,
                    Color color, float thickness);
    void setSmooth(bool s) { smooth = s; }
    bool getSmooth() const { return smooth; }
    void clear();

    const uint8_t *getPixels() const { return pixels.data(); }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width, height;
    bool smooth = false;
    vector<uint8_t> pixels;

    Stroke currentStroke;
    vector<Stroke> strokes;
};
#pragma once
#include <vector>
#include <utility>

using namespace std;

inline pair<int, int> cubicBezier(
    pair<int, int> p0,
    pair<int, int> p1,
    pair<int, int> p2,
    pair<int, int> p3,
    float t)
{
    float u = 1.0f - t;
    return {
        (int)(u * u * u * p0.first + 3 * u * u * t * p1.first + 3 * u * t * t * p2.first + t * t * t * p3.first),
        (int)(u * u * u * p0.second + 3 * u * u * t * p1.second + 3 * u * t * t * p2.second + t * t * t * p3.second)};
}

inline vector<std::pair<int, int>> bezierControPoints(
    vector<pair<int, int>> points)
{
    vector<pair<int, int>> ctrl;
    for (int i = 0; i + 1 < (int)points.size(); i++)
    {
        auto [x0, y0] = points[i];
        auto [x1, y1] = points[i + 1];
        ctrl.push_back({(int)(x0 + (x1 - x0) * 0.33f), (int)(y0 + (y1 - y0) * 0.33f)});
        ctrl.push_back({(int)(x0 + (x1 - x0) * 0.66f), (int)(y0 + (y1 - y0) * 0.66f)});
    }
    return ctrl;
}

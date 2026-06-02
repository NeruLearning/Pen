![](https://media.tenor.com/RXpiLts0y6EAAAAi/jade-unjaded.gif)


# Pen-Whiteboard for Windows
a digital Whiteboard with pen input, written in C++

## Features

- Real-time pen input via Windows Pointer API
- Pressure sensitivity (pressure = stroke thickness)
- Tilt support
- Bézier smoothing (toggleable)
- OpenGL rendering via GLFW

## Requirements

Windows 10 or higher
MinGW-W64 (g++ 13.x)
Vulkan SDK
GLFW 3.4

## Project Structure
```
Notebook_C/
├── src/
│   ├── main.cpp            # Entry point, Windows event loop
│   ├── window.hpp/cpp      # GLFW window + OpenGL rendering
│   ├── pen.hpp             # Windows Pointer API, pen input
│   ├── stroke.hpp          # Single stroke (points, pressure, tilt)
│   ├── Canvas/
│   │   ├── canvas.hpp/cpp  # Drawing surface, pixel buffer
│   │   ├── brush.hpp       # Bresenham lines, circle brush
│   │   ├── bezier.hpp      # Bézier curve algorithm
│   │   └── color.hpp       # Color struct
├── libs/
│   └── glfw-3.4.bin.WIN64/ # GLFW library
├── build/                  # Compiled output
└── run.bat                 # Build & run script
```
## Build

```bat
run.bat
```

Or manually:

```bash
g++ src/main.cpp src/window.cpp src/Canvas/canvas.cpp -o build/main.exe \
  -DUNICODE=0 -D_UNICODE=0 \
  -I./libs/glfw-3.4.bin.WIN64/include \
  -L./libs/glfw-3.4.bin.WIN64/lib-mingw-w64 \
  -lglfw3 -luser32 -lgdi32 -lopengl32
```

## Architecture

pen.hpp       →  Windows Pointer API, reads hardware data
stroke.hpp    →  Collects a complete stroke (begin/add/end)
canvas.cpp    →  Manages pixel buffer, calls Brush
brush.hpp     →  Paints pixels (Bresenham, circles)
bezier.hpp    →  Smooths strokes via cubic Bézier curves
window.cpp    →  GLFW window, uploads canvas as OpenGL texture
main.cpp      →  Event loop, connects all components



## Controls
```
| Action | Description |
|--------|-------------|
| Pen down | Start new stroke |
| Pen move | Draw |
| Pen up | End stroke |
| `S` key | Toggle Bézier smoothing |
```
## Technical Details
```
- Canvas resolution: dynamic (monitor resolution)
- Pixel format: RGBA 8-bit
- Rendering: OpenGL texture on fullscreen quad
- Input: `WM_POINTERDOWN`, `WM_POINTERUPDATE`, `WM_POINTERUP`
- Stroke thickness: `pressure * 15.0f + 1.0f` pixels

```

@echo off


mkdir ..\build
pushd ..\build


g++ ..\src\main.cpp ..\src\window.cpp -o main.exe ^
  -I..\libs\glfw-3.4.bin.WIN64\include ^
  -L..\libs\glfw-3.4.bin.WIN64\lib-mingw-w64 ^
  -lglfw3 -luser32 -lgdi32 -lopengl32

.\main.exe

pause
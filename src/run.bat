@echo off

if not exist ..\build mkdir ..\build
pushd ..\build


g++ ..\src\main.cpp ..\src\window.cpp ..\src\Canvas\canvas.cpp -o main.exe ^
  -DUNICODE=0 ^
  -D_UNICODE=0 ^
  -I..\libs\glfw-3.4.bin.WIN64\include ^
  -L..\libs\glfw-3.4.bin.WIN64\lib-mingw-w64 ^
  -lglfw3 -luser32 -lgdi32 -lopengl32

if errorlevel 1 (
  echo Build fehlgeschlagen.
  popd
  pause
  exit /b 1
)

echo Starte main.exe ...
main.exe

popd

pause
@echo off


mkdir ..\build
pushd ..\build


g++ ..\src\pen.cpp -o .\pen.exe -luser32 

.\pen.exe

pause
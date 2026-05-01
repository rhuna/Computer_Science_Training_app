@echo off
g++ -std=c++17 main.cpp -o exercise.exe || exit /b 1
exercise.exe | findstr /C:"PASS_BASE_CONVERTER"

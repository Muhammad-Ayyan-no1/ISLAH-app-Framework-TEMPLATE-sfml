@echo off
REM Create built directory if it doesn't exist
if not exist built (
    mkdir built
)

g++ src/main.cpp -o built\ISLAH.exe -Isrc -Iinclude -lsfml-graphics -lsfml-window -lsfml-system
if %errorlevel% neq 0 (
    echo Compilation failed.
    pause
    exit /b
)
echo Compilation successful. Running the application...
cd built
ISLAH.exe
cd
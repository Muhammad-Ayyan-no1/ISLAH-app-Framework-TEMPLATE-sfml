@echo off
setlocal enabledelayedexpansion

REM Create built and include directories if they don't exist
if not exist built (
    mkdir built
)
if not exist built\include (
    mkdir built\include
)

REM Recursively copy all files from include\ to built\include\, preserving structure
for /R include %%F in (*) do (
    set "src=%%F"
    set "dest=%%F"
    set "dest=!dest:include=built\include!"
    
    REM Create destination directory if needed
    for %%D in ("!dest!") do (
        if not exist "%%~dpD" (
            mkdir "%%~dpD"
        )
    )
    
    copy /Y "!src!" "!dest!" >nul
)

REM Compile the project
g++ src/main.cpp -o built\ISLAH.exe -Isrc -Iinclude -lsfml-graphics -lsfml-window -lsfml-system
if %errorlevel% neq 0 (
    echo Compilation failed.
    pause
    exit /b
)

echo Compilation successful. Running the application...
cd built
ISLAH.exe

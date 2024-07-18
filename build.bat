@echo off
setlocal enabledelayedexpansion

REM Check if default Conan profile exists
conan profile path default >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo Default Conan profile not found. Creating one...
    conan profile detect
    if %ERRORLEVEL% neq 0 (
        echo Failed to create default Conan profile.
        pause
        exit /b 1
    )
    echo Default Conan profile created successfully.
    pause
) else (
    echo Default Conan profile found.
)

if not exist build mkdir build

echo Running Conan install...
conan install . --output-folder=build --build=missing
if %ERRORLEVEL% neq 0 (
    echo Conan install failed.
    pause
    exit /b 1
)
echo Conan install completed successfully.
pause

echo Configuring CMake...
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake
if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed.
    pause
    exit /b 1
)
echo CMake configuration completed successfully.
pause

echo Building project...
cmake --build build --config Release
if %ERRORLEVEL% neq 0 (
    echo Build failed.
    pause
    exit /b 1
)
echo Build completed successfully.
pause

echo Build process finished.
pause
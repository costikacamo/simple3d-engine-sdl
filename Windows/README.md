# Windows Build Instructions

1. Prerequisites:
   - Install Visual Studio 2022 Community Edition
   - Download SDL2 development libraries from https://github.com/libsdl-org/SDL/releases
   - Install CMake from https://cmake.org/download/

2. Set up SDL2:
   - Create folder: `C:\SDL2`
   - Extract SDL2 development libraries to `C:\SDL2`
   - Directory structure should look like:
     ```
     C:\SDL2\
     ├── include\
     ├── lib\
     └── cmake\
     ```

3. Build:
   - Double-click `build.bat`
   - Or run these commands in Developer Command Prompt:
     ```batch
     mkdir build
     cd build
     cmake -G "Visual Studio 17 2022" -A x64 ..
     cmake --build . --config Release
     ```

4. Run:
   - The executable will be in `build\Release\raycaster.exe`
   - Make sure SDL2.dll is in the same folder as the executable
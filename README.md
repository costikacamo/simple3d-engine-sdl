# Simple Raycasting Engine

A basic raycasting engine implemented in C++ using SDL2, inspired by classic games like Wolfenstein 3D.

## Features

- First-person perspective rendering using raycasting
- Smooth movement and rotation
- Collision detection
- Customizable map layout
- Configurable display and gameplay settings
- Cross-platform support (Windows, macOS, Linux)

## Prerequisites

- C++ compiler (GCC, Clang, or MSVC)
- SDL2 library
- CMake (recommended for cross-platform building)

## Installation Instructions

### Linux

#### Ubuntu/Debian
```bash
# Install required packages
sudo apt update
sudo apt install build-essential cmake libsdl2-dev
```

#### Arch Linux
```bash
sudo pacman -S base-devel cmake sdl2
```

#### Fedora
```bash
sudo dnf install gcc-c++ cmake SDL2-devel
```

### macOS

Using Homebrew:
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required packages
brew install cmake sdl2
```

### Windows

1. **Install Visual Studio**
   - Download and install [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)
   - During installation, select "Desktop development with C++"

2. **Install SDL2**
   - Download SDL2 development libraries for Windows from [SDL releases](https://github.com/libsdl-org/SDL/releases)
   - Create a folder `C:\SDL2`
   - Extract the SDL2 files there

3. **Set up Environment Variables**
   - Add `C:\SDL2\bin` to your system's PATH environment variable

## Building

### Using CMake (Recommended)

```bash
# Clone the repository
git clone https://github.com/costikacamo/simple3d-engine-sdl
cd raycasting-engine

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
cmake --build .
```

### Manual Compilation

#### Linux
```bash
g++ main.cpp -o raycaster -lSDL2
```

#### macOS
```bash
g++ main.cpp -o raycaster -I/usr/local/include -L/usr/local/lib -lSDL2
```

#### Windows (MinGW)
```bash
g++ main.cpp -o raycaster.exe -I"C:\SDL2\include" -L"C:\SDL2\lib" -lSDL2main -lSDL2
```

#### Windows (MSVC)
```bash
cl main.cpp /I "C:\SDL2\include" /link /LIBPATH:"C:\SDL2\lib\x64" SDL2.lib SDL2main.lib /SUBSYSTEM:CONSOLE
```

## Running the Game

### Linux/macOS
```bash
./raycaster
```

### Windows
```bash
raycaster.exe
```

Note: On Windows, make sure SDL2.dll is in the same directory as your executable or in your system PATH.

## Controls

- **Arrow Up/Down**: Move forward/backward
- **Arrow Left/Right**: Rotate camera
- **ESC**: Exit game

## Customization

The engine can be customized by modifying the constants in the `Config` namespace:

```cpp
namespace Config {
    // Display settings
    const int SCREEN_WIDTH = 640;      // Window width
    const int SCREEN_HEIGHT = 480;     // Window height
    const float FOV = 60.0f;           // Field of view
    
    // Player settings
    const float ROTATION_SPEED = 180.0f;  // Rotation speed
    const float MOVE_SPEED = 2.5f;        // Movement speed
    // ...more settings
}
```

## Troubleshooting

### Common Issues

1. **SDL2 not found**
   - Linux: Install SDL2 development packages
   - Windows: Check SDL2 path and environment variables
   - macOS: Ensure SDL2 is installed via Homebrew

2. **Compilation errors**
   - Make sure all prerequisites are installed
   - Check if PATH variables are set correctly
   - Verify SDL2 installation

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by Wolfenstein 3D and early raycasting games
- SDL2 community for their excellent documentation
- Contributors and supporters of this project

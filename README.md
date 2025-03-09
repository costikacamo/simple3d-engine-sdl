# Simple Raycasting Engine

A basic raycasting engine implemented in C++ using SDL2, inspired by classic games like Wolfenstein 3D.

## Features

- First-person perspective rendering using raycasting
- Smooth movement and rotation
- Collision detection
- Customizable map layout
- Configurable display and gameplay settings

## Prerequisites

- C++ compiler
- SDL2 library
- CMake (optional, for build system)

## Building

```bash
# Install SDL2 on Ubuntu/Debian
sudo apt-get install libsdl2-dev

# Compile
g++ main.cpp -o raycaster -lSDL2
```

## Controls

- Arrow Up/Down: Move forward/backward
- Arrow Left/Right: Rotate camera
- ESC: Exit game

## Customization

The engine can be customized by modifying the constants in the `Config` namespace:

- Screen resolution
- Field of view
- Movement and rotation speeds
- Map layout
- Colors and rendering parameters

## License

[Your chosen license]

## Contributing

Feel free to open issues or submit pull requests!

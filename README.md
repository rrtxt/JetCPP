___
# JetCPP

JetCPP is a 2D plane shooter game prototype built using C++ and Raylib.
This project was created to explore how games can be structured without relying on a full game engine, focusing instead on core gameplay and supporting systems implemented from scratch.

The goal of this project is learning-oriented: understanding game architecture, update loops, and system separation in a small but complete prototype.

---
## Table of Contents

- [Features](#features)
- [Tech Stack](#tech-stack)
- [Project Structure](#project-structure-high-level)
- [Installation](#installation)
- [Build Instructions (CMake)](#build-instructions-cmake)
- [Notes](#notes)

---

## Features

* Core game loop implementation
* Keyboard input handling
* Object update and rendering pipeline
* Collision detection
* Game state management (menu, gameplay, etc.)
* Simple event system
* Basic UI system
* Audio integration using Raylib

---

## Tech Stack

* **Language:** C++
* **Framework:** Raylib
* **Build System:** CMake
* **Compiler:** Any C++17-compatible compiler (GCC / Clang / MSVC)

---

## Project Structure (High Level)

```
JetCPP/
├── include/        # Headers file
├── src/            # Game source code
├── assets/         # Textures, audio, and other resources
├── CMakeLists.txt  # CMake build configuration
└── README.md
```

---

## Installation
1. Go to the **Releases** page on GitHub  
2. Download the latest Windows release (`.zip`)  
3. Extract the archive  
4. Run the executable (`.exe`)  

---

## Build Instructions (CMake)

### Prerequisites

* CMake 3.15 or newer
* C++ compiler with C++17 support
* Raylib installed on your system

### Build Steps

```bash
git clone https://github.com/rrtxt/JetCPP.git
cd JetCPP
mkdir build
cd build
cmake ..
cmake --build .
```

After a successful build, the executable will be generated inside the `build` directory.

---

## Notes

This project is a **prototype**, not a full game.
The code prioritizes clarity and learning over performance optimization or advanced engine features.

---

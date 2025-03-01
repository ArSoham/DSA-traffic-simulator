# DSA Queue Simulator

## Four-Way Junction Traffic Management System

This project implements a queue-based traffic management simulation for a four-way junction, developed as part of the Data Structure and Algorithms (COMP202) course.

![Traffic Simulation](https://github.com/ArSoham/dsa-queue-simulator/blob/main/demo.gif)

## Project Overview

The system manages normal and high-priority vehicle dispatch using queue data structures. The traffic flow is controlled by dynamically adjusting traffic lights based on queue sizes and priority conditions.

## Installation and Setup

###  Prerequisites

- C compiler (GCC or MinGW)
- SDL2 library
- Git (optional, for cloning the repository)

### Installing SDL2
1. 🔗 [Download SDL2](https://www.libsdl.org/download-2.0.php)
2. Extract contents to your project directory
3. Create folders if missing:
   - `include/` (for headers)
   - `lib/` (for library files)
   - `bin/` (for output)

## 📂 Project Structure

```
DSA-Queue-Simulator/
├── include/          # Header files
├── lib/              # Library files
├── src/              # Source files
├── bin/              # Executables
└── README.md
```

## Building the Project

```bash
# Clone the repository
git clone https://github.com/YOUR_USERNAME/dsa-queue-simulator.git
cd dsa-queue-simulator

# Compile
g++ -o bin/generator src/generator.c src/traffic_simulation.c -lSDL2 -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2
```

## Running the Simulation
1. start the main simulation:
```bash
./bin/main.exe
```
2. Watch vehicles navigate the intersection!
3. Click the close button (X) to exit.


## Contributing to this project requires to:

1.  Fork the repo
2.  Create a branch (`git checkout -b feature/AmazingFeature`)
3.  Commit changes (`git commit -m 'Add AmazingFeature'`)
4.  Push (`git push origin feature/AmazingFeature`)
5.  Open a Pull Request



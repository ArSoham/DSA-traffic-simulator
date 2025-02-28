# 🚦 DSA Queue Simulator

## Four-Way Junction Traffic Management System

This project implements a queue-based traffic management simulation for a four-way junction, developed as part of the Data Structure and Algorithms (COMP202) course.

![Traffic Simulation](https://github.com/YOUR_USERNAME/dsa-queue-simulator/blob/main/Simulation.gif)

## 📋 Project Overview

The system manages normal and high-priority vehicle dispatch using queue data structures. The traffic flow is controlled by dynamically adjusting traffic lights based on queue sizes and priority conditions.

### ✨ Key Features

- 🚗 **Queue-based Traffic Management**: Vehicles are queued in each lane and processed according to traffic rules
- 🚨 **Priority Lane Handling**: Special handling for high-priority lanes when congestion occurs
- 🖥️ **Real-time Visualization**: Graphical representation using SDL2 library
- 📁 **File-based Communication**: Vehicle generation and processing via text files

## 🏗️ System Architecture

### 🛑 Traffic Management Rules

1. **Normal Condition**: Traffic lights change based on the number of vehicles in each lane, ensuring fair service.
2. **Priority Condition**: When lane AL2 exceeds 10 vehicles, it receives exclusive service until the count drops below 5.
3. **Continuous Processing**: The system continuously monitors lane conditions and adjusts traffic flow.

### ⚙️ Core Components

- **Generator**: Creates vehicle data and writes to text files.
- **Simulator**: Reads vehicle data, manages queues, controls traffic lights, and provides visualization.

## 📊 Data Structures

| Structure | Implementation | Purpose |
|-----------|----------------|---------|
| Queue | Array-based | Storing vehicles in each lane |
| Priority Queue | Modified queue with dynamic priority | Managing high-priority lanes |

## 📚 Algorithm Design

The traffic processing algorithm follows these steps:

1. Read vehicle data from files.
2. Enqueue vehicles into respective lane queues.
3. Check priority conditions.
4. Process vehicles according to current conditions.
5. Update traffic lights accordingly.
6. Render the visualization.
7. Repeat until simulation ends.

### ⏱ Time Complexity Analysis

- **Queue Operations (enqueue, dequeue):** O(1)
- **Traffic Light Update:** O(n) where n = number of lanes
- **Vehicle Processing:** O(n)
- **Overall Time Complexity:** O(n)

## 💻 Implementation Details

### 🔑 Key Functions

```c
// Queue operations
void enqueue(Queue* q, Vehicle v);
Vehicle dequeue(Queue* q);
bool isEmpty(Queue* q);

// Traffic management
void updateTrafficLights(TrafficLight* lights);
void processTraffic(Lane* lanes);

// Visualization
void renderSimulation(SDL_Renderer* renderer, Lane* lanes);
void renderRoads(SDL_Renderer* renderer);
void renderVehicles(SDL_Renderer* renderer, Lane* lanes);

// File I/O
void readLaneData(Lane* lanes);
void writeVehicleData(Lane* lanes);
```

## 🚀 Installation and Setup

### 📌 Prerequisites

- C compiler (GCC or MinGW)
- SDL2 library
- Git (optional, for cloning the repository)

### 🛠 Installing SDL2

#### 🖥️ Windows Users:
1. 🔗 [Download SDL2](https://www.libsdl.org/download-2.0.php)
2. 📂 Extract contents to your project directory
3. 🏗 Create folders if missing:
   - `include/` (for headers)
   - `lib/` (for library files)
   - `bin/` (for output)

#### 🐧 Linux Users:
```bash
sudo apt-get install libsdl2-dev
```

#### 🍏 macOS Users:
```bash
brew install sdl2
```

## 📂 Project Structure

```
DSA-Queue-Simulator/
├── include/          # Header files
├── lib/              # Library files
├── src/              # Source files
├── bin/              # Executables
└── README.md
```

## 🏗️ Building the Project

```bash
# Clone the repository
git clone https://github.com/YOUR_USERNAME/dsa-queue-simulator.git
cd dsa-queue-simulator

# Compile the generator
g++ -o bin/generator src/generator.c src/traffic_simulation.c -lSDL2 -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2

# Compile the simulator
g++ -Iinclude -Llib -o bin/main.exe src/main.c src/traffic_simulation.c -lmingw32 -lSDL2main -lSDL2
```

## ▶️ Running the Simulation
1. start the main simulation:
```bash
./bin/main.exe
```
2. 🚗 Watch vehicles navigate the intersection!
3. ❌ Click the close button (X) to exit.

## 🏁 Traffic Management

- 🚦 **Queue System:** Each lane manages its own queue.
- 🚨 **Priority Handling:** Emergency vehicles go first.
- 🔄 **Traffic Light Cycles:** Automated red/green transitions.
- 🔁 **Turn Management:** Vehicles can turn left, right, or go straight.

## 🤝 Contributing

1. 🍴 Fork the repo
2. 🌿 Create a branch (`git checkout -b feature/AmazingFeature`)
3. 💾 Commit changes (`git commit -m 'Add AmazingFeature'`)
4. 🚀 Push (`git push origin feature/AmazingFeature`)
5. 🔥 Open a Pull Request

## 📚 References

- 📖 [SDL2 Documentation](https://wiki.libsdl.org/)
- 📘 Queue Data Structure: Introduction to Algorithms, CLRS (Cormen, Leiserson, Rivest, Stein)
- 🚑 Traffic Flow Theory: Highway Capacity Manual (Transportation Research Board)

## 🙌 Acknowledgments

- ❤️ SDL2 Dev Team
- 🔬 Traffic Simulation Research Community
- 🎯 Contributors & Testers

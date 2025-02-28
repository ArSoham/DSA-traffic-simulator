#ifndef TRAFFIC_SIMULATION_H
#define TRAFFIC_SIMULATION_H

#include <SDL.h>
#include <stdbool.h>

// Window and display constants
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define LANE_WIDTH 100
#define MAX_VEHICLES 30
#define INTERSECTION_X (WINDOW_WIDTH / 2)
#define INTERSECTION_Y (WINDOW_HEIGHT / 2)
#define STOP_LINE_WIDTH 8
#define TRAFFIC_LIGHT_WIDTH 40
#define TRAFFIC_LIGHT_HEIGHT 60
#define MIN_VEHICLE_GAP 60
#define STOP_VEHICLE_GAP 50

// Enumerations for simulation entities
typedef enum {
    DIRECTION_NORTH,
    DIRECTION_SOUTH,
    DIRECTION_EAST,
    DIRECTION_WEST,
    DIRECTION_COUNT
} Direction;

typedef enum {
    TURN_NONE,
    TURN_LEFT,
    TURN_RIGHT
} TurnDirection;

typedef enum {
    STATE_MOVING,
    STATE_STOPPING,
    STATE_STOPPED,
    STATE_TURNING,
    STATE_ACCELERATING
} VehicleState;

typedef enum {
    REGULAR_CAR,
    AMBULANCE,
    POLICE_CAR,
    FIRE_TRUCK,
    VEHICLE_TYPE_COUNT
} VehicleType;

typedef enum {
    RED,
    YELLOW,
    GREEN
} TrafficLightState;

// Vehicle structure
typedef struct {
    SDL_Rect rect;           // SDL rectangle for rendering
    VehicleType type;        // Type of vehicle
    Direction direction;     // Direction of travel
    TurnDirection turnDirection; // Turn direction if turning
    VehicleState state;      // Current state of the vehicle
    float speed;             // Current speed
    float maxSpeed;          // Maximum speed for this vehicle
    float acceleration;      // Acceleration rate
    float deceleration;      // Deceleration rate
    float x;                 // X position
    float y;                 // Y position
    bool active;             // Is the vehicle active
    float turnAngle;         // Current turning angle
    bool isInRightLane;      // Is the vehicle in the right lane
    float turnProgress;      // Progress of turning (0.0f to 1.0f)
    Uint32 creationTime;     // When the vehicle was created
    bool hasEmergencyLights; // Does the vehicle have flashing lights
} Vehicle;

// Traffic light structure
typedef struct {
    TrafficLightState state;  // Current state (RED, YELLOW, GREEN)
    int timer;               // Time in current state
    SDL_Rect position;       // Position of the traffic light
    Direction direction;     // Direction the light controls
    int greenDuration;       // How long the green light lasts
    int yellowDuration;      // How long the yellow light lasts
    int redDuration;         // How long the red light lasts
    Uint32 lastStateChange;  // When the state last changed
} TrafficLight;

// Statistics for the simulation
typedef struct {
    int vehiclesPassed;      // Vehicles that have exited the simulation
    int totalVehicles;       // Total vehicles created
    float vehiclesPerMinute; // Throughput
    Uint32 startTime;        // When simulation started
    int emergencyVehicles;   // Number of emergency vehicles
    int totalWaitTime;       // Total time vehicles spent waiting
    int maxQueueLength;      // Maximum queue length observed
    float averageSpeed;      // Average speed of vehicles
    int trafficViolations;   // Traffic light violations
} Statistics;

// Queue data structure for vehicle management
typedef struct Node {
    Vehicle vehicle;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
    Direction laneDirection;
} Queue;

// Global queue declaration
extern Queue laneQueues[DIRECTION_COUNT];

// Weather and time of day settings
typedef enum {
    WEATHER_CLEAR,
    WEATHER_RAIN,
    WEATHER_SNOW,
    WEATHER_FOG
} WeatherCondition;

typedef enum {
    TIME_DAY,
    TIME_DUSK,
    TIME_NIGHT,
    TIME_DAWN
} TimeOfDay;

typedef struct {
    WeatherCondition weather;
    TimeOfDay timeOfDay;
    float visibility;        // 0.0 to 1.0
    bool streetLightsOn;     // Are street lights on
} EnvironmentSettings;

// Function declarations
// Initialization functions
void initializeTrafficLights(TrafficLight* lights);
void initializeEnvironment(EnvironmentSettings* environment);
void initializeStatistics(Statistics* stats);

// Update functions
void updateTrafficLights(TrafficLight* lights);
void updateVehicle(Vehicle* vehicle, TrafficLight* lights, Vehicle vehicles[], int count, EnvironmentSettings* environment);
bool isSafeToMove(Vehicle* vehicle, Vehicle vehicles[], int count);
bool isSafeToStop(Vehicle* vehicle, Vehicle vehicles[], int count);

// Vehicle creation and management
Vehicle* createVehicle(Direction direction, Uint32 currentTime, EnvironmentSettings* environment);
void clearInactiveVehicles(Vehicle vehicles[], int* count);

// Rendering functions
void renderSimulation(SDL_Renderer* renderer, Vehicle* vehicles, TrafficLight* lights, Statistics* stats, EnvironmentSettings* environment);
void renderRoads(SDL_Renderer* renderer, EnvironmentSettings* environment);
void renderTrafficLights(SDL_Renderer* renderer, TrafficLight* lights);
void renderVehicles(SDL_Renderer* renderer, Vehicle* vehicles, int count, Uint32 currentTime);
void renderEnvironment(SDL_Renderer* renderer, EnvironmentSettings* environment);
void renderStatistics(SDL_Renderer* renderer, Statistics* stats);
void renderQueues(SDL_Renderer* renderer);

// Queue functions
void initQueue(Queue* q, Direction direction);
void enqueue(Queue* q, Vehicle vehicle);
Vehicle dequeue(Queue* q);
int isQueueEmpty(Queue* q);

// Environment functions
void toggleDayNight(EnvironmentSettings* environment);
void changeWeather(EnvironmentSettings* environment, WeatherCondition weather);

// Utility functions
SDL_Color getVehicleColor(VehicleType type, TimeOfDay timeOfDay);
void saveSimulationState(Vehicle vehicles[], int count, TrafficLight* lights, Statistics* stats);
bool loadSimulationState(Vehicle vehicles[], int* count, TrafficLight* lights, Statistics* stats);

#endif
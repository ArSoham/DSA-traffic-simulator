#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "traffic_simulation.h"

Queue laneQueues[DIRECTION_COUNT];
int lanePriorities[DIRECTION_COUNT] = {0};

const SDL_Color VEHICLE_COLORS[] = {
    {30, 144, 255, 255}, {255, 0, 0, 255}, {0, 0, 139, 255}, {255, 140, 0, 255}
};

const SDL_Color VEHICLE_NIGHT_COLORS[] = {
    {20, 90, 160, 255}, {180, 0, 0, 255}, {0, 0, 90, 255}, {180, 100, 0, 255}
};

const float WEATHER_SPEED_FACTORS[] = {1.0f, 0.7f, 0.5f, 0.6f};

void initializeTrafficLights(TrafficLight *lights) {
    for (int i = 0; i < DIRECTION_COUNT; i++) {
        lights[i] = (TrafficLight){
            .state = RED, .timer = 0,
            .greenDuration = 5000, .yellowDuration = 2000, .redDuration = 7000,
            .lastStateChange = SDL_GetTicks(), .direction = i
        };
    }
}

void initializeEnvironment(EnvironmentSettings *environment) {
    *environment = (EnvironmentSettings){WEATHER_CLEAR, TIME_DAY, 1.0f, false};
}

void initializeStatistics(Statistics *stats) {
    *stats = (Statistics){0, 0, 0, SDL_GetTicks(), 0, 0, 0, 0, 0};
}

void updateTrafficLights(TrafficLight *lights) {
    Uint32 currentTime = SDL_GetTicks();
    for (int i = 0; i < DIRECTION_COUNT; i++) {
        Uint32 timeInState = currentTime - lights[i].lastStateChange;
        if (lights[i].state == GREEN && timeInState >= lights[i].greenDuration) {
            lights[i].state = YELLOW;
            lights[i].lastStateChange = currentTime;
        } else if (lights[i].state == YELLOW && timeInState >= lights[i].yellowDuration) {
            lights[i].state = RED;
            lights[i].lastStateChange = currentTime;
        } else if (lights[i].state == RED && timeInState >= lights[i].redDuration) {
            lights[i].state = GREEN;
            lights[i].lastStateChange = currentTime;
        }
    }
}

Vehicle *createVehicle(Direction direction, Uint32 currentTime, EnvironmentSettings *environment) {
    Vehicle *vehicle = (Vehicle *)malloc(sizeof(Vehicle));
    vehicle->direction = direction;
    vehicle->creationTime = currentTime;
    vehicle->type = rand() % VEHICLE_TYPE_COUNT;
    vehicle->active = true;
    vehicle->speed = 3.0f * WEATHER_SPEED_FACTORS[environment->weather];
    vehicle->state = STATE_MOVING;
    vehicle->turnDirection = (rand() % 100 < 30) ? TURN_LEFT : TURN_NONE;
    vehicle->rect.w = 30;
    vehicle->rect.h = 20;
    vehicle->x = direction == DIRECTION_EAST ? -50 : (direction == DIRECTION_WEST ? WINDOW_WIDTH + 50 : INTERSECTION_X);
    vehicle->y = direction == DIRECTION_NORTH ? WINDOW_HEIGHT + 50 : (direction == DIRECTION_SOUTH ? -50 : INTERSECTION_Y);
    enqueue(&laneQueues[direction], *vehicle);
    return vehicle;
}

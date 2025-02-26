// include/vehicle.h
#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <SDL2/SDL.h>

struct Vehicle {
    std::string number;
    char lane;
    time_t arrivalTime;
    SDL_Rect position;
    int speed;
    int angle;
};

#endif
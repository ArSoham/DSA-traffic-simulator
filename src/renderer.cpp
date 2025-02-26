// src/renderer.cpp
#include "renderer.h"
#include <iostream>

Renderer::Renderer() : window(nullptr), renderer(nullptr) {}

Renderer::~Renderer() {
    SDL_DestroyTexture(carTexture);
    SDL_DestroyTexture(roadTexture);
    SDL_DestroyTexture(trafficLightTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Renderer::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Traffic Simulator", 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED,
                            SCREEN_WIDTH, 
                            SCREEN_HEIGHT, 
                            SDL_WINDOW_SHOWN);
    
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    loadTextures();
    return true;
}

void Renderer::loadTextures() {
    // Load textures from assets folder
    SDL_Surface* surface = SDL_LoadBMP("assets/car.bmp");
    if (surface) {
        carTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    surface = SDL_LoadBMP("assets/road.bmp");
    if (surface) {
        roadTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    surface = SDL_LoadBMP("assets/traffic_light.bmp");
    if (surface) {
        trafficLightTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}

void Renderer::renderJunction() {
    // Draw roads
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    
    // Vertical road
    SDL_Rect vRoad = {350, 0, 100, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &vRoad);
    
    // Horizontal road
    SDL_Rect hRoad = {0, 250, SCREEN_WIDTH, 100};
    SDL_RenderFillRect(renderer, &hRoad);
    
    // Road markings
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int i = 0; i < SCREEN_HEIGHT; i += 40) {
        SDL_RenderDrawLine(renderer, 400, i, 400, i + 20);
    }
    for(int i = 0; i < SCREEN_WIDTH; i += 40) {
        SDL_RenderDrawLine(renderer, i, 300, i + 20, 300);
    }
}

void Renderer::renderVehicles(const VehicleQueue& queue) {
    std::queue<Vehicle> vehicles = queue.getQueue();
    SDL_Rect destRect = {0, 0, 30, 50};  // Car size

    while(!vehicles.empty()) {
        Vehicle v = vehicles.front();
        vehicles.pop();
        
        destRect.x = v.position.x;
        destRect.y = v.position.y;
        
        SDL_RenderCopyEx(renderer, carTexture, NULL, &destRect, v.angle, NULL, SDL_FLIP_NONE);
    }
}

void Renderer::renderTrafficLight(int x, int y, bool isGreen) {
    SDL_Rect lightRect = {x, y, 20, 60};
    SDL_SetRenderDrawColor(renderer, 
                          isGreen ? 0 : 255,
                          isGreen ? 255 : 0,
                          0, 255);
    SDL_RenderFillRect(renderer, &lightRect);
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}
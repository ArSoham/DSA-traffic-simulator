#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "traffic_simulation.h"
#include <SDL_ttf.h>

void initializeSDL(SDL_Window **window, SDL_Renderer **renderer) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init(); // Initialize SDL_ttf
    *window = SDL_CreateWindow("Traffic Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(*renderer, 200, 200, 200, 255); // Set background color to light gray
}

void cleanupSDL(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void handleEvents(bool *running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *running = false;
        }
    }
}

void renderText(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_Color textColor = {0, 0, 0, 255}; // Black text
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Soham Aryal", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {10, 10, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    bool running = true;
    Uint32 lastVehicleSpawn = 0;
    const Uint32 SPAWN_INTERVAL = 700; // Adjusted for clarity

    srand(time(NULL));

    initializeSDL(&window, &renderer);
    
    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 1;
    }
    
    // Initialize vehicles
    Vehicle vehicles[MAX_VEHICLES] = {0};
    int vehicleCount = 0;
    TrafficLight lights[4];
    initializeTrafficLights(lights);
    Statistics stats = {0};

    while (running) {
        handleEvents(&running);
        renderSimulation(renderer, vehicles, lights, &stats);
        renderText(renderer, font);
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // 60 FPS
    }

    TTF_CloseFont(font);
    cleanupSDL(window, renderer);
    return 0;
}
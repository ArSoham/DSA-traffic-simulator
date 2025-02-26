#include <SDL2/SDL.h>
#include <iostream>
#include "queue.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

// Initialize SDL
bool initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    *window = SDL_CreateWindow("Traffic Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    return (*renderer != NULL);
}

// Draw roads and traffic lights
void drawJunction(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_Rect road = {200, 0, 400, 600};  // Vertical road
    SDL_RenderFillRect(renderer, &road);

    road = {0, 200, 800, 200};  // Horizontal road
    SDL_RenderFillRect(renderer, &road);
}

// Main simulation function
void simulateTraffic(SDL_Renderer* renderer, VehicleQueue& laneQueue) {
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawJunction(renderer);

        // Render vehicle queue visually
        int x = 100;
        int y = 100;
        std::queue<Vehicle> tempQueue = laneQueue.getQueue();

        while (!tempQueue.empty()) {
            Vehicle v = tempQueue.front();
            tempQueue.pop();

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_Rect car = {x, y, 30, 30};
            SDL_RenderFillRect(renderer, &car);

            x += 40;
            if (x > SCREEN_WIDTH - 100) {
                x = 100;
                y += 40;
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
}

// Main program
int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initSDL(&window, &renderer)) {
        return 1;
    }

    VehicleQueue laneQueue;
    laneQueue.enqueue({"ABC123", 'A'});
    laneQueue.enqueue({"DEF456", 'B'});

    simulateTraffic(renderer, laneQueue);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

// include/renderer.h
#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "queue.h"

class Renderer {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* carTexture;
    SDL_Texture* roadTexture;
    SDL_Texture* trafficLightTexture;
    
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

public:
    Renderer();
    ~Renderer();
    bool init();
    void loadTextures();
    void renderJunction();
    void renderVehicles(const VehicleQueue& queue);
    void renderTrafficLight(int x, int y, bool isGreen);
    void clear();
    void present();
    SDL_Renderer* getRenderer() { return renderer; }
};

#endif
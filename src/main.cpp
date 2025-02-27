// src/main.cpp
#include "include/renderer.h"

#include "queue.h"
#include <chrono>
#include <thread>

int main() {
    Renderer renderer;
    if (!renderer.init()) {
        return 1;
    }

    LaneManager laneManager;
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        renderer.clear();
        renderer.renderJunction();

        // Render traffic lights
        renderer.renderTrafficLight(330, 200, true);  // North
        renderer.renderTrafficLight(450, 350, false); // South
        renderer.renderTrafficLight(330, 350, false); // West
        renderer.renderTrafficLight(450, 200, false); // East

        // Render vehicles in each lane
        renderer.renderVehicles(laneManager.getLane('A'));
        renderer.renderVehicles(laneManager.getLane('B'));
        renderer.renderVehicles(laneManager.getLane('C'));
        renderer.renderVehicles(laneManager.getLane('D'));

        renderer.present();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }

    return 0;
}
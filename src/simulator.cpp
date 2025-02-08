#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include "queue.h"  // Include queue definition

#define VEHICLE_FILE "data/laneA.txt"

// Function to process traffic queue
void processTrafficQueue(VehicleQueue &queue) {
    while (true) {
        std::ifstream file(VEHICLE_FILE);
        std::string line;
        
        if (file.is_open()) {
            while (getline(file, line)) {
                std::string number = line.substr(0, line.find(':'));
                char lane = line[line.find(':') + 1];

                queue.enqueue({number, lane});
                std::cout << "Vehicle added to queue: " << number << " from lane " << lane << std::endl;
            }
            file.close();
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));  // Refresh every 2s
    }
}

int main() {
    VehicleQueue vehicleQueue;
    std::thread queueThread(processTrafficQueue, std::ref(vehicleQueue));

    while (true) {
        if (!vehicleQueue.isEmpty()) {
            Vehicle v = vehicleQueue.dequeue();
            std::cout << "Processing vehicle: " << v.number << " from lane " << v.lane << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    queueThread.join();
    return 0;
}

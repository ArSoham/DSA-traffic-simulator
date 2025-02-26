#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <string>

// Structure for vehicle
struct Vehicle {
    std::string number;
    char lane;
};

// Queue for managing vehicles
class VehicleQueue {
private:
    std::queue<Vehicle> vehicles;  // Standard queue for vehicles
public:
    void enqueue(Vehicle v);
    Vehicle dequeue();
    bool isEmpty();
    int size();
};

#endif // QUEUE_H

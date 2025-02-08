#include "queue.h"

void VehicleQueue::enqueue(Vehicle v) {
    vehicles.push(v);
}

Vehicle VehicleQueue::dequeue() {
    if (!vehicles.empty()) {
        Vehicle v = vehicles.front();
        vehicles.pop();
        return v;
    }
    return {"", ' '}; // Empty vehicle as fallback
}

bool VehicleQueue::isEmpty() {
    return vehicles.empty();
}

int VehicleQueue::size() {
    return vehicles.size();
}


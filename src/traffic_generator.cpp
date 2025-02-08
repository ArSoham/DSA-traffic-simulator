#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // For sleep()

#define FILENAME "data/laneA.txt"

// Generate random vehicle number
std::string generateVehicleNumber() {
    std::string vehicle = "";
    vehicle += (char)('A' + rand() % 26);
    vehicle += (char)('A' + rand() % 26);
    vehicle += std::to_string(rand() % 10);
    vehicle += (char)('A' + rand() % 26);
    vehicle += std::to_string(rand() % 10);
    return vehicle;
}

// Generate random lane
char generateLane() {
    char lanes[] = {'A', 'B', 'C', 'D'};
    return lanes[rand() % 4];
}

int main() {
    std::ofstream file;
    srand(time(0));

    while (true) {
        file.open(FILENAME, std::ios::app);
        if (!file) {
            std::cerr << "Error opening file!" << std::endl;
            return 1;
        }

        std::string vehicle = generateVehicleNumber();
        char lane = generateLane();

        file << vehicle << ":" << lane << std::endl;
        file.close();

        std::cout << "Generated: " << vehicle << ":" << lane << std::endl;
        sleep(1); // Wait 1 second before generating next vehicle
    }

    return 0;
}

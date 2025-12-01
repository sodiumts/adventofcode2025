#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <print>
#include <string>
#include <utility>
#include <vector>


enum Rots {LEFT = 0, RIGHT = 1};


int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::string line;
    std::vector<std::pair<Rots, uint64_t>> rotations;
    while(std::getline(file, line)) {
        std::pair<Rots, uint64_t> insertable;
        if (line[0] == 'L') insertable.first = LEFT;
        else insertable.first = RIGHT;

        insertable.second = std::stoull(line.substr(1, line.length())); 
        rotations.push_back(insertable);
    }
 
    int64_t currentRotation = 50;
    uint64_t zeros = 0;
    for (auto &rot: rotations) {
        if (rot.first == RIGHT) {
            zeros += rot.second / 100;
            uint64_t leftoverRotation = rot.second % 100;
            
            uint64_t newSum = leftoverRotation + currentRotation;
            if (newSum % 100 == 0) {
                zeros++;
                currentRotation = 0;
            } else if (newSum / 100 > 0) {
                zeros++;
                currentRotation = newSum % 100;
            } else {
                currentRotation = newSum;
            }
        } else {
            int64_t newRotation = currentRotation - rot.second;
            if (newRotation > 0) {
                currentRotation = newRotation;
                continue;
            };
            if (currentRotation == 0) {
                zeros--;
            }

            uint64_t rotationCounts = (-newRotation) / 100; 
            zeros += rotationCounts;
            
            newRotation = newRotation + (100 * (rotationCounts + 1));

            if (newRotation % 100 == 0) {
                zeros++;
                currentRotation = 0; 
                continue;
            }
            zeros++;
            currentRotation = newRotation;
        }
    }
    std::println("Zero count {}", zeros);
    return 1;
}

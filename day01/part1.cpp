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
            currentRotation += rot.second;
        } else {
            currentRotation -= rot.second;
            if (currentRotation < 0) {
                currentRotation = 100 + currentRotation;
            }
        }
        if (currentRotation % 100 == 0) {
            zeros++;
            currentRotation = 0;
        };
    }
    std::println("Zero count {}", zeros);
    return 1;
}

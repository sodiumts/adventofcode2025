#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <print>
#include <string>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::vector<uint64_t> idxRanges;
    std::string line;


    uint64_t answer;
    while(std::getline(file, line)) {
        if (line.empty()) break;
        
        uint8_t outsideMax = 0;
        uint8_t insideMax = 0;
        for (uint64_t i = 0; i < line.length() - 1; i++) {
            uint8_t outsideBat = line[i] - '0';

            if (outsideBat <= outsideMax) continue;
            outsideMax = outsideBat;
            insideMax = 0;

            for (uint64_t j = i + 1; j < line.length(); j++) {
                uint8_t insideBat = line[j] - '0';
                if (insideBat <= insideMax) continue;
                insideMax = insideBat;
            }
        }
        
        uint8_t lineMax = outsideMax * 10 + insideMax;
        answer += lineMax;
    }
    

    std::println("Answer: {}", answer);
 
    return 1;
}

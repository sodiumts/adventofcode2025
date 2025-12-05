#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <print>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::vector<std::pair<uint64_t, uint64_t>> idxRanges;
    std::string line;
    while(std::getline(file, line)) {
        if (line.empty()) break;

        std::istringstream stream(line);
        
        std::string split;
        bool firstString = true;
        uint64_t startidx = 0;
        uint64_t endidx = 0;
        while(std::getline(stream, split, '-')) {
            if (firstString) {
                startidx = std::stoull(split);
                firstString = false;
            } else {
                endidx = std::stoull(split);
            }    
        }
        
        idxRanges.push_back({startidx, endidx});
    }
    
    uint64_t answer = 0;
    while(std::getline(file, line)) {
        uint64_t numcheck = std::stoull(line);
        for (const auto& ranges: idxRanges) {
            if (numcheck >= ranges.first && numcheck <= ranges.second) {
                answer++;
                break;
            }
        } 
    }

    std::println("Answer: {}", answer);
 
    return 1;
}

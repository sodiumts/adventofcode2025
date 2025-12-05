#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <print>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>

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
    
    std::sort(idxRanges.begin(), idxRanges.end(), [](std::pair<uint64_t, uint64_t> a, std::pair<uint64_t, uint64_t> b) { return a.first < b.first; });
    
    std::vector<std::pair<uint64_t, uint64_t>> newPairs;
    uint64_t previousPairIndex = 0;
    newPairs.push_back(idxRanges[0]);
    for (int i = 1; i < idxRanges.size(); i++) {
        auto previousPair = newPairs[previousPairIndex];
        if(previousPair.second >= idxRanges[i].first) {
            if (previousPair.second >= idxRanges[i].second) continue;
            newPairs[previousPairIndex] = {previousPair.first, idxRanges[i].second}; 
        } else {
            newPairs.push_back({idxRanges[i].first, idxRanges[i].second});
            previousPairIndex++;
        }
    }

    uint64_t answer = 0;
    for (const auto& range: newPairs) {
        answer += range.second - range.first + 1;
    }

    std::println("Answer: {}", answer);
 
    return 1;
}

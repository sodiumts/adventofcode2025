#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <print>
#include <string>
#include <vector>

uint8_t up(const std::vector<std::vector<bool>>& map, uint8_t row, uint8_t col) {
    uint8_t totalCount = 0;
    if (map[row-1][col-1]) totalCount++;
    if (map[row-1][col]) totalCount++;
    if (map[row-1][col+1]) totalCount++;

    return totalCount;
}

uint8_t mid(const std::vector<std::vector<bool>>& map, uint8_t row, uint8_t col) {
    uint8_t totalCount = 0;
    if (map[row][col-1]) totalCount++;
    if (map[row][col+1]) totalCount++;

    return totalCount;
}

uint8_t dow(const std::vector<std::vector<bool>>& map, uint8_t row, uint8_t col) {
    uint8_t totalCount = 0;
    if (map[row+1][col-1]) totalCount++;
    if (map[row+1][col]) totalCount++;
    if (map[row+1][col+1]) totalCount++;

    return totalCount;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::vector<std::vector<bool>> papersMap;

    std::string line;
    bool firstTime = true;
    while(std::getline(file, line)) {
        if (firstTime) {
            std::vector<bool> v(line.length() + 2, false);
            papersMap.push_back(v);
            firstTime = false;
        }

        if (line.empty()) break;
        std::vector<bool> linePapers = {false};

        for (const auto& slot: line) {
            if (slot == '.') linePapers.push_back(false);
            else linePapers.push_back(true);
        }

        linePapers.push_back(false);

        papersMap.push_back(linePapers);
    }

    papersMap.push_back(papersMap[0]);
    
    uint64_t colCount = papersMap[0].size();
   
    uint64_t answer = 0;
    uint64_t removedRolls;
    while(true) {
        removedRolls = 0;
        for (uint64_t row = 1; row < papersMap.size() - 1; row++) {
            for (uint64_t col = 1; col < colCount - 1; col++) {
                if (papersMap[row][col] == false) continue;
                if (up(papersMap, row, col) + mid(papersMap, row, col) + dow(papersMap, row, col) < 4) {
                    papersMap[row][col] = false;
                    removedRolls++;
                }
            }
        }
    
        if (removedRolls == 0) {
            break;
        } else {
            answer += removedRolls;
        }
    }


    for (const auto& line: papersMap) {
        for (const auto &p: line) {
            std::print("{}", p ? '1' : '0');
        }
        std::println();
    }
    

    std::println("Answer: {}", answer);
 
    return 1;
}

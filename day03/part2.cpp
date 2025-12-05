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
        


        
    }
    

    std::println("Answer: {}", answer);
 
    return 1;
}

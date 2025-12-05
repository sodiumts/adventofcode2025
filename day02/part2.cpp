#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <print>
#include <string>
#include <utility>
#include <vector>
#include <sstream>


bool check_num_invalid(std::string &num) { 
    int substringidx = 1;
    std::string subs = num.substr(0, substringidx); 
    int nextidx = 0;

    while(true) {
        if (subs == num.substr(nextidx, subs.length())) {
            nextidx += subs.length();
            if (nextidx == num.length()) return true;
        } else {
            substringidx++;
            if (substringidx > num.length() / 2) return false;

            subs = num.substr(0, substringidx);
            nextidx = 0;
        }
    }
}


int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::vector<std::pair<uint64_t, uint64_t>> idRanges;
    std::string line;
    while(std::getline(file, line)) {
        if (line.empty()) break;

        std::istringstream stream(line);
        
        std::string split;
    
        while(std::getline(stream, split, ',')) {
            std::istringstream stream2(split);

            std::string split2;
            std::uint64_t firstId = 0;
            std::uint64_t secondId = 0;
            bool firstNum = true;
            while(std::getline(stream2, split2, '-')) {
                if (firstNum) {
                    firstId = std::stoull(split2);
                    firstNum = false;
                } else {
                    secondId = std::stoull(split2);
                }
            }
            
            idRanges.push_back({firstId, secondId});
        }
    }

    uint64_t answer = 0;    
    for (const auto& range: idRanges) { 
        for (uint64_t i = range.first; i <= range.second; i++) {
            std::string stringnum = std::to_string(i);
            if (stringnum.length() == 1) continue;
            
            if (check_num_invalid(stringnum)) {
                answer += std::stoull(stringnum);
            }
        }

    }


    std::println("Answer: {}", answer);
 
    return 1;
}

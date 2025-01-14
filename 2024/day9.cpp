#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

void partOne(std::vector<std::string> &blocks) {
    auto it = std::find(blocks.begin(), blocks.end(), ".");
    if (it != blocks.end()) {
        while (!std::all_of(it, blocks.end(), [](std::string c) { return c == "."; })) {

            int indexOfFirstEmptyBlock = std::distance(blocks.begin(), it);
            int indexOfLastFileBlock= blocks.size() - 1;
            
            while(blocks[indexOfLastFileBlock] == ".") {
                indexOfLastFileBlock--;
            }

            std::swap(blocks[indexOfFirstEmptyBlock], blocks[indexOfLastFileBlock]);
            blocks.back() = ".";
            it = std::find(blocks.begin(), blocks.end(), ".");
        }
    } 
}

void moveFiles(std::vector<std::string> &blocks, int& maxId) {
    auto itLastFileEnd = std::find_if(blocks.rbegin(), blocks.rend(), [&maxId](std::string s) {
        return s != "." && std::stoi(s) < maxId;
    });
    maxId--;
    auto itLastFileStart = std::find_if(itLastFileEnd, blocks.rend(), [itLastFileEnd](std::string s) { return s !=*itLastFileEnd;});
    int numberOfFileBlocks = std::distance(itLastFileEnd, itLastFileStart);

    std::vector<std::string> pattern(numberOfFileBlocks, ".");
    auto itFirstAvailable = std::search(blocks.begin(), blocks.end(), pattern.begin(), pattern.end());
    
    if (itFirstAvailable == blocks.end()) {
        return;
    }

    int indexOfFirstEmptyBlock = std::distance(blocks.begin(), itFirstAvailable);
    int startIndexOfLastFile = blocks.size() - std::distance(blocks.rbegin(), itLastFileStart);
    
    if (indexOfFirstEmptyBlock > startIndexOfLastFile) {
        return;
    }

    for (int i = 0; i < numberOfFileBlocks; i++) {
        std::swap(blocks[startIndexOfLastFile + i], blocks[indexOfFirstEmptyBlock + i]);
    }
}

void partTwo(std::vector<std::string> &blocks, const int& id) {
    int maxId = id;
    for (int i = 0; i < id; i++) {
        moveFiles(blocks, maxId);
    }
}

int main() {
    std::ifstream file;
    file.open("C:/Projects/AdventOfCode/2024/day9data.txt");
    // file.open("C:/Users/sebas/projekt/AdventOfCode/2024/day9data.txt");


    if ( !file.is_open() ) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;  
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    bool part1 = false;
    double sum = 0;
    std::vector<std::string> blocks;
    int count = 0;
    int id = 0;

    for (char c : content) {
        int value = c - '0';
        std::string stringToAdd;
        (count++ % 2 == 0) ? stringToAdd = std::to_string(id++) : stringToAdd = ".";
        
        for (int i = 0; i < value; i++) {
            blocks.push_back(stringToAdd);
        }
    }
    
    if (part1) {
        partOne(blocks);
    } else {
        partTwo(blocks, id);
    }

    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] == "." && part1) {
            break;
        } else if (blocks[i] == "." && !part1) {
            continue;
        }
        sum += i*std::stoi(blocks[i]);
    }
    std::cout << std::endl;

    std::cout << "sum: " << std::fixed << std::setprecision(0) << sum << std::endl;

    file.close();
    return 0;
}
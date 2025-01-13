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

void moveFiles(std::vector<std::string> &blocks, std::vector<std::string>& bannedIds, int& maxId) {
    // auto itFirstEmptyBlock = std::find(blocks.begin(), blocks.end(), ".");

    // int indexOfFirstEmptyBlock = std::distance(blocks.begin(), itFirstEmptyBlock);
    // // std::cout << "empty block startindex: " << indexOfFirstEmptyBlock << std::endl;

    // auto itNextUsedBlock = std::find_if(itFirstEmptyBlock, blocks.end(), [](std::string s) { return s != ".";});

    // int numberOfEmptyBlocks = std::distance(itFirstEmptyBlock, itNextUsedBlock);

    // std::cout << "no . empty blocks: " << numberOfEmptyBlocks << std::endl;
    auto itLastFileEnd = std::find_if(blocks.rbegin(), blocks.rend(), [&maxId](std::string s) {
        return s != "." && std::stoi(s) < maxId; //Can use int instead
    });

    // bannedIds.push_back(*itLastFileEnd);

    // std::cout << "first block startindex from end: " << std::distance(blocks.rbegin(), itLastFileEnd) << std::endl;
    
    auto itLastFileStart = std::find_if(itLastFileEnd, blocks.rend(), [itLastFileEnd](std::string s) { return s !=*itLastFileEnd;});

    // std::cout << "first block endindex from end: " << std::distance(itLastFileEnd, itLastFileStart) << std::endl;

    int numberOfFileBlocks = std::distance(itLastFileEnd, itLastFileStart);
    // std::cout << "found file with id " << *itLastFileEnd << " which is " << numberOfFileBlocks << " file blocks long" << std::endl;
    
    if (std::stoi(*itLastFileEnd) % 100 == 0) {
        int percent = 100 - std::stoi(*itLastFileEnd) / 100;
        std::cout << percent << " percent DONE..." << std::endl;
    }

    std::vector<std::string> pattern(numberOfFileBlocks, ".");
    auto itFirstAvailable = std::search(blocks.begin(), blocks.end(), pattern.begin(), pattern.end());
    
    if (itFirstAvailable == blocks.end()) {
        return;
    }
    int indexOfFirstEmptyBlock = std::distance(blocks.begin(), itFirstAvailable);
        
    int startIndexOfLastFile = blocks.size() - std::distance(blocks.rbegin(), itLastFileStart);
    // std::cout << "last file startindex: " << startIndexOfLastFile << std::endl;
    
    if (indexOfFirstEmptyBlock > startIndexOfLastFile) {
        return;
    }

    for (int i = 0; i < numberOfFileBlocks; i++) {
        std::swap(blocks[startIndexOfLastFile + i], blocks[indexOfFirstEmptyBlock + i]);
    }

    // else {
    //     itFirstEmptyBlock = std::find(itNextUsedBlock, blocks.end(), ".");

    //     if (std::find_if(itFirstEmptyBlock, blocks.end(), [](std::string s) { return s != ".";}) != blocks.end()) {
    //         moveFiles(blocks, bannedIds);
    //     } else {
    //         bannedIds.push_back(*itLastFileEnd);
    //     }
    // }
}

void partTwo(std::vector<std::string> &blocks, const int& id) {
    // std::cout << "BEFORE SWAP" << std::endl;

    // for (int i = 0; i < blocks.size(); i++) {
    //     std::cout << blocks[i];
    // }
    // std::cout << std::endl;
    // auto itFirstEmptyBlo = std::find(blocks.begin(), blocks.end(), ".");
    int iterations = 1;
    std::vector<std::string> bannedIds;
    int maxId = id;
    // if (itFirstEmptyBlo != blocks.end()) {
        // while (std::find(bannedIds.begin(), bannedIds.end(), *blocks.begin()) == bannedIds.end()) {
        for (int i = 0; i < id; i++) {
            moveFiles(blocks, bannedIds, maxId);
            maxId--;
            // itFirstEmptyBlo = std::find(blocks.begin(), blocks.end(), ".");

            // std::cout << "AFTER SWAP: " << iterations++ << std::endl;
            // for (int i = 0; i < blocks.size(); i++) {
            //     std::cout << blocks[i];
            // }
            // std::cout << std::endl;

            // std::cout << "BANNED IDs: ";
            // for (int i = 0; i < bannedIds.size(); i++) {
            //     std::cout << bannedIds[i] << " ";
            // }
            // std::cout << std::endl;
        }
    // } 
}

int main() {
    std::ifstream file;
    // file.open("C:/Projects/AdventOfCode/2024/day9data.txt");
    // file.open("C:/Projects/AdventOfCode/2024/day9data.txt");
    file.open("C:/Users/sebas/projekt/AdventOfCode/2024/day9data.txt");


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
    // std::cout << id;
    
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
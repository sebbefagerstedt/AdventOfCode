#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <set>
#include <tuple>

void findAntennaPos(const std::vector< std::vector <char>> map, std::vector<std::vector<std::pair<int,int>>>& antennaPos, std::vector<char>& antennaTypes) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if( map[i][j] != '.') {
                auto it = std::find(antennaTypes.begin(), antennaTypes.end(), map[i][j]);
                std::pair<int,int> coord = {i,j};
                if (it != antennaTypes.end()) {
                    size_t pos = std::distance(antennaTypes.begin(), it);
                    antennaPos[pos].push_back(coord);
                } else {
                    antennaTypes.push_back(map[i][j]);
                    std::vector<std::pair<int,int>> newType;
                    newType.push_back(coord);
                    antennaPos.push_back(newType);
                }
            }
        }
    }
}
bool isNodeInMap(const int mapWidth, const int mapHeight, const int row, const int col) {
    return (col >= 0 && col < mapWidth && row >= 0 && row < mapHeight);
}

bool isNodeInVector(const std::vector<std::pair<int,int>> vector, const std::pair<int,int> Node) {
    return std::find(vector.begin(), vector.end(), Node) != vector.end();
}

std::pair<int, int> createNodeCoords(const int& antennaPos1, const int& antennaPos2, int& multiplier) {
    int diff = std::abs(antennaPos1 - antennaPos2);
    int antiNode1coord = antennaPos1;
    int antiNode2coord = antennaPos2;

    if (antiNode1coord > antiNode2coord) {
        antiNode1coord += diff*multiplier;
        antiNode2coord -= diff*multiplier;
    } else {
        antiNode1coord -= diff*multiplier;
        antiNode2coord += diff*multiplier;
    }

    return {antiNode1coord, antiNode2coord};
}

std::vector<std::pair<int,int>> generateInvalidAntiNodePos(std::vector<std::vector<std::pair<int,int>>>& antennaPos) {
    std::vector<std::pair<int,int>> invalidAntiNodePos;
    for (int i = 0; i < antennaPos.size(); i++) {
        if (antennaPos[i].size() == 1) {
            if (!isNodeInVector(invalidAntiNodePos, antennaPos[i][0])) {
                invalidAntiNodePos.push_back(antennaPos[i][0]);
            }
        }
    }
    return invalidAntiNodePos;
}

std::vector<std::pair<int,int>> createAntinodePos(std::vector<std::vector<std::pair<int,int>>>& antennaPos, const int mapWidth, const int mapHeight, const bool part1) {
    std::vector<std::pair<int,int>> uniqueAntinodePos;

    for (int i = 0; i < antennaPos.size(); i++) {
        if (antennaPos[i].size() > 1) {

            if (!part1) { // Add antennaNodes
                for (int j = 0; j < antennaPos[i].size(); j++) {
                    std::pair<int,int> antennaNode = {antennaPos[i][j].first, antennaPos[i][j].second};
                    if(!isNodeInVector(uniqueAntinodePos, antennaNode)) {
                        uniqueAntinodePos.push_back(antennaNode);
                    }
                }
            }
            
            for (int j = 0; j < antennaPos[i].size() - 1; j++) {
                for (int k = j + 1; k < antennaPos[i].size(); k++) {
                    bool continueGenerateNodes = true;
                    int multiplier = 1;
                    while(continueGenerateNodes) {
                        auto [antiNode1Row, antiNode2Row] = createNodeCoords(antennaPos[i][j].first, antennaPos[i][k].first, multiplier);
                        auto [antiNode1Col, antiNode2Col] = createNodeCoords(antennaPos[i][j].second, antennaPos[i][k].second, multiplier);
                        std::pair<int,int> Node1 = {antiNode1Row, antiNode1Col};
                        std::pair<int,int> Node2 = {antiNode2Row, antiNode2Col};
                        std::vector<std::pair<int,int>> invalidAntiNodesPos = generateInvalidAntiNodePos(antennaPos);

                        if (isNodeInMap(mapWidth, mapHeight, antiNode1Row,antiNode1Col) && !isNodeInVector(uniqueAntinodePos, Node1) && !isNodeInVector(invalidAntiNodesPos, Node1)) {
                            uniqueAntinodePos.push_back(Node1);      
                        }
                        if (isNodeInMap(mapWidth, mapHeight, antiNode2Row,antiNode2Col) && !isNodeInVector(uniqueAntinodePos, Node2) && !isNodeInVector(invalidAntiNodesPos, Node2)) {
                            uniqueAntinodePos.push_back(Node2);
                        }
                        multiplier++;
                        bool nodesOutsideMap = (!isNodeInMap(mapWidth, mapHeight, antiNode1Row,antiNode1Col) && !isNodeInMap(mapWidth, mapHeight, antiNode2Row,antiNode2Col));
                        if(part1 || nodesOutsideMap) {
                            continueGenerateNodes = false;
                        }
                    }
                }
            }
        }
    }
    return uniqueAntinodePos;
}

int main() {
    std::ifstream file;
    std::string line;
    std::vector< std::vector <char>> map;
    bool part1 = false;

    file.open("C:/Users/sebas/projekt/AdventOfCode/2024/day8data.txt");

    if ( !file.is_open() ) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;  
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        char pos_data;
        std::vector <char> maprow;

        while (ss >> pos_data) {
            maprow.push_back(pos_data);
        }
        map.push_back(maprow);
    }

    std::vector< std::vector<std::pair<int,int>> > antennaPos;
    std::vector<char> antennaTypes;

    findAntennaPos(map, antennaPos, antennaTypes);
    int mapWidth = map[0].size();
    int mapHeight = map.size();

    std::vector<std::pair<int,int>> uniqueAntinodePos = createAntinodePos(antennaPos, mapWidth, mapHeight, part1);
    std::cout << "Number of pos: " << uniqueAntinodePos.size();
}
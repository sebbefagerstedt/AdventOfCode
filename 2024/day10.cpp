#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <set>
#include <tuple>

// struct with pointers in all directions, null if no path possible;
// maybe a bool that says if it is a trailhead and top
// save score in struct
// save trailheads in a vector
struct Coordinate {
    int row, col;

    // Constructor to initialize coordinates
    Coordinate(int rowCoord, int colCoord) : row(rowCoord), col(colCoord) {}

    // Display function for coordinates
    void display() const {
        std::cout << "(" << row << ", " << col << ")";
    }
};

struct Node {
    Coordinate coordinate;
    int height;
    int score;
    int rating;
    Node* up;
    Node* down;
    Node* left;
    Node* right;

    Node(int height, int row, int col)
        :  height(height), coordinate(row,col), score(0), rating(0), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
};

// DFS algorithm
void findPaths(Node* current, std::set<Node*>& visited, std::vector<Node*>& path, std::vector<std::vector<Node*>>& allPaths, std::set<Node*>& visitedPeaks) {
    if (!current || visited.count(current)) return; // Null or already visited

    visited.insert(current);
    path.push_back(current); 

    if (current->height == 9) {
        allPaths.push_back(path);
        if (!visitedPeaks.count(current)) {
            visitedPeaks.insert(current);
            path[0]->score++;
        }
        path[0]->rating++;
    } else {
        // Explore neighbors
        findPaths(current->up, visited, path, allPaths,visitedPeaks);
        findPaths(current->down, visited, path, allPaths,visitedPeaks);
        findPaths(current->left, visited, path, allPaths,visitedPeaks);
        findPaths(current->right, visited, path, allPaths,visitedPeaks);
    }

    // Backtrack
    path.pop_back();
    visited.erase(current);
}

int main() {
    std::ifstream file;
    std::string line;
    std::vector< std::vector <int>> map;
    bool part1 = false;

    // file.open("C:/Users/sebas/projekt/AdventOfCode/2024/testdata.txt");
    file.open("C:/Projects/AdventOfCode/2024/day10data.txt");

    if ( !file.is_open() ) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;  
    }

    std::vector<std::vector<Node*>> nodes;
    std::vector<Node*> trailheads;
    int row = 0;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        char pos_data;
        std::vector<Node*> rownodes;
        int col = 0;
        while (ss >> pos_data) {
            int height = pos_data - '0';
            Node* node = new Node(height,row,col);
            if (height == 0) {
                trailheads.push_back(node);
            }
            rownodes.push_back(node);
            col++;
        }
        nodes.push_back(rownodes);
        row++;
    }

    //link nodes
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes[i].size(); j++) { 
            Node* current = nodes[i][j];
            int nextHeight = current->height + 1;
            if (i > 0 && nodes[(i - 1)][j]->height == nextHeight) current->up = nodes[(i - 1)][j]; 
            if (i < nodes.size() - 1 && nodes[(i + 1)][j]->height == nextHeight) current->down = nodes[(i + 1)][j];
            if (j > 0 && nodes[i][j - 1]-> height == nextHeight) current->left = nodes[i][j - 1];
            if (j < nodes[i].size() - 1 && nodes[i][j + 1]->height == nextHeight ) current->right = nodes[i][j + 1];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    int totalScore = 0;
    int totalRating = 0;
    std::vector<std::vector<Node*>> allPaths;
    for (Node* start : trailheads) {
        std::set<Node*> visited;
        std::vector<Node*> path;
        std::set<Node*> visitedPeaks;

        findPaths(start, visited, path, allPaths, visitedPeaks);
        totalScore += start->score;
        totalRating += start->rating;
    }

    // std::cout << "All paths from 0 to 9:\n";
    // for (const auto& path : allPaths) {
    //     for (const auto& node : path) {
    //         node->coordinate.display();
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << "Total score: " << totalScore << std::endl;
    std::cout << "Total rating: " << totalRating << std::endl;

    file.close();
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

//day1 = 2493
//day2 = 1890
void check_for_xmas(std::vector< std::vector <char>> crossword, int i, int j, int &number_of_xmas) {
    if (crossword[i][j] == 'X') {
        // Northwest
        if (i >= 3 && j >= 3 && crossword[i-1][j-1] == 'M' && crossword[i-2][j-2] == 'A' && crossword[i-3][j-3] == 'S') {
            number_of_xmas += 1;
        }
        // North
        if (i >= 3 && crossword[i-1][j] == 'M' && crossword[i-2][j] == 'A' && crossword[i-3][j] == 'S') {
            number_of_xmas += 1;
        }
        // Northeast
        if (i >= 3 && j <= crossword[i].size() - 4 && crossword[i-1][j+1] == 'M' && crossword[i-2][j+2] == 'A' && crossword[i-3][j+3] == 'S') {
            number_of_xmas += 1;
        }
        // West
        if (j >= 3 && crossword[i][j-1] == 'M' && crossword[i][j-2] == 'A' && crossword[i][j-3] == 'S') {
            number_of_xmas += 1;
        }
        // East
        if (j <= crossword[i].size() - 4 && crossword[i][j+1] == 'M' && crossword[i][j+2] == 'A' && crossword[i][j+3] == 'S') {
            number_of_xmas += 1;
        }
        // Southwest
        if (i <= crossword.size() - 4 && j >= 3 && crossword[i+1][j-1] == 'M' && crossword[i+2][j-2] == 'A' && crossword[i+3][j-3] == 'S') {
            number_of_xmas += 1;
        }
        // South
        if (i <= crossword.size() - 4 && crossword[i+1][j] == 'M' && crossword[i+2][j] == 'A' && crossword[i+3][j] == 'S') {
            number_of_xmas += 1;
        }
        // Southeast
        if (i <= crossword.size() - 4 && j <= crossword[i].size() - 4 && crossword[i+1][j+1] == 'M' && crossword[i+2][j+2] == 'A' && crossword[i+3][j+3] == 'S') {
            number_of_xmas += 1;
        }
    }
}

void check_for_cross_MAS(std::vector< std::vector <char>> crossword, std::vector< std::vector <int>> &MAS_matrix, int i, int j, int &number_of_xmas) {
    if (crossword[i][j] == 'M') {
        // Northwest
        if (i >= 2 && j >= 2 && crossword[i-1][j-1] == 'A' && crossword[i-2][j-2] == 'S') {
            MAS_matrix[i-1][j-1]++;
        }
        // Northeast
        if (i >= 2 && j <= crossword[i].size() - 3 && crossword[i-1][j+1] == 'A' && crossword[i-2][j+2] == 'S') {
            MAS_matrix[i-1][j+1]++;
        }
        // Southwest
        if (i <= crossword.size() - 3 && j >= 2 && crossword[i+1][j-1] == 'A' && crossword[i+2][j-2] == 'S') {
            MAS_matrix[i+1][j-1]++;
        }
        // Southeast
        if (i <= crossword.size() - 3 && j <= crossword[i].size() - 3 && crossword[i+1][j+1] == 'A' && crossword[i+2][j+2] == 'S') {
            MAS_matrix[i+1][j+1]++;
        }
    }
}

int main() {
    std::ifstream file;
    std::string line;
    std::vector< std::vector <char>> crossword;
    std::vector< std::vector <int>> MAS_matrix;

    bool part1 = false;
    int number_of_xmas = 0;
    file.open("day4data.txt");
    if ( !file.is_open() ) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;  
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        char letter;
        std::vector <char> wordrow;
        std::vector <int> zeros_row;

        while (ss >> letter) {
            wordrow.push_back(letter);
            zeros_row.push_back(0);
        }
        crossword.push_back(wordrow);
        MAS_matrix.push_back(zeros_row);
    }

    for (int i = 0; i < crossword.size(); i++) {
        for (int j = 0; j < crossword[i].size(); j++) {
            if (part1){
                check_for_xmas(crossword, i, j, number_of_xmas);
            } else {
                check_for_cross_MAS(crossword, MAS_matrix, i, j, number_of_xmas);
            }
        }
    }

    if (!part1) {
        for (int i = 0; i < MAS_matrix.size(); i++) {
            for (int j = 0; j < MAS_matrix[i].size(); j++) {
                if (MAS_matrix[i][j] == 2) {
                    number_of_xmas += 1;
                }
            }
        }
    }
    
    std::cout << number_of_xmas << std::endl;

    return 0;
}


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <set>
#include <tuple>

int main() {
    std::ifstream file;
    std::string line;
    std::vector< std::vector <int>> equations;

    bool part1 = true;
    int col = -1;
    int row = -1;
    char direction = 'X';

    // file.open("testdata.txt");
    file.open("C:/Users/sebas/projekt/AdventOfCode/2024/testdata.txt");
    
    if ( !file.is_open() ) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;  
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        int result;
        char colon;
        int number;
        std::vector <int> equation;
        ss >> result >> colon;
        equation.push_back(result);
        while (ss >> number) {
            equation.push_back(number);
        }
        equations.push_back(equation);
    }

    if (part1) {   
        for (int i = 0; i < equations.size(); i++) {
            for (int j = 0; j < equations[i].size(); j++) {
                std::cout << equations[i][j] << ",";
            }
            std::cout << std::endl;
        }

    }
      
    return 0;
}


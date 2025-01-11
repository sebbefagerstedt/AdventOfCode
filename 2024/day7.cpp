#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <set>
#include <tuple>
#include <cstdint>
//Answer part 1: 20281182715321 correct
//Answer part 2: 159490400628354 correct

long long evaluate(const std::vector<int>& equation, const std::vector<std::string>& operators) {
    long long result = equation[0];

    for (size_t i = 0; i < operators.size(); i++) {

        if (operators[i] == "+") {
            result += equation[i + 1];
        } else if (operators[i] == "*") {
            result *= equation[i + 1];
        } else if (operators[i] == "||") {
            std::string concatenated = std::to_string(result) + std::to_string(equation[i + 1]);
            result = std::stoll(concatenated);
        }
    }
    return result;
}

bool equationIsValid(const long long result, const std::vector<int>& equation, std::vector<std::string>& operatorTypes) {
    size_t numOperators = equation.size() - 1;

    int baseNumber = operatorTypes.size();
    int totalCombinations = 1;

    for (int i = 0; i < numOperators; i++) {
        totalCombinations *= baseNumber;
    }

    for (int i = 0; i < totalCombinations; i++) {
        std::vector<int> operatorCombination;
        std::vector<std::string> operators;
        int currentCombination = i;

        for (int j = 0; j < numOperators; j++) {
            operators.push_back(operatorTypes[currentCombination % baseNumber]);
            currentCombination /= baseNumber;
        }

        long long equationResult = evaluate(equation, operators);
        if (result == equationResult) {
            return true;
        }
    }

    return false;
}

int main() {
    std::ifstream file;
    std::string line;
    std::vector< std::vector <int>> equations;
    std::vector< long long> results;
    std::vector<std::string> operatorTypes;
    bool part1 = false;
    long long sumValidEquations = 0;

    file.open("C:/Users/sebas/projekt/AdventOfCode/2024/day7data.txt");
    
    if ( !file.is_open() ) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;  
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        long long result;
        char colon;
        int number;
        std::vector <int> equation;
        ss >> result >> colon;
        results.push_back(result);
        while (ss >> number) {
            equation.push_back(number);
        }
        equations.push_back(equation);
    }

    if (part1) { 
        operatorTypes = {"+", "*"};
    } else {
        operatorTypes = {"+", "*", "||"};
    }  

    for (int i = 0; i < equations.size(); i++) {           

        if(equationIsValid(results[i],equations[i], operatorTypes)) {
            sumValidEquations += results[i];
        }
    }
    std::cout << sumValidEquations << std::endl;
    
      
    return 0;
}


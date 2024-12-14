#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <regex>

int main() {
    std::ifstream file;
    double sum = 0;

    // file.open("C:/Projects/AdventOfCode/day3data.txt");
    file.open("C:/Users/sebas/projekt/AdventOfCode/2024/day3data.txt");

    if ( file.is_open() ) { 
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        std::regex pattern(R"(mul\((\d+),(\d+)\))"); //divided into 3 parts 0 is the full, 1 is first int and 2 is second int
        std::string do_string = "do()";
        std::string dont_string = "don't()";
        size_t position_dont;
        size_t next_position_do;

        while (content.find(dont_string) != std::string::npos) {
            // finds index of next occuring "don't"
            position_dont = content.find(dont_string);

            // finds index of next do() command that occurs after the don't command
            std::string leftover_content = content.substr(position_dont,content.size()); 
            next_position_do = leftover_content.find(do_string);

            // erases next_position_do index amount of character from content starting from "don't" 
            content.erase(position_dont, next_position_do);
        }
        
        auto words_begin = std::sregex_iterator(content.begin(), content.end(), pattern);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            int num1 = std::stoi(match.str(1));
            int num2 = std::stoi(match.str(2));
            sum += num1*num2;
        }
        
    }
    file.close();
    std::cout << std::fixed << std::setprecision(0) << sum << std::endl;
    return 0;
}
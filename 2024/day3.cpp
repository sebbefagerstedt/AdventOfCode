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

    file.open("C:/Projects/AdventOfCode/2024/day3data.txt");
    // file.open("C:/Users/sebas/projekt/AdventOfCode/2024/day3data.txt");

    if ( file.is_open() ) { 
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        std::regex pattern(R"(mul\((\d+),(\d+)\))"); //divided into 3 parts 0 is the full, 1 is first int and 2 is second int
        std::string do_string = "do()";
        std::string dont_string = "don't()";

        size_t position_dont = 0;
        while ((position_dont = content.find(dont_string, position_dont)) != std::string::npos) {
            size_t next_position_do;

            // std::string leftover_content = content.substr(position_dont,content.size()); 
            next_position_do = content.find(do_string, position_dont);
            int char_to_rem = (next_position_do != std::string::npos) ? next_position_do - position_dont : content.size() - position_dont;
            content.erase(position_dont, char_to_rem);
        }
        
        auto words_begin = std::sregex_iterator(content.begin(), content.end(), pattern);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            int num1 = std::stoi(match.str(1));
            int num2 = std::stoi(match.str(2));
            sum += num1*num2;
        }
        
    } else {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;  // Exit the program with an error code
    }
    

    file.close();
    std::cout << std::fixed << std::setprecision(0) << sum << std::endl;
    return 0;
}
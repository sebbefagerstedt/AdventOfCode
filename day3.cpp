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

    file.open("C:/Projects/AdventOfCode/day3data.txt");
    //old answer: 133332996 too high
    //new answer: 133332996

    if ( file.is_open() ) { 
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();


        std::regex pattern(R"(mul\((\d+),(\d+)\))");
        std::string do_string = "do()";
        std::string dont_string = "don't()";
        size_t position_dont;
        size_t position_do;


        std::string leftover_content = content;
        std::string new_content = "";

        while (leftover_content.find(dont_string) != std::string::npos || leftover_content.find(do_string) != std::string::npos) {
            position_dont = leftover_content.find(dont_string);
            position_do = leftover_content.find(do_string);
            if (position_do == std::string::npos) {
                position_do = leftover_content.size() - 1;
            } else if (position_dont == std::string::npos) {
                position_dont = leftover_content.size() - 1;
            }
            new_content += leftover_content.substr(0, position_dont);
            leftover_content.erase(0, position_do + do_string.size());
        }

        new_content += leftover_content;
        std::cout << new_content << std::endl;

        auto words_begin = std::sregex_iterator(new_content.begin(), new_content.end(), pattern);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            int num1 = std::stoi(match.str(1));
            int num2 = std::stoi(match.str(2));
            // std::cout << num1 << " " << num2 << std::endl;
            sum += num1*num2;
        }
        
    }
    file.close();
    std::cout << std::fixed << std::setprecision(0) << sum << std::endl;

    return 0;
}
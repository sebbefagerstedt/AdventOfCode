#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {
    std::ifstream report_list;
    std::string line;
    int number_safe_levels = 0;
    
    report_list.open("day2data.txt");

    if ( report_list.is_open() ) { 
        while (std::getline(report_list, line)) {
            std::vector<int> levels;
            int number_of_increasing = 0;
            std::istringstream ss(line);
            int level;
            bool safe_report = true;

            while (ss >> level) {
                levels.push_back(level);
            }

            for (int i = 1; i < levels.size(); i++) {
                if (levels[i] > levels[i-1]) {
                    number_of_increasing++;
                } 

                if (std::abs(levels[i] - levels[i-1]) < 1 || std::abs(levels[i] - levels[i-1]) > 3) {
                    safe_report = false;
                    break;
                }
            }
            std::cout << "increasing: " << std::fixed << std::setprecision(0) << number_of_increasing << std::endl;
            std::cout << "safe report: " << safe_report << std::endl;

            if ((number_of_increasing == levels.size() - 1 || number_of_increasing == 0) && safe_report) {
                number_safe_levels++;
            }
        }
    }

    report_list.close();

    std::cout << std::fixed << std::setprecision(0) << number_safe_levels << std::endl;
}
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
            std::istringstream ss(line);
            int level;

            while (ss >> level) {
                levels.push_back(level);
            }

            int safe_modified_reports = 0;
            
            for (int a = 0; a < levels.size(); ++a){
                int safe_level = true;
                int number_of_increasing = 0;
                std::vector<int> modifiedLevels = levels;
                modifiedLevels.erase(modifiedLevels.begin() + a);

                for (int i = 1; i < modifiedLevels.size(); i++) {
                    if (modifiedLevels[i] > modifiedLevels[i-1]) {
                        number_of_increasing++;
                    } 

                    if (std::abs(modifiedLevels[i] - modifiedLevels[i-1]) < 1 || std::abs(modifiedLevels[i] - modifiedLevels[i-1]) > 3) {
                        safe_level = false;
                    }
                }

                if ((number_of_increasing == levels.size() - 2 || number_of_increasing == 0) && safe_level) {
                    safe_modified_reports++;
                }
            }
                
            if (safe_modified_reports != 0 ) {
                number_safe_levels++;
            }
        }

    }

    report_list.close();

    std::cout << std::fixed << std::setprecision(0) << number_safe_levels << std::endl;
}
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>
#include <cmath>

void processData(std::ifstream& file, std::vector<std::pair<int, int>> &rules, std::vector<std::vector<int>> &updates) {
    std::string line;
    std::regex patternRules(R"(^(\d+)\|(\d+)$)");
    std::regex patternUpdates(R"(^(\d+,)*\d+$)");

    while (std::getline(file, line)) {
        std::smatch matches;
        if (std::regex_match(line, matches, patternRules)) {
            int first = std::stoi(matches[1]);
            int second = std::stoi(matches[2]);
            rules.emplace_back(first, second);
        } else if (std::regex_match(line, matches, patternUpdates)) {
            std::istringstream lineStream(line);
            std::string number;
            std::vector<int> numbers;
            while (std::getline(lineStream, number, ',')) {
                numbers.push_back(std::stoi(number));
            }
            updates.push_back(numbers);
        }
    }
}
bool is_ok_update(std::vector<int> &list, std::vector<std::pair<int, int>> &rules) {
    std::vector<int> pages_done;
    bool ok_update = true;
    for (size_t i = 0; i < list.size(); ++i) {
        for (const auto& pair : rules) {
            if (list[i] == pair.second && std::find(pages_done.begin(), pages_done.end(), pair.first) == pages_done.end() && std::find(list.begin(), list.end(), pair.first) != list.end()) { 
                ok_update = false;
                break;
            }
        }
        pages_done.push_back(list[i]);
    }
    return ok_update;
}

void improve_update(std::vector<int> &list, std::vector<std::pair<int, int>> &rules) {
    std::vector<int> pages_done;
    for (size_t i = 0; i < list.size(); ++i) {
        for (const auto& pair : rules) {
            auto first_it = std::find(list.begin(), list.end(), pair.first);
            if (list[i] == pair.second && std::find(pages_done.begin(), pages_done.end(), pair.first) == pages_done.end() && first_it != list.end()) {
                std::size_t first_index = std::distance(list.begin(), first_it);
                auto second_it = list.begin() + i;  
                list.insert(second_it, pair.first);
                list.erase(list.begin() + first_index + 1);
                break;
            }
        }
        pages_done.push_back(list[i]);
    }
}

int main() {
    std::ifstream file;
    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;
    int sum_of_middle_numbers = 0;
    int sum_of_middle_numbers_improved_updates = 0;

    file.open("day5data.txt");
    if ( !file.is_open() ) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;  
    }

    processData(file, rules, updates);
    file.close();

    for (std::vector<int>& list : updates) { 
        if (is_ok_update(list, rules)) {
            sum_of_middle_numbers += list[list.size() / 2];
        } else {
            while(!is_ok_update(list, rules)) {
                improve_update(list, rules);
            }
            sum_of_middle_numbers_improved_updates += list[list.size() / 2];
        }
    }
    std::cout << "Total sum: " << sum_of_middle_numbers << std::endl;
    std::cout << "Total sum improved: " << sum_of_middle_numbers_improved_updates << std::endl;

    return 0;
}
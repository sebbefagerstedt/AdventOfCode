#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <set>
#include <tuple>

void find_guardpos(std::vector< std::vector <char>> &map, int &row, int &col, char &direction) {

    bool found = false;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            switch (map[i][j]) {
                case '^':
                    row = i;
                    col = j;
                    direction = 'N';
                    found = true;
                    break;
                case 'v':
                    row = i;
                    col = j;
                    direction = 'S';
                    found = true;
                    break;
                case '<':
                    row = i;
                    col = j;
                    direction = 'W';
                    found = true;
                    break;
                case '>':
                    row = i;
                    col = j;
                    direction = 'E';
                    found = true;
                    break;
                default:
                    break;
            }
        }

        if (found) {
            break; 
        }
    }
}

void track_guard(std::vector< std::vector <char>> &map, int row, int col, char &direction, bool &guard_leaving) {
    int curr_i = row;
    int curr_j = col;

    while (!guard_leaving && map[curr_i][curr_j] != '#') {
        map[curr_i][curr_j] = 'X';
        switch (direction) {
            case 'N':
                if (curr_i == 0) {
                    guard_leaving = true;
                    break;
                }
                else if (map[curr_i - 1][curr_j] == '#') {
                    map[curr_i][curr_j] = '>';
                }
                curr_i--;
                break;
            case 'S':
                if (curr_i == map.size() - 1) {
                    guard_leaving = true;
                    break;
                } else if (map[curr_i + 1][curr_j] == '#') {
                    map[curr_i][curr_j] = '<';
                }
                curr_i++;
                break;
            case 'W':
                if (curr_j == 0) {
                    guard_leaving = true;
                    break;
                } else if (map[curr_i][curr_j - 1] == '#') {
                    map[curr_i][curr_j] = '^';
                }
                curr_j--;
                break;
            case 'E':
                if (curr_j == map[0].size() - 1) {
                    guard_leaving = true;
                } else if (map[curr_i][curr_j + 1] == '#') {
                    map[curr_i][curr_j] = 'v';
                }
                curr_j++;
                break;
            default:
                break;
        }

    }

}

int count_dpos(std::vector< std::vector <char>> map) {
    int number_of_dpos = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 'X') {
                number_of_dpos++;
            }
        }
    }
    return number_of_dpos;
}

int main() {
    std::ifstream file;
    std::string line;
    std::vector< std::vector <char>> map;
    bool part1 = false;
    int col = -1;
    int row = -1;
    char direction = 'X';

    file.open("day6data.txt");
    
    if ( !file.is_open() ) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;  
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        char pos_data;
        std::vector <char> maprow;

        while (ss >> pos_data) {
            maprow.push_back(pos_data);
        }
        map.push_back(maprow);
    }

    if (part1) {   
        bool guard_leaving = false;

        while(!guard_leaving) {
            find_guardpos(map, row, col, direction);
            track_guard(map, row, col, direction, guard_leaving);
        }

        int number_of_dpos = count_dpos(map);    
        std::cout << number_of_dpos << std::endl;

    } else {
        int no_working_obstruction = 0;

        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if (i == 79 && j == 87 ) {
                    continue;
                }
                bool guard_leaving = false;

                std::vector< std::vector <char>> map_copy = map;
                map_copy[i][j] = '#';
                std::set<std::tuple<int, int, char>> visited;

                while (!guard_leaving) {
                    find_guardpos(map_copy, row, col, direction);
                    track_guard(map_copy, row, col, direction, guard_leaving);
                    if (visited.find({row, col, direction}) != visited.end()) {
                        no_working_obstruction++;
                        std::cout << "obstruction pos: " << i << "," << j << std::endl;
                        break;
                    }
                    visited.insert({row, col, direction});

                }   
            }
        }
        std::cout << no_working_obstruction << std::endl; 
    }
    return 0;
}


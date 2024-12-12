#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {
    std::ifstream location_lists;
    std::string line;
    std::vector<double> leftList, rightList;
    double distance_difference;
    double similarity_score;
    location_lists.open("day1data.txt");

    if ( location_lists.is_open() ) { 
        while (std::getline(location_lists, line)) {
            std::istringstream ss(line);
            double left, right;
            if (ss >>left >> right) {
                leftList.push_back(left);
                rightList.push_back(right);
            }
        }
    }

    location_lists.close();

    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    for (int i = 0; i < leftList.size(); i++) {
        double difference = leftList[i] - rightList[i];
        distance_difference += std::abs(difference);

        int occurrences = 0;
        auto it = std::find(rightList.begin(), rightList.end(), leftList[i]);
        while (it != rightList.end()) {
            occurrences++;
            it = std::find(it + 1, rightList.end(), leftList[i]);
        }
        
        similarity_score += occurrences*leftList[i];
    }

    std::cout << std::fixed << std::setprecision(0) << distance_difference << std::endl;
    std::cout << std::fixed << std::setprecision(0) << similarity_score << std::endl;
}
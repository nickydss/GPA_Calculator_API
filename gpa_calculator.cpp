//g++ -std=c++17 -o gpa_calculator gpa_calculator.cpp
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"

double calculateGPA(const std::vector<std::string>& grades, const std::vector<int>& credits) {
    double totalQualityPoints = 0.0;
    int totalCredits = 0;
    auto getGradePoints = [](const std::string& grade) -> double {
        if (grade == "A") return 4.0;
        if (grade == "A-") return 3.7;
        if (grade == "B+") return 3.3;
        if (grade == "B") return 3.0;
        if (grade == "B-") return 2.7;
        if (grade == "C+") return 2.3;
        if (grade == "C") return 2.0;
        if (grade == "C-") return 1.7;
        if (grade == "D+") return 1.3;
        if (grade == "D") return 1.0;
        return 0.0;
    };

    for (size_t i = 0; i < grades.size(); ++i) {
        totalQualityPoints += getGradePoints(grades[i]) * credits[i];
        totalCredits += credits[i];
    }
    return (totalCredits > 0) ? (totalQualityPoints / totalCredits) : 0.0;
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    auto json = nlohmann::json::parse(input);

    std::vector<std::string> grades = json["grades"];
    std::vector<int> credits = json["credits"];

    double gpa = calculateGPA(grades, credits);
    nlohmann::json result = { {"gpa", gpa} };
    std::cout << result.dump() << std::endl;

    return 0;
}

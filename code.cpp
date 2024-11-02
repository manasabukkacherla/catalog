#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <json/json.h> 
#include <cmath>


long long decodeBase(const std::string& value, int base) {
    long long result = 0;
    for (char digit : value) {
        result *= base;
        if (digit >= '0' && digit <= '9') {
            result += digit - '0';
        } else if (digit >= 'a' && digit <= 'f') {
            result += digit - 'a' + 10;
        }
    }
    return result;
}

// Function to perform Lagrange Interpolation to find f(0), which is the constant term
long long lagrangeInterpolation(const std::vector<std::pair<int, long long>>& points, int k) {
    long long result = 0;
    for (int i = 0; i < k; ++i) {
        long long term = points[i].second;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= -points[j].first;
                term /= (points[i].first - points[j].first);
            }
        }
        result += term;
    }
    return result;
}

int main() {
    // Load JSON file
    std::ifstream file("testcase.json");
    Json::Value root;
    file >> root;
    file.close();

    // Parse keys for n and k
    int n = root["keys"]["n"].asInt();
    int k = root["keys"]["k"].asInt();

    // Parse and decode points (x, y) from JSON
    std::vector<std::pair<int, long long>> points;
    for (const auto& key : root.getMemberNames()) {
        if (key == "keys") continue;

        int x = std::stoi(key);
        int base = root[key]["base"].asInt();
        std::string valueStr = root[key]["value"].asString();
        long long y = decodeBase(valueStr, base);

        points.push_back({x, y});
    }

    // Calculate the constant term using Lagrange Interpolation
    long long constantTerm = lagrangeInterpolation(points, k);

    // Output the result
    std::cout << "The constant term (secret) is: " << constantTerm << std::endl;

    return 0;
}

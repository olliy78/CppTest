#include "operations.h"
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <filesystem>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <limits>
#include <iterator>
#include <vector>
#include <string>

std::vector<double> readNumbers(const std::string& filename) {
    if (!std::filesystem::exists(filename)) {
        throw std::runtime_error("Input file does not exist: " + filename);
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open input file: " + filename);
    }

    std::vector<double> numbers;
    std::string token;
    while (file >> token) {
        try {
            size_t idx = 0;
            double val = std::stod(token, &idx);
            if (idx == token.size()) {
                numbers.push_back(val);
            }
        } catch (const std::exception&) {
            // ungültiges Token -> überspringen
            continue;
        }
    }

    if (numbers.empty()) {
        throw std::runtime_error("No valid numbers found in input file: " + filename);
    }

    return numbers;
}

void writeResult(const std::string& filename, double result) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open output file: " + filename);
    }
    file << std::setprecision(std::numeric_limits<double>::digits10 + 1) << result << '\n';
}

double performAdd(const std::vector<double>& numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), 0.0);
}

double performSubtract(const std::vector<double>& numbers) {
    if (numbers.empty()) {
        throw std::runtime_error("No numbers to subtract");
    }
    return std::accumulate(std::next(numbers.begin()), numbers.end(), numbers[0],
                           [](double a, double b) { return a - b; });
}

double performMultiply(const std::vector<double>& numbers) {
    if (numbers.empty()) {
        throw std::runtime_error("No numbers to multiply");
    }
    return std::accumulate(std::next(numbers.begin()), numbers.end(), numbers[0],
                           [](double a, double b) { return a * b; });
}

double performDivide(const std::vector<double>& numbers) {
    if (numbers.empty()) {
        throw std::runtime_error("No numbers to divide");
    }
    return std::accumulate(std::next(numbers.begin()), numbers.end(), numbers[0],
                           [](double a, double b) {
                               if (b == 0.0) throw std::runtime_error("Division by zero");
                               return a / b;
                           });
}

static std::string toLowerTrim(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    std::copy_if(s.begin(), s.end(), std::back_inserter(out), [](unsigned char c){ return !std::isspace(c); });
    std::transform(out.begin(), out.end(), out.begin(), [](unsigned char c){ return std::tolower(c); });
    return out;
}

Operation parseOperation(const std::string& opStr) {
    static const std::unordered_map<std::string, Operation> map = {
        {"add", Operation::ADD},
        {"subtract", Operation::SUBTRACT},
        {"multiply", Operation::MULTIPLY},
        {"divide", Operation::DIVIDE}
    };

    std::string key = toLowerTrim(opStr);
    auto it = map.find(key);
    if (it != map.end()) return it->second;

    throw std::invalid_argument("Invalid operation: " + opStr);
}
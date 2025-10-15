#include "operations.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <numeric>

std::vector<double> readNumbers(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open input file: " + filename);
    }

    std::vector<double> numbers;
    double num;
    while (file >> num) {
        numbers.push_back(num);
    }

    if (numbers.empty()) {
        throw std::runtime_error("No numbers found in input file");
    }

    return numbers;
}

void writeResult(const std::string& filename, double result) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open output file: " + filename);
    }
    file << result << std::endl;
}

double performAdd(const std::vector<double>& numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), 0.0);
}

double performSubtract(const std::vector<double>& numbers) {
    if (numbers.empty()) {
        throw std::runtime_error("No numbers to subtract");
    }
    double result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        result -= numbers[i];
    }
    return result;
}

double performMultiply(const std::vector<double>& numbers) {
    if (numbers.empty()) {
        throw std::runtime_error("No numbers to multiply");
    }
    double result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        result *= numbers[i];
    }
    return result;
}

double performDivide(const std::vector<double>& numbers) {
    if (numbers.empty()) {
        throw std::runtime_error("No numbers to divide");
    }
    double result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] == 0.0) {
            throw std::runtime_error("Division by zero");
        }
        result /= numbers[i];
    }
    return result;
}

Operation parseOperation(const std::string& opStr) {
    if (opStr == "add") {
        return Operation::ADD;
    } else if (opStr == "subtract") {
        return Operation::SUBTRACT;
    } else if (opStr == "multiply") {
        return Operation::MULTIPLY;
    } else if (opStr == "divide") {
        return Operation::DIVIDE;
    } else {
        throw std::invalid_argument("Invalid operation: " + opStr);
    }
}

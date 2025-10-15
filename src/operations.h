#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <vector>
#include <string>

enum class Operation {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

// Read numbers from a file
std::vector<double> readNumbers(const std::string& filename);

// Write result to a file
void writeResult(const std::string& filename, double result);

// Perform operations
double performAdd(const std::vector<double>& numbers);
double performSubtract(const std::vector<double>& numbers);
double performMultiply(const std::vector<double>& numbers);
double performDivide(const std::vector<double>& numbers);

// Parse operation string
Operation parseOperation(const std::string& opStr);

#endif // OPERATIONS_H

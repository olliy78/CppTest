#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include "../src/operations.h"

namespace fs = std::filesystem;

class OperationsTest : public ::testing::Test {
protected:
    std::string testDir = "/tmp/cpptest_tests";
    
    void SetUp() override {
        // Create test directory
        fs::create_directories(testDir);
    }
    
    void TearDown() override {
        // Clean up test files
        fs::remove_all(testDir);
    }
    
    std::string createTestFile(const std::string& filename, const std::string& content) {
        std::string fullPath = testDir + "/" + filename;
        std::ofstream file(fullPath);
        file << content;
        file.close();
        return fullPath;
    }
    
    std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string content;
        std::string line;
        while (std::getline(file, line)) {
            content += line;
        }
        return content;
    }
};

TEST_F(OperationsTest, ReadNumbersFromFile) {
    std::string testFile = createTestFile("input.txt", "1.0 2.0 3.0 4.0 5.0");
    std::vector<double> numbers = readNumbers(testFile);
    
    ASSERT_EQ(numbers.size(), 5);
    EXPECT_DOUBLE_EQ(numbers[0], 1.0);
    EXPECT_DOUBLE_EQ(numbers[1], 2.0);
    EXPECT_DOUBLE_EQ(numbers[2], 3.0);
    EXPECT_DOUBLE_EQ(numbers[3], 4.0);
    EXPECT_DOUBLE_EQ(numbers[4], 5.0);
}

TEST_F(OperationsTest, ReadNumbersEmptyFile) {
    std::string testFile = createTestFile("empty.txt", "");
    EXPECT_THROW(readNumbers(testFile), std::runtime_error);
}

TEST_F(OperationsTest, ReadNumbersNonexistentFile) {
    EXPECT_THROW(readNumbers(testDir + "/nonexistent.txt"), std::runtime_error);
}

TEST_F(OperationsTest, WriteResult) {
    std::string outputFile = testDir + "/output.txt";
    writeResult(outputFile, 42.5);
    
    std::string content = readFile(outputFile);
    EXPECT_EQ(content, "42.5");
}

TEST_F(OperationsTest, PerformAdd) {
    std::vector<double> numbers = {1.0, 2.0, 3.0, 4.0, 5.0};
    double result = performAdd(numbers);
    EXPECT_DOUBLE_EQ(result, 15.0);
}

TEST_F(OperationsTest, PerformAddSingleNumber) {
    std::vector<double> numbers = {42.0};
    double result = performAdd(numbers);
    EXPECT_DOUBLE_EQ(result, 42.0);
}

TEST_F(OperationsTest, PerformAddNegativeNumbers) {
    std::vector<double> numbers = {-1.0, -2.0, -3.0};
    double result = performAdd(numbers);
    EXPECT_DOUBLE_EQ(result, -6.0);
}

TEST_F(OperationsTest, PerformSubtract) {
    std::vector<double> numbers = {10.0, 2.0, 3.0};
    double result = performSubtract(numbers);
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST_F(OperationsTest, PerformSubtractSingleNumber) {
    std::vector<double> numbers = {42.0};
    double result = performSubtract(numbers);
    EXPECT_DOUBLE_EQ(result, 42.0);
}

TEST_F(OperationsTest, PerformMultiply) {
    std::vector<double> numbers = {2.0, 3.0, 4.0};
    double result = performMultiply(numbers);
    EXPECT_DOUBLE_EQ(result, 24.0);
}

TEST_F(OperationsTest, PerformMultiplySingleNumber) {
    std::vector<double> numbers = {42.0};
    double result = performMultiply(numbers);
    EXPECT_DOUBLE_EQ(result, 42.0);
}

TEST_F(OperationsTest, PerformMultiplyWithZero) {
    std::vector<double> numbers = {2.0, 0.0, 4.0};
    double result = performMultiply(numbers);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(OperationsTest, PerformDivide) {
    std::vector<double> numbers = {100.0, 2.0, 5.0};
    double result = performDivide(numbers);
    EXPECT_DOUBLE_EQ(result, 10.0);
}

TEST_F(OperationsTest, PerformDivideSingleNumber) {
    std::vector<double> numbers = {42.0};
    double result = performDivide(numbers);
    EXPECT_DOUBLE_EQ(result, 42.0);
}

TEST_F(OperationsTest, PerformDivideByZero) {
    std::vector<double> numbers = {10.0, 0.0};
    EXPECT_THROW(performDivide(numbers), std::runtime_error);
}

TEST_F(OperationsTest, ParseOperationAdd) {
    Operation op = parseOperation("add");
    EXPECT_EQ(op, Operation::ADD);
}

TEST_F(OperationsTest, ParseOperationSubtract) {
    Operation op = parseOperation("subtract");
    EXPECT_EQ(op, Operation::SUBTRACT);
}

TEST_F(OperationsTest, ParseOperationMultiply) {
    Operation op = parseOperation("multiply");
    EXPECT_EQ(op, Operation::MULTIPLY);
}

TEST_F(OperationsTest, ParseOperationDivide) {
    Operation op = parseOperation("divide");
    EXPECT_EQ(op, Operation::DIVIDE);
}

TEST_F(OperationsTest, ParseOperationInvalid) {
    EXPECT_THROW(parseOperation("invalid"), std::invalid_argument);
}

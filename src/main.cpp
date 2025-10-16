#include <iostream>
#include <string>
#include <getopt.h>
#include "operations.h"


// Function to display help message
void printHelp() {
    std::cout << "Usage: cpptest -o <operation> <input_file> <output_file>\n";
    std::cout << "       cpptest -h|--help\n\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help              Display this help message\n";
    std::cout << "  -o, --operation <op>    Specify operation: add, subtract, multiply, divide\n\n";
    std::cout << "Arguments:\n";
    std::cout << "  <input_file>            Input file with space-separated numbers\n";
    std::cout << "  <output_file>           Output file for the result\n\n";
    std::cout << "Operations:\n";
    std::cout << "  add                     Add all numbers from input file\n";
    std::cout << "  subtract                Subtract all numbers sequentially\n";
    std::cout << "  multiply                Multiply all numbers\n";
    std::cout << "  divide                  Divide all numbers sequentially\n";
}

// Main function‚
int main(int argc, char* argv[]) {
    std::string operation;
    bool helpRequested = false;

    // Define long options
    static struct option long_options[] = {
        {"help",      no_argument,       0, 'h'},
        {"operation", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;

    // Parse options
    while ((opt = getopt_long(argc, argv, "ho:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'h':
                helpRequested = true;
                break;
            case 'o':
                operation = optarg;
                break;
            case '?':
                // getopt_long already printed an error message
                return 1;
            default:
                return 1;
        }
    }

    // If help is requested, print help and exit
    if (helpRequested) {
        printHelp();
        return 0;
    }

    // Check if operation is specified
    if (operation.empty()) {
        std::cerr << "Error: Operation must be specified with -o or --operation\n";
        std::cerr << "Use -h or --help for usage information\n";
        return 1;
    }

    // Check if input and output files are specified
    if (optind + 2 > argc) {
        std::cerr << "Error: Input and output files must be specified\n";
        std::cerr << "Use -h or --help for usage information\n";
        return 1;
    }

    std::string inputFile = argv[optind];
    std::string outputFile = argv[optind + 1];

    try {
        // Parse the operation
        Operation op = parseOperation(operation);

        // Read numbers from input file
        std::vector<double> numbers = readNumbers(inputFile);

        // Perform operation
        double result;
        switch (op) {
            case Operation::ADD:
                result = performAdd(numbers);
                break;
            case Operation::SUBTRACT:
                result = performSubtract(numbers);
                break;
            case Operation::MULTIPLY:
                result = performMultiply(numbers);
                break;
            case Operation::DIVIDE:
                result = performDivide(numbers);
                break;
        }

        // Write result to output file
        writeResult(outputFile, result);

        std::cout << "Operation completed successfully. Result written to " << outputFile << std::endl;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

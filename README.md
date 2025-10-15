# CppTest
C++ Command-Line Calculator

## Description
A command-line program that performs arithmetic operations (add, subtract, multiply, divide) on numbers from an input file and writes the result to an output file.

## Building
```bash
mkdir build
cd build
cmake ..
make
```

## Usage
```bash
cpptest -o <operation> <input_file> <output_file>
cpptest -h|--help
```

### Options
- `-h, --help` - Display help message
- `-o, --operation <op>` - Specify operation: add, subtract, multiply, divide

### Operations
- `add` - Add all numbers from input file
- `subtract` - Subtract all numbers sequentially (first - second - third - ...)
- `multiply` - Multiply all numbers
- `divide` - Divide all numbers sequentially (first / second / third / ...)

### Examples
```bash
# Add numbers
echo "1 2 3 4 5" > input.txt
./cpptest -o add input.txt output.txt
cat output.txt  # Shows: 15

# Subtract numbers
echo "10 2 3" > input.txt
./cpptest --operation subtract input.txt output.txt
cat output.txt  # Shows: 5

# Multiply numbers
echo "2 3 4" > input.txt
./cpptest -o multiply input.txt output.txt
cat output.txt  # Shows: 24

# Divide numbers
echo "100 2 5" > input.txt
./cpptest -o divide input.txt output.txt
cat output.txt  # Shows: 10
```

## Testing
Run unit tests:
```bash
cd build
./cpptest_tests
```

## Input File Format
Input files should contain space-separated numbers, for example:
```
1.5 2.0 3.5 4.0
```

## Requirements
- CMake 3.10 or higher
- C++17 compatible compiler
- Google Test (automatically downloaded during build)

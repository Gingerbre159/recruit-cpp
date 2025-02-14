#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>

/*
Exercise: Basic Statistics Calculator

Implement a Statistics calculator that can process a series of integers and compute basic statistics.

Requirements:
1. Complete the Stats class implementation below
2. The class should store the following statistics:
   - sum: The sum of all numbers
   - max: The maximum value
   - avg: The average (mean) value as a double
3. The program should handle standard input correctly in normal mode

Notes:
- Handle empty input appropriately
- Consider edge cases like negative numbers
- The calculate() method should process the input vector and update all statistics
*/

class Stats {
    public:
        Stats() = default;
        Stats(const std::vector<int>& data) {
            calculate(data);
        }

        void calculate(const std::vector<int>& data);

        int sum{0};
        int max{0};
        double avg{0.0};
};

void
Stats::calculate(const std::vector<int>& data) {
    if (data.empty()) {
        sum = 0;
        max = 0;
        avg = 0.0;
        return;
    }

    // Reset stats
    sum = 0;
    max = data[0];
    avg = 0.0;

    // Find sum and max
    for (int num : data) {
        sum += num;
        if (num > max) {
            max = num;
        }
    }

    // Find avg
    avg = static_cast<double>(sum) / data.size();
}

// Unit test function
bool runUnitTests() {
    struct TestCase {
        std::vector<int> input;
        int expectedSum;
        int expectedMax;
        double expectedAvg;
    };

    std::vector<TestCase> testCases = {
        {{1, 2, 3, 4, 5}, 15, 5, 3.0},          // Test case 1: Positive numbers
        {{-1, -2, -3, -4, -5}, -15, -1, -3.0},  // Test case 2: Negative numbers
        {{}, 0, 0, 0.0},                        // Test case 3: Empty input
        {{-1, 2, -3, 4, -5}, -3, 4, -0.6},      // Test case 4: Mixed negative and positive numbers
        {{1, -2, 3, -4, 5}, 3, 5, 0.6},         // Test case 5: More mixed negative and positive numbers
        {{42}, 42, 42, 42.0},                   // Test case 6: Single element
        {{0, 0, 0, 0, 0}, 0, 0, 0.0},           // Test case 7: All zeros
        {{1000000, 2000000, 3000000}, 6000000, 3000000, 2000000.0}, // Test case 8: Large numbers
        {{5, 5, 5, 5}, 20, 5, 5.0},             // Test case 9: Duplicate values
        {{-42}, -42, -42, -42.0}                // Test case 10: Single negative element
    };

    bool allTestsPassed = true;

    for (const auto& testCase : testCases) {
        Stats s(testCase.input);

        if (s.sum != testCase.expectedSum ||
            s.max != testCase.expectedMax ||
            std::abs(s.avg - testCase.expectedAvg) > 1e-6) {
                std::cerr << "Test failed for input: {";
                for (int num : testCase.input) {
                    std:: cerr << num << " ";
                }
                std::cerr << "}" << std::endl;
                std::cerr << "Expected: Sum = " << testCase.expectedSum
                        << ", Max = " << testCase.expectedMax
                        << ", Avg = " << testCase.expectedAvg << std::endl;
                std::cerr << "Actual: Sum = " << s.sum
                        << ", Max = " << s.max
                        << ", Avg = " << s.avg << std::endl;
                allTestsPassed = false;
        }
    }

    return allTestsPassed;
}

int main(int argc, char** argv) {
    // Check if running in test mode
    if (argc == 2 && std::strcmp(argv[1], "--test") == 0) {
        std::cout << "Running unit tests..." << std::endl;
        bool allTestsPassed = runUnitTests();

        if (allTestsPassed) {
            std::cout << "All tests passed!" << std::endl;
            return 0; // Exit with code 0 (success)
        } else {
            std::cerr << "Some tests failed." << std::endl;
            return 1; // Exit with code 1 (failure)
        }
    }

    // Normal mode: Read input and compute stats
    std::vector<int> data;
    int num;

    std::cout << "Enter integers (Ctrl + Z (Windows) or Ctrl + D (Mac/Linux) to end input)" << std::endl;

    while (std::cin >> num) {
        data.push_back(num);
    }

    // Exit with appropriate message if input is invalid
    if (std::cin.fail() && !std::cin.eof()) {
        std::cerr << "Error: Invalid input. Please enter integers only." << std::endl;
        return 1;
    }

    Stats s(data);
     
    std::cout << "Count: " << data.size() << std::endl;
    std::cout << "Sum:   " << s.sum << std::endl;
    std::cout << "Max:   " << s.max << std::endl;
    std::cout << "Avg:   " << std::fixed << std::setprecision(6)
              << s.avg << std::endl;
    
    return 0;
}

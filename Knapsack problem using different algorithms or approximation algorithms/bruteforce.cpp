/* I have done this assignment completely on my own. I have not copied it, nor have I given
my solution to anyone else. I understand that if I am involved in plagiarism or cheating I
will have to sign an official form that I have cheated and that this form will be stored in my
official university record. I also understand that I will receive a grade of 0 for the involved
assignment for my first offense and that I will receive a grade of “F” for the course for
any additional offense.

Narendra Dhuraji Khatpe
B00984858

*/


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// Custom data structure representing an item in the knapsack problem
struct Item {
    std::string name;  // Name or identifier of the item
    int profit;        // Profit or value associated with the item
    int weight;        // Weight of the item
};

/**
 * @brief Converts a binary number to its decimal equivalent.
 * 
 * @param binary Binary number to be converted.
 * @param n Number of bits in the binary representation.
 * @return int Decimal equivalent of the binary number.
 */
int binaryToDecimal(int binary, int n) {
    int decimal = 0;
    int base = 1;
    int temp = binary;

    while (temp) {
        int lastDigit = temp % 10;
        temp = temp / 10;
        decimal += lastDigit * base;
        base = base * 2;
    }

    return decimal;
}

/**
 * @brief Solves the knapsack problem using a brute-force approach.
 * 
 * @param filePath Path to the input file containing knapsack problem details.
 * @param outputPath Path to the output file where the solution will be written.
 */
void bruteForceKnapsack(const std::string& filePath, const std::string& outputPath) {
    std::ifstream inputFile(filePath);
    std::ofstream outputFile(outputPath);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return;
    }

    // Read the number of items and knapsack capacity
    int n, W;
    inputFile >> n >> W;

    // Read item details
    std::vector<Item> items(n);
    for (int i = 0; i < n; ++i) {
        inputFile >> items[i].name >> items[i].profit >> items[i].weight;
    }

    inputFile.close();

    int maxProfit = 0;
    int selectedWeight = 0;
    int selectedItems = 0;
    int maxProfitBinary = 0;

    // Brute force approach: Try all possible combinations
    for (int i = 0; i < std::pow(2, n); ++i) {
        int currentProfit = 0;
        int currentWeight = 0;

        for (int j = 0; j < n; ++j) {
            if ((i & (1 << j)) != 0) {
                currentProfit += items[j].profit;
                currentWeight += items[j].weight;
            }
        }

        if (currentWeight <= W && currentProfit > maxProfit) {
            maxProfit = currentProfit;
            selectedWeight = currentWeight;
            selectedItems = i;
        }
    }

    // Write the solution to the output file
    outputFile << __builtin_popcount(selectedItems) << " " << maxProfit << " " << selectedWeight << "\n";

    for (int j = 0; j < n; ++j) {
        if ((selectedItems & (1 << j)) != 0) {
            outputFile << items[j].name << " " << items[j].profit << " " << items[j].weight << "\n";
        }
    }

    outputFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    const std::string inputFilePath = argv[1];
    const std::string outputFilePath = "output1.txt";

    bruteForceKnapsack(inputFilePath, outputFilePath);

    std::cout << "Solution written to " << outputFilePath << std::endl;

    return 0;
}


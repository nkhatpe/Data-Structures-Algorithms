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
#include <random>
#include <ctime>

// Custom data structure representing an item in the knapsack problem
struct Item {
    std::string name;  // Name or identifier of the item
    int profit;        // Profit or value associated with the item
    int weight;        // Weight of the item
};

// Function to generate a random knapsack problem and save it to a file
void createKnapsackProblem(const std::string& filePath) {
    std::ofstream outputFile(filePath);

    // Generate random values
    int n = std::rand() % 6 + 5;  // Random number of items between 5 and 10
    int W = 0;  // Total weight of the knapsack
    std::vector<Item> items;

    for (int i = 1; i <= n; ++i) {
        Item item;
        item.name = "item" + std::to_string(i);
        item.profit = std::rand() % 21 + 10;  // Random profit between 10 and 30
        item.weight = std::rand() % 16 + 5;   // Random weight between 5 and 20
        W += item.weight;
        items.push_back(item);
    }

    W = static_cast<int>(0.6 * W);  // Set the total weight of the knapsack to 60% of the total weight

    // Write to the file
    outputFile << n << " " << W << "\n";
    for (const auto& item : items) {
        outputFile << item.name << " " << item.profit << " " << item.weight << "\n";
    }

    outputFile.close();
}

int main() {
    // Seed for random values
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    createKnapsackProblem("knapsack01.txt");
    std::cout << "knapsack01.txt created." << std::endl;

    return 0;
}


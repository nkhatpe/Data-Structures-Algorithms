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
#include <algorithm>
#include <unordered_map>

using namespace std;

// Structure to represent an item in the knapsack problem
struct Item {
    string name;    // Name or identifier of the item
    int profit;     // Profit or value associated with the item
    int weight;     // Weight of the item
    double ratio;   // Profit-to-weight ratio
};

// Function to compare items based on their profit-to-weight ratio
bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

/**
 * @brief Solves the knapsack problem using an improved greedy algorithm.
 * 
 * @param filename Path to the input file containing knapsack problem details.
 * @param outputFilename Path to the output file where the solution will be written.
 */
void improvedGreedyKnapsack(const string& filename, const string& outputFilename) {
    ifstream file(filename);

    if (file.is_open()) {
        int n, capacity;
        file >> n >> capacity;

        vector<Item> items(n);

        // Read item details and calculate profit-to-weight ratio
        for (int i = 0; i < n; ++i) {
            file >> items[i].name >> items[i].profit >> items[i].weight;
            items[i].ratio = static_cast<double>(items[i].profit) / items[i].weight;
        }

        file.close();

        // Sort items in descending order based on profit-to-weight ratio
        sort(items.begin(), items.end(), compareItems);

        int currentWeightGreedy4 = 0;
        int totalProfitGreedy4 = 0;
        vector<Item> selectedItemsGreedy4;

        // Greedily select items
        for (const Item& item : items) {
            if (currentWeightGreedy4 + item.weight <= capacity) {
                selectedItemsGreedy4.push_back(item);
                currentWeightGreedy4 += item.weight;
                totalProfitGreedy4 += item.profit;
            }
        }

        // Calculate BGreedy4
        int BGreedy4 = totalProfitGreedy4;

        // Calculate maxB
        int maxB = 0;
        for (const Item& item : items) {
            maxB = max(maxB, item.profit);
        }

        // Calculate APP
        int APP = max(BGreedy4, maxB);

        // Write the final solution to output file
        ofstream outputFile(outputFilename);
        if (outputFile.is_open()) {
            outputFile << selectedItemsGreedy4.size() << " " << APP << " " << currentWeightGreedy4 << "\n";

            // Sort selected items by name before printing
            sort(selectedItemsGreedy4.begin(), selectedItemsGreedy4.end(), [](const Item& a, const Item& b) {
                return a.name < b.name;
            });

            for (const Item& item : selectedItemsGreedy4) {
                outputFile << item.name << " " << item.profit << " " << item.weight << "\n";
            }

            outputFile.close();
            cout << "Solution written to " << outputFilename << endl;
        } else {
            cout << "Unable to open output file";
        }
    }
}

int main() {
    const string inputFilePath = "knapsack01.txt";
    const string outputFilePath = "output3.txt";

    improvedGreedyKnapsack(inputFilePath, outputFilePath);

    return 0;
}


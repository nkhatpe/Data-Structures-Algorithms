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

using namespace std;


// Definition of a custom data structure representing an item in the knapsack problem
struct Item {
    string itemName;
    int itemProfit;
    int itemWeight;
};

// Function to refine the knapsack solution and write the entries to "entries2.txt"
void refineKnapsack(int itemCount, int knapsackCapacity, int *weights, int *profits) {
    // Dynamic programming table to store intermediate results
    vector<vector<int>> dp(itemCount + 1, vector<int>(knapsackCapacity + 1, 0));

    // Mark the necessary entries of the table dp for refinement
    dp[itemCount][knapsackCapacity] = 1;

    // Loop to calculate the necessary entries of the dp table
    for (int i = itemCount; i > 1; i--) {
        for (int w = knapsackCapacity; w >= 0; w--) {
            if (dp[i][w] == 1) {
                // If the current entry is marked, mark the next possible entries
                if (w - weights[i - 1] >= 0) {
                    dp[i - 1][w - weights[i - 1]] = 1;
                }
                dp[i - 1][w] = 1;
            }
        }
    }

    // Open the entries file to write the refined entries
    ofstream entriesFile("entries2.txt");
    if (!entriesFile.is_open()) {
        cerr << "Unable to open entries2.txt" << endl;
        exit(1);
    }

    // Loop to write the refined entries to the entries2.txt file
    for (int i = 1; i <= itemCount; i++) {
        entriesFile << "row" << i << "   ";
        for (int w = 0; w <= knapsackCapacity; w++) {
            // If the entry is marked, calculate its value and write it to the file
            if (dp[i][w] == 1) {
                if (weights[i - 1] <= w) {
                    dp[i][w] = max(profits[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
                entriesFile << dp[i][w] << " ";
            }
        }
        entriesFile << "\n";
    }

    entriesFile.close();  // Close the entries file

    // Calculate selected items for the final solution
    int i = itemCount, j = knapsackCapacity;
    vector<int> selectedItems;

    while (i > 0 && j > 0) {
        if (dp[i][j] != dp[i - 1][j]) {
            selectedItems.push_back(i);
            j -= weights[i - 1];
        }
        i -= 1;
    }

    // Write the final solution to output2.txt
    ofstream outputFile("output2.txt");
    if (!outputFile.is_open()) {
        cerr << "Unable to open output2.txt" << endl;
        exit(1);
    }

    // Reverse the order of selected items and write them to the output2.txt file
    reverse(selectedItems.begin(), selectedItems.end());
    outputFile << selectedItems.size() << " " << dp[itemCount][knapsackCapacity] << " " << knapsackCapacity - j << "\n";

    for (int item : selectedItems) {
        outputFile << "item" << item << " " << profits[item - 1] << " " << weights[item - 1] << "\n";
    }

    outputFile.close();  // Close the output file

    cout << "Entries written to entries2.txt" << endl;
    cout << "Solution written to output2.txt" << endl;
}

int main() {
    const string myInputFilePath = "knapsack01.txt";

    ifstream myFile(myInputFilePath);

    if (myFile.is_open()) {
        int itemCount, refineKnapsackCapacity;
        myFile >> itemCount >> refineKnapsackCapacity;

        int myProfits[itemCount], myWeights[itemCount];

        for (int i = 0; i < itemCount; ++i) {
            string itemName;
            myFile >> itemName >> myProfits[i] >> myWeights[i];
        }

        myFile.close();

        // Call the function to refine the knapsack solution and write entries
        refineKnapsack(itemCount, refineKnapsackCapacity, myWeights, myProfits);
    } else {
        cerr << "Unable to open file" << endl;
    }

    return 0;
}


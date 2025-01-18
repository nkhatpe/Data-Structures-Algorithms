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
#include <string>
#include <map>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

struct Card {
    string name;
    int market_price;
    int gertrude_price;
};

// Function to read market prices from a file
void readMarketPrices(const string& marketPriceFile, map<string, int>& marketPrices) {
    ifstream file(marketPriceFile);
    if (!file) {
        cerr << "Error: Unable to open market price file." << endl;
        exit(1);
    }

    int numCards;
    file >> numCards;

    for (int i = 0; i < numCards; ++i) {
        string cardName;
        int price;
        file >> cardName >> price;
        marketPrices[cardName] = price;
    }

    file.close();
}

// Function to compute maximum profit and selected cards
int computeMaxProfit(vector<Card>& priceList, int budget, vector<string>& selectedCards) {
    int numCards = priceList.size();
    int maxProfit = 0;
    vector<int> bestSelectedIndices;
    
    // iterating through all possible combinations of cards using a binary mask

    for (int mask = 0; mask < (1 << numCards); ++mask) {
        int currentBudget = 0;
        int currentProfit = 0;
        vector<int> selectedIndices;

        for (int i = 0; i < numCards; ++i) {
            if (mask & (1 << i)) {
                currentBudget += priceList[i].gertrude_price;
                currentProfit += priceList[i].market_price - priceList[i].gertrude_price;
                selectedIndices.push_back(i);
            }
        }

        if (currentBudget <= budget && currentProfit > maxProfit) {
            maxProfit = currentProfit;
            bestSelectedIndices = selectedIndices;
        }
    }

    selectedCards.clear();
    for (int index : bestSelectedIndices) {
        selectedCards.push_back(priceList[index].name);
    }

    return maxProfit;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <market-price-file> <price-list-file>" << endl;
        return 1;
    }

    map<string, int> marketPrices;
    readMarketPrices(argv[1], marketPrices);

    ifstream priceListFile(argv[2]);
    if (!priceListFile) {
        cerr << "Error: Unable to open price list file." << endl;
        return 1;
    }

    ofstream outputFile("output.txt"); // Open an output file

    while (!priceListFile.eof()) {
        int numCards, budget;
        priceListFile >> numCards >> budget;

        vector<Card> priceList(numCards);
        for (int i = 0; i < numCards; ++i) {
            priceListFile >> priceList[i].name >> priceList[i].gertrude_price;
            if (marketPrices.find(priceList[i].name) == marketPrices.end()) {
                cerr << "Error: Card '" << priceList[i].name << "' not found in market prices." << endl;
                return 1;
            }
            priceList[i].market_price = marketPrices[priceList[i].name];
        }

        vector<string> selectedCards;
        clock_t startTime = clock();
        int maxProfit = computeMaxProfit(priceList, budget, selectedCards);
        clock_t endTime = clock();
        double elapsedSeconds = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;

        // Redirect output to the output.txt file
        outputFile << numCards << " " << maxProfit << " " << selectedCards.size() << " " << fixed << setprecision(6) << elapsedSeconds << endl;
        for (const string& card : selectedCards) {
            outputFile << card << endl;
        }
    }

    priceListFile.close();
    outputFile.close(); // Close the output file
    return 0;
}


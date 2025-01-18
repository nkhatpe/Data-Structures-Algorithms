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
#include <string>
#include <vector>
using namespace std;

void lcs(string X, string Y) {
    int m = X.length();
    int n = Y.length();

    // Create and initialize the tables for dynamic programming
    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0)); // c[i][j] stores the length of LCS of X[0..i-1] and Y[0..j-1]
    vector<vector<string>> b(m + 1, vector<string>(n + 1, "")); // b[i][j] stores the direction of the optimal subproblem solution

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                // If characters match, extend the LCS
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = "D"; // Diagonal
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                // Choose the direction that maximizes the LCS length
                c[i][j] = c[i - 1][j];
                b[i][j] = "U"; // Up
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = "L"; // Left
            }
        }
    }

    // Construct the LCS from the tables
    int lcsLength = c[m][n];
    string lcsString;

    int i = m, j = n;

    while (i > 0 && j > 0) {
        if (b[i][j] == "D") {
            // Follow the diagonal direction and include the character
            lcsString = X[i - 1] + lcsString;
            i--;
            j--;
        } else if (b[i][j] == "U") {
            // Move upward
            i--;
        } else {
            // Move leftward
            j--;
        }
    }

    // Print the length of the LCS and the LCS itself
    cout << "Length of LCS: " << lcsLength << endl;
    cout << "LCS: " << lcsString << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: ./lcs <input-string1> <input-string2>" << endl;
        return 1;
    }

    string X = argv[1];
    string Y = argv[2];

    lcs(X, Y);

    return 0;
}


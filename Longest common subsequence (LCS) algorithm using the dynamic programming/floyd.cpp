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
#include <climits>
#include <sstream>

const int INF = INT_MAX;

// Function to perform the Floyd-Warshall algorithm
void floydWarshall(std::vector<std::vector<int>>& D, std::vector<std::vector<int>>& P) {
    int n = D.size();

    // Iterate through all vertices as intermediate nodes
    for (int k = 0; k < n; k++) {
        // Iterate through all pairs of vertices (i, j)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Update the distance and path if there is a shorter path through vertex k
                if (D[i][k] != INF && D[k][j] != INF && D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k + 1; // Update P matrix with intermediate vertex
                }
            }
        }
    }
    
}

int main() {
    // Open input file
    std::ifstream inputFile("graph.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file 'graph.txt'" << std::endl;
        return 1;
    }

    // Open output file
    std::ofstream outputFile("output.txt");

    int problemNumber = 1;
    std::string line;

    // Read input file line by line
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string token;
        std::string problemToken;

        // Parse problem information
        iss >> problemToken; // "Problem"
        int problem;
        iss >> problem; // X
        iss >> token; // ":"
        if (token != ":") continue;

        iss >> token; // "n"
        if (token != "n") continue;

        iss >> token; // "="
        if (token != "=") continue;

        int n;
        iss >> n; // Y

        if (n <= 0) break;

        // Initialize matrices for distance (D) and path (P)
        std::vector<std::vector<int>> D(n, std::vector<int>(n));
        std::vector<std::vector<int>> P(n, std::vector<int>(n, 0));

        // Read the graph's adjacency matrix from the input file
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                inputFile >> D[i][j];
            }
        }

        // Apply the Floyd-Warshall algorithm to find shortest paths
        floydWarshall(D, P);

        // Write results to the output file
        outputFile << "Problem " << problemNumber << ": n = " << n << "\n";
        outputFile << "P matrix:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                outputFile << P[i][j] << "\t";
            }
            outputFile << "\n";
        }
        outputFile << "\n";


            // Print shortest paths and lengths for each pair of vertices
       	    for (int i = 0; i < n; i++) {
	    outputFile << "V" << i + 1 << "-Vj: shortest path and length\n";
	    for (int j = 0; j < n; j++) {
		outputFile << "V" << i + 1 << " ";
		int k = P[i][j];
		while (k != 0) {
		    outputFile << "V" << k << " ";
		    k = P[k - 1][j];
		}
		outputFile << "V" << j + 1 << " : " << D[i][j] << "\n";
	    }
	    outputFile << "\n";
	}

        // Increment problem number for the next iteration
        problemNumber++;
    }

    // Close input and output files
    inputFile.close();
    outputFile.close();

    return 0;
}


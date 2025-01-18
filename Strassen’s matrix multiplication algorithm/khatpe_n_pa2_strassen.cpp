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
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cmath>

using namespace std;

// Function for standard matrix multiplication
vector<vector<int>> standardMatrixMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Function to add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Function to subtract two matrices
vector<vector<int>> subtractMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Function for Strassen's matrix multiplication
vector<vector<int>> strassenMatrixMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    // Base case: if the matrix size is 1x1, perform a simple multiplication
    if (n == 1) {
        vector<vector<int>> result(1, vector<int>(1));
        result[0][0] = A[0][0] * B[0][0];
        return result;
    }

    int half = n / 2;

    // Divide matrices A and B into submatrices
    vector<vector<int>> A11(half, vector<int>(half));
    vector<vector<int>> A12(half, vector<int>(half));
    vector<vector<int>> A21(half, vector<int>(half));
    vector<vector<int>> A22(half, vector<int>(half));

    vector<vector<int>> B11(half, vector<int>(half));
    vector<vector<int>> B12(half, vector<int>(half));
    vector<vector<int>> B21(half, vector<int>(half));
    vector<vector<int>> B22(half, vector<int>(half));



    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            // Split A and B into submatrices
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // Calculate 7 products using recursive calls
    vector<vector<int>> P1 = strassenMatrixMultiplication(A11, subtractMatrices(B12, B22));
    vector<vector<int>> P2 = strassenMatrixMultiplication(addMatrices(A11, A12), B22);
    vector<vector<int>> P3 = strassenMatrixMultiplication(addMatrices(A21, A22), B11);
    vector<vector<int>> P4 = strassenMatrixMultiplication(A22, subtractMatrices(B21, B11));
    vector<vector<int>> P5 = strassenMatrixMultiplication(addMatrices(A11, A22), addMatrices(B11, B22));
    vector<vector<int>> P6 = strassenMatrixMultiplication(subtractMatrices(A12, A22), addMatrices(B21, B22));
    vector<vector<int>> P7 = strassenMatrixMultiplication(subtractMatrices(A11, A21), addMatrices(B11, B12));

    // Calculate the result submatrices
    vector<vector<int>> C11 = subtractMatrices(addMatrices(addMatrices(P5, P4), P6), P2);
    vector<vector<int>> C12 = addMatrices(P1, P2);
    vector<vector<int>> C21 = addMatrices(P3, P4);
    vector<vector<int>> C22 = subtractMatrices(subtractMatrices(addMatrices(P5, P1), P3), P7);

    // Combine the submatrices to get the result matrix
    vector<vector<int>> result(n, vector<int>(n));

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            result[i][j] = C11[i][j];
            result[i][j + half] = C12[i][j];
            result[i + half][j] = C21[i][j];
            result[i + half][j + half] = C22[i][j];
        }
    }

    return result;
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " n" << endl;
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0 || (n & (n - 1)) != 0) {
        cout << "n should be a positive power of 2." << endl;
        return 1;
    }

    // Seed for random number generation
    srand(time(0));

    // Generate random matrices A and B
    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % (int(sqrt(INT_MAX) / n));
            B[i][j] = rand() % (int(sqrt(INT_MAX) / n));
        }
    }

    // Print matrices A and B
    cout << "Matrix A = " << endl;
    printMatrix(A);
    cout << "Matrix B = " << endl;
    printMatrix(B);

    // Perform standard matrix multiplication
    vector<vector<int>> standardResult = standardMatrixMultiplication(A, B);

    // Perform Strassen's matrix multiplication
    vector<vector<int>> strassenResult = strassenMatrixMultiplication(A, B);

    // Print the results
    cout << "The result of standard matrix multiplication A*B:" << endl;
    printMatrix(standardResult);

    cout << "The result of Strassen's matrix multiplication A*B:" << endl;
    printMatrix(strassenResult);

    // Check if the results match
    bool match = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (standardResult[i][j] != strassenResult[i][j]) {
                match = false;
                break;
        }
    }
}

    if (match) {
    cout << "Matrix multiplication results match!" << endl;
} else {
    cout << "Matrix multiplication results do not match." << endl;
}


    return 0;   
}


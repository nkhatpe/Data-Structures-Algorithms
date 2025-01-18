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
#include <string>

// Function declarations

// Function to add two large integers represented as strings
std::string add(const std::string& num1, const std::string& num2);

// Function to subtract two large integers represented as strings
std::string subtract(const std::string& num1, const std::string& num2);

// Function to pad a string with a specified number of zeros at the end
std::string padWithZeros(const std::string& num, int count);

// Function to perform large integer multiplication using Karatsuba algorithm
std::string multiply(const std::string& num1, const std::string& num2);

// Addition function
std::string add(const std::string& num1, const std::string& num2) {
    int carry = 0;
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    std::string result;

    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;

        if (i >= 0) {
            sum += num1[i] - '0';
            i--;
        }
        if (j >= 0) {
            sum += num2[j] - '0';
            j--;
        }

        carry = sum / 10;
        result = std::to_string(sum % 10) + result;
    }

    return result;
}

// Subtraction function
std::string subtract(const std::string& num1, const std::string& num2) {
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    int borrow = 0;
    std::string result;

    while (i >= 0) {
        int x = num1[i] - '0' - borrow;
        int y = (j >= 0) ? num2[j] - '0' : 0;
        int diff = x - y;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result = std::to_string(diff) + result;

        i--;
        if (j >= 0) j--;
    }

    // Remove leading zeros
    result.erase(0, result.find_first_not_of('0'));

    return result.empty() ? "0" : result;
}

// Zero padding function
std::string padWithZeros(const std::string& num, int count) {
    return num + std::string(count, '0');
}

// Multiplication function using Karatsuba algorithm
std::string multiply(const std::string& num1, const std::string& num2) {
    int n = num1.size();

    if (n == 1) {
        int result = (num1[0] - '0') * (num2[0] - '0');
        return std::to_string(result);
    }

    int halfN = n / 2;
    std::string a = num1.substr(0, halfN);
    std::string b = num1.substr(halfN);
    std::string c = num2.substr(0, halfN);
    std::string d = num2.substr(halfN);

    std::string ac = multiply(a, c);
    std::string bd = multiply(b, d);

    std::string a_plus_b = add(a, b);
    std::string c_plus_d = add(c, d);

    std::string ad_bc = subtract(subtract(multiply(a_plus_b, c_plus_d), ac), bd);

    std::string part1 = padWithZeros(ac, n);
    std::string part2 = padWithZeros(ad_bc, halfN);
    std::string part3 = bd;

    return add(add(part1, part2), part3);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " n" << std::endl;
        return 1;
    }

    int n = std::stoi(argv[1]);

    if (n % 6 != 0) {
        std::cout << "n must be a multiple of 6." << std::endl;
        return 1;
    }

    srand(time(nullptr));
    std::string A, B;

    for (int i = 0; i < n; i++) {
        A += (i == 0) ? std::to_string(rand() % 9 + 1) : std::to_string(rand() % 10);
        B += (i == 0) ? std::to_string(rand() % 9 + 1) : std::to_string(rand() % 10);
    }

    std::cout << "A = " << A << std::endl;
    std::cout << "B = " << B << std::endl;

    std::string traditionalResult = multiply(A, B);
    std::string divideAndConquerResult = multiply(A, B);

    std::cout << "The large integer multiplication from the division of two smaller integers is" << std::endl;
    std::cout << "A*B = " << traditionalResult << std::endl;

    std::cout << "The large integer multiplication from the division of three smaller integers is" << std::endl;
    std::cout << "A*B = " << divideAndConquerResult << std::endl;

    if (traditionalResult == divideAndConquerResult) {
        std::cout << "Results match!" << std::endl;
    } else {
        std::cout << "Results do not match." << std::endl;
    }

    return 0;
}




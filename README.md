# Algorithm Implementations

A collection of classic algorithm implementations including brute force approaches, dynamic programming solutions, and matrix operations. Each implementation includes analysis of time complexity and algorithmic approach.

## Implementations

### 1. Brute Force Algorithm
- Implementation of exhaustive search approach
- Applications:
  - String matching
  - Pattern finding
  - Combinatorial problems
- Time Complexity Analysis
- Time Complexity: O(n!) for permutation problems
- Space Complexity: O(n) for recursion depth
- Test cases demonstrating various scenarios

### 2. Knapsack Problem
Different approaches to solving the 0/1 Knapsack problem:
- Dynamic Programming Solution
  - Time Complexity: O(nW)
  - Space Complexity: O(nW)
- Approximation Algorithms
  - Greedy Approach O(n log n) time for sorting
  - FPTAS O(n/ε) time where ε is the approximation factor (Fully Polynomial Time Approximation Scheme)
- Performance comparison between approaches

### 3. Longest Common Subsequence (LCS)
Dynamic Programming implementation of LCS:
- Matrix-based solution
- Backtracking for sequence reconstruction
- Time Complexity: O(mn)
- Space Complexity: O(mn)
- Example cases with visualizations

### 4. Strassen's Matrix Multiplication
- Implementation of Strassen's algorithm for matrix multiplication
- Comparison with conventional matrix multiplication
- Time Complexity: O(n^2.807)
- Optimizations and threshold implementations
- Performance analysis with varying matrix sizes
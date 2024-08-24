#include <iostream>
using namespace std;

#define alphaR 5 // m
#define alphaC 5 // n
#define betaR 5 // m
#define betaC 3 // n

template <size_t rows, size_t cols>
void printMatrix(int(&matrix)[rows][cols]);

int main() {
    int alpha[alphaR][alphaC] = {
        {1, 0, 0, 1, 0},
        {7, 0, 4, 0, 0},
        {0, 2, 0, 0, 9},
        {0, 0, 6, 6, 0},
        {9, 0, 5, 0, 9}
    };
    int beta[betaR][betaC] = {
        {10, 20, 3},
        {19, 10, 2},
        {10, 3, 19},
        {12, 0, 16},
        {19, 16, 0}
    };

    if (alphaC != betaR) {
        cout << "The first matrix must have the same number of columns as the second matrix has rows for multiplication.";
    }
    else {
        int result[alphaR][betaC] = { 0 };
        for (int i = 0; i < alphaR; i++) {
            for (int j = 0; j < betaC; j++) {
                for (int k = 0; k < betaR; k++) {
                    result[i][j] += alpha[i][k] * beta[k][j];
                }
            }
        }
        cout << "--- Alpha ---" << endl;
        printMatrix(alpha);
        cout << "--- Beta ---" << endl;
        printMatrix(beta);
        cout << "--- Result ---" << endl;
        printMatrix(result);
    }

}

template <size_t rows, size_t cols>
void printMatrix(int(&matrix)[rows][cols]) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}
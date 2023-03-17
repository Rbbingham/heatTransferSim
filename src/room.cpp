#include "room.h"

#include <cstdio>
#include <climits>

Room::Room (const int& numRows, const int& numCols, const double& baseTemp) : nRows(numRows + 2), nCols(numCols + 2) {
    matrix = std::make_unique<std::unique_ptr<double[]>[]> (numRows + 2);

    for (int i = 0; i < numRows + 2; ++i) {
        matrix[i] = std::make_unique<double[]> (numCols + 2);
    }

    for (int i = 0; i < numRows + 2; ++i) {
        if (i == 0 || i == numRows + 1) {
            for (int j = 0; j < numCols + 2; ++j) {
                matrix[i][j] = 0;
            }

            continue;
        }

        for (int j = 0; j < numCols + 2; ++j) {
            if (j == 0 || j == numCols + 1) {
                matrix[i][j] = 0;
                continue;
            }

            matrix[i][j] = baseTemp;
        }
    }
}

Room::~Room () = default;

inline void Room::setTemp (const int &row, const int &col, const double &temp) {
    matrix[row + 1][col + 1] = temp;
}

void Room::print () {
    for (int i = 1; i < nRows - 1; ++i) {
        printf("[ ");

        for (int j = 1; j < nCols - 1; ++j) {
            printf("%.2f, ", matrix[i][j]);
        }

        printf(" ]\n");
    }
}
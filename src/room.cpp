#include "room.h"

#include <cstdio>
#include <stdexcept>

Room::Room (const int& numRows, const int& numCols, const double& baseTemp) : nRows(numRows + 2), nCols(numCols + 2) {
    matrix = std::make_unique<std::unique_ptr<double[]>[]> (numRows + 2);

    for (int i = 0; i < numRows + 2; ++i) {
        matrix[i] = std::make_unique<double[]> (numCols + 2);
    }

    for (int i = 0; i < numRows + 2; ++i) {
        for (int j = 0; j < numCols + 2; ++j) {
            matrix[i][j] = baseTemp;
        }
    }
}

Room::Room(const Room& right) : nRows(right.nRows), nCols(right.nCols) {
    this->matrix = std::make_unique<std::unique_ptr<double[]>[]> (right.nRows);

    for (int i = 0; i < right.nRows; ++i) {
        this->matrix[i] = std::make_unique<double[]> (right.nCols);
    }

    for (int i = 0; i < right.nRows; ++i) {
        for (int j = 0; j < right.nCols; ++j) {
            this->matrix[i][j] = right.matrix[i][j];
        }
    }
}

Room::~Room () = default;

void Room::setHeat(std::vector<std::tuple<int, int, double>> heaters) {
    for (auto i : heaters) {
        matrix[std::get<0>(i) + 1][std::get<1>(i) + 1] = std::get<2>(i);
    }
}

void Room::calculateTemp(Room& old, int row, int col, const double &k) {
    double factor = old.matrix[row - 1][col] + old.matrix[row + 1][col] + old.matrix[row][col - 1] + old.matrix[row][col + 1] +
            old.matrix[row - 1][col - 1] + old.matrix[row - 1][col + 1] + old.matrix[row + 1][col - 1] + old.matrix[row + 1][col + 1];

    this->matrix[row][col] = (old.matrix[row][col] + (k * factor) / 8.0) / 2.0;
}

void Room::print () {
    if (nRows > 15 || nCols > 15) {
        printf("(Matrix dimensions to large to show)\n");
        return;
    }

    for (int i = 1; i < nRows - 1; ++i) {
        printf("[ ");

        for (int j = 1; j < nCols - 1; ++j) {
            if (j == nCols - 2) {
                printf("%.4f", matrix[i][j]);
                break;
            }

            printf("%.4f, ", matrix[i][j]);
        }

        printf(" ]\n");
    }
}

Room& Room::operator=(const Room& right){
    if (&right == this) {
        return *this;
    }
    else if ((this->nRows != right.nRows) || (this->nCols != right.nCols)) {
        throw std::length_error("Matrix dimensions don't match.");
    }

    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            this->matrix[i][j] = right.matrix[i][j];
        }
    }

    return *this;
};
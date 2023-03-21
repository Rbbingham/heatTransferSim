#include "room.h"

#include <cstdio>
#include <stdexcept>

Room::Room () : matrix(nullptr), nRows(0), nCols(0) {}

// constructor: initializes matrix of size numRows x numCols with value baseTemp
Room::Room (const int& numRows, const int& numCols, const float& baseTemp) : nRows(numRows + 2), nCols(numCols + 2) {
    // create array of pointers
    this->matrix = std::make_unique<std::unique_ptr<float[]>[]> (numRows + 2);

    for (int i = 0; i < numRows + 2; ++i) {
        // create pointers that point to array of doubles
        matrix[i] = std::make_unique<float[]> (numCols + 2);
    }

    // set each value to baseTemp
    for (int i = 0; i < numRows + 2; ++i) {
        for (int j = 0; j < numCols + 2; ++j) {
            matrix[i][j] = baseTemp;
        }
    }
}

// copy constructor: initialize new matrix with the same values as right matrix
Room::Room(const Room& right) : nRows(right.nRows), nCols(right.nCols) {
    // create array of pointers
    this->matrix = std::make_unique<std::unique_ptr<float[]>[]> (right.nRows);

    for (int i = 0; i < right.nRows; ++i) {
        // create pointers that point to array of doubles
        this->matrix[i] = std::make_unique<float[]> (right.nCols);
    }

    // set new matrix values to that of right matrix
    for (int i = 0; i < right.nRows; ++i) {
        for (int j = 0; j < right.nCols; ++j) {
            this->matrix[i][j] = right.matrix[i][j];
        }
    }
}

// default for unique pointers
Room::~Room () = default;

// sets the heaters
void Room::setHeat(std::vector<std::tuple<int, int, float>>& heaters) {
    for (auto i : heaters) {
        matrix[std::get<0>(i) + 1][std::get<1>(i) + 1] = std::get<2>(i);
    }
}

// calculate the temp of cell[row][col] based on old matrix and k value
void Room::calculateTemp(Room& old, int row, int col, const float &k) {
    float factor = old.matrix[row - 1][col] + old.matrix[row + 1][col] + old.matrix[row][col - 1] + old.matrix[row][col + 1] +
            old.matrix[row - 1][col - 1] + old.matrix[row - 1][col + 1] + old.matrix[row + 1][col - 1] + old.matrix[row + 1][col + 1];

    this->matrix[row][col] = (old.matrix[row][col] + (k * factor) * (float) 0.125) * (float) 0.5;
}

// prints the values of the matrix as long as its dimensions are acceptable
void Room::print () {
    if (nRows > 20 || nCols > 20) {
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

// assignment operator: takes left matrix and right matrix and sets left matrix's values equal to right matrix's values
Room& Room::operator=(const Room& right){
    // if the same matrix return or if different dimensions throw error
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

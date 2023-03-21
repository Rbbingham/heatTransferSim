#include "room.h"

#include <gtest/gtest.h>
#include <cmath>

#define EPSILON 0.0001

double heaterPOS[10][10] = {
            {30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
            {30, 60, 30, 30, 30, 30, 30, 30, 30, 30},
            {30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
            {30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
            {30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
            {30, 30, 30, 30, 30, 60, 30, 30, 30, 30},
            {30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
            {30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
            {30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
            {30, 30, 30, 30, 30, 30, 30, 30, 30, 10},
};

double firstIter[10][10] = {
            {31.875, 31.875, 31.875, 30, 30, 30, 30, 30, 30, 30},
            {31.875, 60, 31.875, 30, 30, 30, 30, 30, 30, 30},
            {31.875, 31.875, 31.875, 30, 30, 30, 30, 30, 30, 30},
            {30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
            {30, 30, 30, 30, 31.875, 31.875, 31.875, 30, 30, 30},
            {30, 30, 30, 30, 31.875, 60, 31.875, 30, 30, 30},
            {30, 30, 30, 30, 31.875, 31.875, 31.875, 30, 30, 30},
            {30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
            {30, 30, 30, 30, 30, 30, 30, 30, 28.75, 28.75},
            {30, 30, 30, 30, 30, 30, 30, 30, 28.75, 10},
};

std::vector<std::tuple<int, int, float>> heaters = {
    std::make_tuple(1, 1, 60.0),
    std::make_tuple(5, 5, 60.0),
    std::make_tuple(9, 9, 10.0)
};

TEST (BasicTests, CopyCon) {
    Room firstMatrix(10, 10, 30);
    Room copyMatrix(firstMatrix);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            EXPECT_EQ(firstMatrix.getTemp(i, j), copyMatrix.getTemp(i, j));
        }
    }
}

TEST (BasicTests, SetHeaters) {
    Room testMatrix(10, 10, 30);
    testMatrix.setHeat(heaters);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            EXPECT_EQ(heaterPOS[i][j], testMatrix.getTemp(i, j));
        }
    }
}

TEST (BasicTests, CalculateTemp) {
    int k = 1;
    Room testMatrix(10, 10, 30);
    testMatrix.setHeat(heaters);
    Room oldMatrix(testMatrix);

    for (int i = 1; i < 11; ++i) {
        for (int j = 1; j < 11; ++j) {
            testMatrix.calculateTemp(oldMatrix, i, j, k);
        }
    }

    testMatrix.setHeat(heaters);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            EXPECT_LT(fabs(firstIter[i][j] - testMatrix.getTemp(i, j)), EPSILON);
        }
    }
}

TEST (BasicTests, Assignment) {
    Room firstMatrix(10, 10, 30);
    firstMatrix.setHeat(heaters);
    Room assignment = firstMatrix;

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            EXPECT_EQ(firstMatrix.getTemp(i, j), assignment.getTemp(i, j));
        }
    }
}
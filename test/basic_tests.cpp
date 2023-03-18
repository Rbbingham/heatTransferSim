#include "room.h"

#include <gtest/gtest.h>
#include <cmath>

TEST(BasicTests, Input) {
    std::vector<std::tuple<int, int, double>> heaters;
    heaters.emplace_back(std::make_tuple(1, 1, 60.0));
    heaters.emplace_back(std::make_tuple(5, 5, 60.0));
    heaters.emplace_back(std::make_tuple(9, 9, 10.0));

    int k = 1;
    const double EPSILON = 0.0001;
    Room testMatrix(10, 10, 30);
    testMatrix.setHeat(heaters);
    Room oldMatrix(testMatrix);

    double example[10][10] = {
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

    for (int i = 1; i < 11; ++i) {
        for (int j = 1; j < 11; ++j) {
            testMatrix.calculateTemp(oldMatrix, i, j, k);
        }
    }

    testMatrix.setHeat(heaters);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            EXPECT_LT(fabs(example[i][j] - testMatrix.getTemp(i, j)), EPSILON);
        }
    }
}
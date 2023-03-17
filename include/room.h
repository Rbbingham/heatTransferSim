#pragma once

#include <memory>

class Room {
private:
    std::unique_ptr<std::unique_ptr<double[]>[]> matrix;
    const int nRows;
    const int nCols;

public:
    Room (const int& numRows, const int& numCols, const double& baseTemp);
    ~Room ();

    inline void setTemp (const int& row, const int& col, const double& temp);
    void print ();
};
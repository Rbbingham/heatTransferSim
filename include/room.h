#pragma once

#include <memory>
#include <tuple>
#include <vector>

class Room {
private:
    std::unique_ptr<std::unique_ptr<double[]>[]> matrix;
    int nRows;
    int nCols;

public:
    Room (const int& numRows, const int& numCols, const double& baseTemp);
    Room (const Room& right);
    ~Room ();

    inline int getRows () const { return nRows; }
    inline int getCols () const { return nCols; }
    inline double getTemp (int i, int j) const { return matrix[i + 1][j + 1]; }
    void setHeat (std::vector<std::tuple<int, int, double>> heaters);
    void calculateTemp (Room& old, int row, int col, const double& k);
    void print ();

    Room& operator=(const Room& right);
};
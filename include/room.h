#pragma once

#include <memory>
#include <tuple>
#include <vector>

class Room {
private:
    std::unique_ptr<std::unique_ptr<float[]>[]> matrix;
    int nRows;
    int nCols;

public:
    Room (const int& numRows, const int& numCols, const float& baseTemp); // constructor
    Room (const Room& right); // copy constructor
    ~Room ();

    inline int getRows () const { return nRows; }
    inline int getCols () const { return nCols; }
    inline float getTemp (int i, int j) const { return matrix[i + 1][j + 1]; }
    void setHeat (const std::vector<std::tuple<int, int, float>>& heaters);
    void calculateTemp (Room& old, int row, int col, const float& k);
    void print ();

    Room& operator=(const Room& right); // assignment operator overload
};
#pragma once

#include <memory>
#include <tuple>
#include <vector>

class Room {
private:
    std::unique_ptr<std::unique_ptr<float[]>[]> matrix = nullptr;
    int nRows = 0;
    int nCols = 0;

public:
    Room() = default;
    Room (const int& numRows, const int& numCols, const float& baseTemp); // constructor
    Room (const Room&); // copy constructor
    Room (Room&&) = default;
    ~Room () = default;

    inline int getRows () const { return nRows; }
    inline int getCols () const { return nCols; }
    inline float getTemp (int i, int j) const { return matrix[i + 1][j + 1]; }
    void setHeat (std::vector<std::tuple<int, int, float>>& heaters);
    void calculateTemp (Room& old, int row, int col, const float& k);
    void inline swap (Room& right) { this->matrix.swap(right.matrix); };
    void print ();

    Room& operator= (const Room& right) = delete; // assignment operator overload
    Room& operator= (Room&&) = default;
};

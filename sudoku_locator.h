#include "matrix_locator.h"

class SudokuLocator : public MatrixLocator {
public:
    SudokuLocator(size_t rows, size_t cols) : MatrixLocator(rows, cols) {}

public:
    int *locate(const int *data, size_t row, size_t col) const override {
        if (data == nullptr) {
            return nullptr;
        }
        if (row >= rows || col >= cols) {
            throw std::out_of_range("index out of range");
        }
        return (int *) data + row * cols + col;
    }
};
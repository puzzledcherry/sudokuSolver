/*
 * DO NOT TOUCH THIS FILE
 */

class MatrixLocator {
protected:
    size_t rows, cols;
public:
    MatrixLocator(size_t rows, size_t cols) : rows(rows), cols(cols) {}

    virtual int *locate(const int *data, size_t row, size_t col) const = 0;

private:
    MatrixLocator() = default;
};
#include <iostream>
#include <stdexcept>
#include <cstring>
#include "sudoku_locator.h"

#define SUDOKU_BOARD_SIZE 9

class Sudoku {
private:
    // challenge[row][col], row major
    int *challenge;

    MatrixLocator &locator;

    int *challenge_board(size_t row, size_t col) const {
        return locator.locate(challenge, row, col);
    }

    bool solveHelper(size_t row, size_t col); // use this or add your own below as a private member function

public:
    void set_board_val(int row, int col, int val) const {
        if (row > 8 || col > 8) {
            throw std::out_of_range("index out of range");
        }
        *challenge_board(row, col) = val;
    }

    virtual ~Sudoku();

    explicit Sudoku(int *data, MatrixLocator &locator) : locator(locator) {
        challenge = new int[SUDOKU_BOARD_SIZE * SUDOKU_BOARD_SIZE];
        for (int row = 0; row < SUDOKU_BOARD_SIZE; row++) {
            for (int col = 0; col < SUDOKU_BOARD_SIZE; col++) {
                *challenge_board(row, col) = *locator.locate(data, row, col);
            }
        }
    }

    bool operator==(const int *other_sudoku) const {
        for (int row = 0; row < SUDOKU_BOARD_SIZE; row++) {
            for (int col = 0; col < SUDOKU_BOARD_SIZE; col++) {
                if (*challenge_board(row, col) != *locator.locate(other_sudoku, row, col)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator==(const Sudoku &other_sudoku) const {
        for (int row = 0; row < SUDOKU_BOARD_SIZE; row++) {
            for (int col = 0; col < SUDOKU_BOARD_SIZE; col++) {
                if (*challenge_board(row, col) != *other_sudoku.challenge_board(row, col)) {
                    return false;
                }
            }
        }
        return true;
    }

    void print() const {
        for (int row = 0; row < SUDOKU_BOARD_SIZE; row++) {
            for (int col = 0; col < SUDOKU_BOARD_SIZE; col++) {
                printf(" [%d] ", *challenge_board(row, col));
                if (col == 8) {
                    printf("\n");
                }
            }
        }
        printf("\n");
    }

    bool solve();

    int &operator()(size_t row, size_t col) {
        if (row >= SUDOKU_BOARD_SIZE || col >= SUDOKU_BOARD_SIZE) {
            throw std::out_of_range("index out of range");

        }
        return *(challenge_board(row, col));
    }

    int operator()(size_t row, size_t col) const {
        if (row >= SUDOKU_BOARD_SIZE || col >= SUDOKU_BOARD_SIZE) {
            throw std::out_of_range("index out of range");

        }
        return *(challenge_board(row, col));
    }
};
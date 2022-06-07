#include <set>
#include "sudoku.h"

Sudoku::~Sudoku() {
    delete[] challenge;
}

bool Sudoku::solve() {
    //calling the helper function
    return (solveHelper(0, 0));
}

bool Sudoku::solveHelper (size_t row, size_t col) {
    //base case, need to check there are no more empty spaces
    if ((row >= 8) && (col > 8))
    {
        return true;
    }

    //check if we reach the end of a row
    if (col > 8)
    {
        row++;
        col = 0;
    }

    //check if spot we at is filled or not
    //if filled do a recursive call one to the right
    if (*challenge_board(row, col) > 0)
    {
        return solveHelper(row, (col + 1));
    }

    //decide what numbers can be placed in the spot
    std::set<int> possibilities;
    for (int i = 0; i < SUDOKU_BOARD_SIZE; i++)
    {
        possibilities.insert(i + 1);
    }

    //check across row for what numbers to remove from set
    //check across the column for what numbers to remove from set
    for (int i = 0; i < SUDOKU_BOARD_SIZE; i++)
    {
        int currRow = *challenge_board(row, i);
        if (currRow > 0)
        {
            possibilities.erase(currRow);
        }

        int currCol = *challenge_board(i, col);
        if (currCol > 0)
        {
            possibilities.erase(currCol);
        }
    }

    //check in the 3x3 for what numbers to remove from set
    size_t squareRow = (row / 3) * 3;
    size_t squareCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int currNum = *challenge_board(squareRow + i, squareCol + j);
            if (currNum > 0)
            {
                possibilities.erase(currNum);
            }
        }
    }

    //iterate through all possibilities
    std::set<int>::iterator point = possibilities.begin();
    while (point != possibilities.end())
    {
        //test out one of the safe numbers
        *challenge_board(row, col) = *point;

        //see if it works with the rest of the numbers
        if (solveHelper(row, col + 1))
        {
            return true;
        }

        //it didn't work try again
        *challenge_board(row, col) = 0;
        point++;
    }

    //none of the safe ones worked??
    return false;
}

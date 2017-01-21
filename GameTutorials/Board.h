#pragma once

#include <vector>
#include <string>


const int TIE_VAL = -1;
// Indexes for board values
const int NO_VAL = 0;
const int X_VAL = 1;
const int O_VAL = 2;

// NOTE: The const after a function name makes a const function,
// indicating that the function won't change anything in the class.
// Const functions CAN NOT call non-const functions of the same class.

// Game board class
class Board {
public:
   
    // Initializes the board
    void init(int size);
    // Clears the board
    void clear();
    // Prints the board to standard output
    void print() const;

    // If no player won, returns NO_VAL. Otherwise returns X_VAL, O_VAL or TIE_VAL
    int checkVictory() const;

    // Sets value at x,y spot
    void setVal(int x, int y, int val) {
        _board[y * _size + x] = val;
    }

    // Gets value at x,y spot
    int getVal(int x, int y) const {
        return _board[y * _size + x];
    }

    // Getters
    int getSize() const { return _size; }

private:
    // Adds a horizontal line to string for printing
    void addHorizontalLine(std::string& s) const;
    // Adds a horizontal axis guide line to string for printing
    void addGuide(std::string& s) const;

    std::vector<int> _board;
    int _size;
};


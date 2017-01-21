#include "Board.h"

#include <string>

// Arrays of chars for printing out the board all fancy-like
const char GLYPHS[3][3][3] = {
    {
        { ' ', ' ', ' ' },
        { ' ', ' ', ' ' },
        { ' ', ' ', ' ' }
    },
    {
        { '#', ' ', '#' },
        { ' ', '#', ' ' },
        { '#', ' ', '#' }
    },
    {
        { '#', '#', '#' },
        { '#', ' ', '#' },
        { '#', '#', '#' }
    }
};


void Board::init(int size) {
    // Just cap it at 9 since we have limited console space
    if (size > 9) size = 9;
    _size = size;
    // Set the board size
    _board.resize(size * size);
    // Clear it
    clear();
}

void Board::clear() {
    for (size_t i = 0; i < _board.size(); i++) {
        _board[i] = NO_VAL;
    }
}

void Board::print() const {
    // Instead of calling printf multiple times, we build a single
    // string and call printf once, since its faster.

    std::string text = "";
    // Just reserve a bunch of memory, this should be enough
    text.reserve(_size * _size * 4);

    // Make top guide
    addGuide(text);

    // Loop through columns
    for (int y = 0; y < _size; y++) {
        // Add line
        addHorizontalLine(text);
        // Loop through glyph y
        for (int gy = 0; gy < 3; gy++) {
            // Add number or space
            if (gy == 1) {
                text += std::to_string(_size - y);
            } else {
                text += " ";
            }
            // Loop through row cells
            for (int x = 0; x < _size; x++) {
                // Loop through glyph x
                text += "|";
                for (int gx = 0; gx < 3; gx++) {
                    text += GLYPHS[getVal(x, _size - y - 1)][gy][gx];
                }
            }
            text += "|";
            // Add number or newline
            if (gy == 1) {
                text += std::to_string(_size - y) + "\n";
            } else {
                text += "\n";
            }
        }
    }
    // Add bottom line
    addHorizontalLine(text);\
    // Make bottom guide
    addGuide(text);

    // printf is faster than cout
    
    // Print the string
    printf("%s\n", text.c_str());
}

int Board::checkVictory() const {
    bool victory;
    int c;
    // Check the rows
    for (int y = 0; y < _size; y++) {
        c = getVal(0, y);
        if (c != NO_VAL) {
            victory = true;
            for (int x = 0; x < _size; x++) {
                if (getVal(x, y) != c) {
                    victory = false;
                    break;
                }
            }
            if (victory) return c;
        }
    }

    // Check the columns
    for (int x = 0; x < _size; x++) {
        c = getVal(x, 0);
        if (c != NO_VAL) {
            victory = true;
            for (int y = 0; y < _size; y++) {
                if (getVal(x, y) != c) {
                    victory = false;
                    break;
                }
            }
            if (victory) return c;
        }
    }

    // Check top left diagonal
    c = getVal(0, 0);
    if (c != NO_VAL) {
        victory = true;
        for (int xy = 0; xy < _size; xy++) {
            if (getVal(xy, xy) != c) {
                victory = false;
                break;
            }
        }
        if (victory) return c;
    }

    // Check top right diagonal
    c = getVal(_size - 1, 0);
    if (c != NO_VAL) {
        victory = true;
        for (int xy = 0; xy < _size; xy++) {
            if (getVal(_size - xy - 1, xy) != c) {
                victory = false;
                break;
            }
        }
        if (victory) return c;
    }

    // Check for tie game
    for (size_t i = 0; i < _board.size(); i++) {
        if (_board[i] == NO_VAL) return NO_VAL;
    }
    // If we get here, every spot was filled, so return tie
    return TIE_VAL;
}

void Board::addHorizontalLine(std::string& s) const {
    s += "-";
    for (int x = 0; x < _size; x++) {
        s += "----";
    }
    s += "--\n";
}

void Board::addGuide(std::string& s) const {
    s += " ";
    for (int i = 1; i <= _size; i++) {
        s += "| " + std::to_string(i) + " ";
    }
    s += "|\n";
}

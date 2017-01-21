#include "MainGame.h"
#include <iostream>

void MainGame::run() {
    init();
    // Game loop
    while (_gameState != GameState::EXIT) {
        // Print out the board
        _board.print();
        // Say which player is playing
        if (_currentPlayer == X_VAL) {
            printf("  Player X's turn!\n\n");
        } else {
            printf("  Player O's turn!\n\n");
        }
        // Perform a move
        if (!_isMultiplayer && _currentPlayer == _aiPlayer) {
            aiMove();
        } else {
            playerMove();
        }
        // Check victory condition
        int rv = _board.checkVictory();
        if (rv != NO_VAL) {
            endGame(rv == TIE_VAL);
        } else {
            changePlayer();
            // printf is faster than cout
            // Add a bunch of blank space to "clear" the command prompt
            for (int i = 0; i < 3; i++) {
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            }
        }
    }
}

void MainGame::init() {
    _gameState = GameState::PLAYING;
    _board.init(3);
    _currentPlayer = X_VAL;
   
    printf("\n\n****** Welcome to Tic-Tac-Toe ******\n\n");

    // Check for multiplayer
    printf("\nMultiplayer? (y/n):");
    char input = ' ';
    bool isValid;
    do {
        isValid = true;
        if (!(std::cin >> input)) {
            std::cout << "Invalid input!";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            isValid = false;
        } else if (input == 'y' || input == 'Y') {
            _isMultiplayer = true;
        } else {
            _isMultiplayer = false;
        }
    } while (isValid == false);
    
    if (!_isMultiplayer) {
        // Get player
        printf("\nWould you like to be X or O:");
        do {
            isValid = true;
            if (!(std::cin >> input)) {
                std::cout << "Invalid input!";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                isValid = false;
            } else if (input == 'x' || input == 'X') {
                _aiPlayer = O_VAL;
            } else if (input == 'o' || input == 'O') {
                _aiPlayer = X_VAL;
            } else {
                std::cout << "Must enter X or O!";
                isValid = false;
            }
        } while (isValid == false);
        // Init the AI player
        _ai.init(_aiPlayer);
    } 
    printf("\n\n");
}

void MainGame::playerMove() {
    // Get input
    bool wasValid = false;

    int x, y;
    do {
        printf("Enter the X: ");
        while (!(std::cin >> x)) {
            std::cin.clear(); 
            std::cin.ignore(1000, '\n'); 
            printf("ERROR: Invalid input!");
        }
        printf("Enter the Y: ");
        while (!(std::cin >> y)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            printf("ERROR: Invalid input!");
        }

        if (x < 1 || y < 1 || x > _board.getSize() || y > _board.getSize()) {
            printf("ERROR: Invalid X or Y!\n");
        } else if (_board.getVal(x - 1, y - 1) != 0) {
            printf("ERROR: That spot is taken!\n");
        } else {
            wasValid = true;
        }

    } while (!wasValid);

    // Now place the token
    _board.setVal(x - 1, y - 1, _currentPlayer);
}

void MainGame::aiMove() {
    // TODO: Implement this
    _ai.performMove(_board);
}

void MainGame::changePlayer() {
    if (_currentPlayer == X_VAL) {
        _currentPlayer = O_VAL;
    } else {
        _currentPlayer = X_VAL;
    }
}

void MainGame::endGame(bool wasTie) {

    _board.print();

    if (wasTie) {
        printf("\n\n Tie game! Enter any key to play again, or Z to exit: ");
    } else {
        if (_currentPlayer == X_VAL) {
            printf("\n\n  Player X wins! Enter any key to play again, or Z to exit: ");
        } else {
            printf("\n\n  Player O wins! Enter any key to play again, or Z to exit: ");
        }
    }

    char input;
    std::cin >> input;
    if (input == 'Z' || input == 'z') {
        _gameState = GameState::EXIT;
    } else {
        // Re init the game
        init();
    }
}

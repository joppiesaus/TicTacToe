#pragma once

#include "AI.h"
#include "Board.h"

enum class GameState { PLAYING, EXIT };

class MainGame {
public:
    // Runs the main loop
    void run();

private:
    // Initializes the game
    void init();
    // Performs a human controlled move
    void playerMove();
    // Performs an AI move
    void aiMove();
    // Changes players
    void changePlayer();
    // Ends a game and prompts for quit or re-try
    void endGame(bool wasTie);

    // Member Variables
    Board _board; ///< The tic-tac-toe boarde
    int _currentPlayer; ///< The index of the current player
    int _aiPlayer; ///< Index of the AI player
    GameState _gameState; ///< The state of the game
    AI _ai; ///< The AI player
    bool _isMultiplayer;
};


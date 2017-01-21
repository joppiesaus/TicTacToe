#pragma once

#include "Board.h"

struct AiMove
{
	AiMove() {}
	AiMove(int Score) : score(Score){}
	int x;
	int y;
	int score;
};

class AI {
public:
    // Initializes the AI player
    void init(int aiPlayer);
    // Performs the AI move
    void performMove(Board& board);
private:

	AiMove getBestMove(Board& board, int player, int depth = 0);

    int _aiPlayer; ///< Index of the AI
    int _humanPlayer; ///< Index of the player
};


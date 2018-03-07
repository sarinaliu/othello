#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <algorithm>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
	Board *b;
	Side side;
	Side opponentside;

	/*int scoring_sys[8][8] = {
							{3, -2, 2, 2, 2, 2, -2, 3},
                            {-2, -3, 1, 1, 1, 1, -3, -2},
                            {2, 1, 1, 1, 1, 1, 1, 2},
                            {2, 1, 1, 1, 1, 1, 1, 2},
                            {2, 1, 1, 1, 1, 1, 1, 2},
                            {2, 1, 1, 1, 1, 1, 1, 2},
                            {-2, -3, 1, 1, 1, 1, -3, -2},
                            {3, -2, 2, 2, 2, 2, -2, 3}
                        	};*/

    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif

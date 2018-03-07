#include "player.hpp"
#include <vector>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    b = new Board();
    this->b = b;

    this->side = side;

    if (side == BLACK)
    {
        opponentside = WHITE;
    }
    else
    {
        opponentside = BLACK;
    }

}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    int scoring_sys[8][8] = {
                            {3, -2, 2, 2, 2, 2, -2, 3},
                            {-2, -3, 1, 1, 1, 1, -3, -2},
                            {2, 1, 1, 1, 1, 1, 1, 2},
                            {2, 1, 1, 1, 1, 1, 1, 2},
                            {2, 1, 1, 1, 1, 1, 1, 2},
                            {2, 1, 1, 1, 1, 1, 1, 2},
                            {-2, -3, 1, 1, 1, 1, -3, -2},
                            {3, -2, 2, 2, 2, 2, -2, 3}
                            };

    if (b->isDone())
    {
        return nullptr;
    }

    if (opponentsMove != nullptr)
    {
        b->doMove(opponentsMove, opponentside);
    }

    // RANDOM METHOD
    /*Move *yourMove = new Move(0, 0);
    if (b->hasMoves(side))
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                *yourMove = Move(i, j);
                if (b->checkMove(yourMove, side))
                {
                    b->doMove(yourMove, side);
                    cerr << yourMove->getX() << " , " << yourMove->getY() << endl;
                    return yourMove;
                }
            }
        }
    }*/
    


    vector<Move*> v_moves;
    vector<int> v_scores;
    Move *yourMove = new Move(0, 0);
    int num = 0;

    if (b->hasMoves(side))
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                *yourMove = Move(i, j);
                if (b->checkMove(yourMove, side))
                {
                    v_moves.push_back(new Move(i, j));
                    v_scores.push_back(scoring_sys[i][j]);
                }
            }
        }       

        for (unsigned int k = 1; k < v_moves.size(); k++)
        {  
            if (v_scores[k - 1] < v_scores[k])
            {
                num = k;
            }
        }
        
        b->doMove(v_moves[num], side);
        
        return v_moves[num];
    }

    
    return nullptr;
}

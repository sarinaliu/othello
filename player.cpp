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
                            {12, -4, 6, 6, 6, 6, -4, 12},
                            {-4, -8, 1, 1, 1, 1, -8, -4},
                            {6, 1, 1, 1, 1, 1, 1, 6},
                            {6, 1, 1, 1, 1, 1, 1, 6},
                            {6, 1, 1, 1, 1, 1, 1, 6},
                            {6, 1, 1, 1, 1, 1, 1, 6},
                            {-4, -8, 1, 1, 1, 1, -8, -4},
                            {12, -4, 6, 6, 6, 6, -4, 12}
                            };
    if (b->isDone())
    {
        return nullptr;
    }

    if (opponentsMove != nullptr)
    {
        b->doMove(opponentsMove, opponentside);
    }

    vector<Move*> v_moves;
    vector<Move*> v_moves_temp;
    vector<Move*> v_moves1;
    vector<Move*> v_moves1_temp;
    vector<Move*> v_moves2;
    vector<Move*> v_moves2_temp;

    vector<Move*> temp1;
    vector<Move*> temp2;
    vector<int> v_scores;
    vector<int> v_scores_temp;
    vector<int> v_scores1;
    vector<int> v_scores1_temp;
    vector<int> v_scores2;
    vector<int> v_scores2_temp;

    Move *yourMove = new Move(0, 0);
    Move *theirMove = new Move(0, 0);
    Move *yourMove1 = new Move(0, 0);
    int num0 = 0;
    int num = 0;
    int finalnum = 0;
    int opp_num = 0;
    int count = 0;

    while (count <= 3)
    {
        if (count == 0)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    *yourMove = Move(i, j);
                    if (b->checkMove(yourMove, side))
                    {
                        v_moves_temp.push_back(new Move(i, j));
                        v_scores_temp.push_back(scoring_sys[i][j]);
                    }
                }
            }

            if (v_scores_temp.size() != 0)
                {
                    num0 = 0;
                    for (unsigned int x = 0; x < v_scores_temp.size(); x++)
                    {
                        if (v_scores_temp[num0] < v_scores_temp[x])
                        {
                            num0 = x;
                        }
                    }

                    for (unsigned int y = 0; y < v_scores_temp.size(); y++)
                    {
                        if (v_scores_temp[num0] == v_scores_temp[y]) // best your moves
                        {
                            v_moves.push_back(new Move(v_moves_temp[y]->getX(), v_moves_temp[y]->getY()));
                            v_scores.push_back(v_scores_temp[y]);
                        }
                    }
                }
        }        

        else if (count == 1 && v_moves.size() != 0)
        {
            for (unsigned int k = 0; k < v_moves.size(); k++)
            {  
                Board *b_copy1 = b->copy();
                b_copy1->doMove(v_moves[k], side);
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        *theirMove = Move(i, j);
                        if (b_copy1->checkMove(theirMove, opponentside))
                        {
                            int score =(v_scores[k] % 48) - (scoring_sys[i][j] % 48);
                            v_scores1_temp.push_back(score);
                            v_moves1_temp.push_back(new Move(i, j));
                        }
                    }
                }

                if (v_scores1_temp.size() != 0)
                {
                    opp_num = 0;
                    for (unsigned int x = 1; x < v_scores1_temp.size(); x++)
                    {
                        if (v_scores1_temp[opp_num] > v_scores1_temp[x])
                        {
                            opp_num = x;
                        }
                    }    
                    for (unsigned int y = 0; y < v_scores1_temp.size(); y++)
                    {
                        if (v_scores1_temp[opp_num] == v_scores1_temp[y])
                        {
                            v_scores1.push_back(v_scores1_temp[y]); // best opponent moves
                            v_moves1.push_back(new Move(v_moves1_temp[y]->getX(), v_moves1_temp[y]->getY()));
                            temp1.push_back(new Move(v_moves[k]->getX(), v_moves[k]->getY())); // original move
                        }
                    }
                }
            }

        }

        else if (count == 2 && v_moves1.size() != 0)
        {
            for (unsigned int k = 0; k < v_moves1.size(); k++)
            {  
                Board *b_copy2 = b->copy();
                b_copy2->doMove(temp1[k], side);
                b_copy2->doMove(v_moves1[k], opponentside);
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        *yourMove1 = Move(i, j);
                        if (b_copy2->checkMove(yourMove1, side))
                        {
                            int score =(v_scores1[k] % 48) + (scoring_sys[i][j] % 48);
                            v_scores2_temp.push_back(score);
                            v_moves2_temp.push_back(new Move(i, j));
                        }
                    }
                }

                if (v_scores2_temp.size() != 0)
                {
                    num = 0;
                    for (unsigned int x = 1; x < v_scores2_temp.size(); x++)
                    {
                        if (v_scores2_temp[num] < v_scores2_temp[x])
                        {
                            num = x;
                        }
                    }    
                    for (unsigned int y = 0; y < v_scores2_temp.size(); y++)
                    {
                        if (v_scores2_temp[num] == v_scores2_temp[y])
                        {
                            v_scores2.push_back(v_scores2_temp[y]); // best your moves
                            v_moves2.push_back(new Move(v_moves2_temp[y]->getX(), v_moves2_temp[y]->getY()));
                            temp2.push_back(new Move(temp1[k]->getX(), temp1[k]->getY())); // original move
                        }
                    }
                }
            }

        }

        else if (count == 3 && v_scores2.size() != 0)
        {
                finalnum = 0;
                for (unsigned int t = 1; t < v_scores2.size(); t++)
                {
                    if (v_scores2[finalnum] < v_scores2[t])
                    {
                        finalnum = t;
                    }
                }

                b->doMove(temp2[finalnum], side);      
                return temp2[finalnum];

        }

        else
        {
            if (!b->isDone())
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        *yourMove = Move(i, j);
                        if (b->checkMove(yourMove, side))
                        {
                            b->doMove(yourMove, side);
                            return yourMove;
                        }
                    }
                }
            }
            else
            {
                return nullptr;
            }
        }

        count++;
    }

    return nullptr;
}

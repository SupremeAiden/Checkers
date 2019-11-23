#include "StudentAI.h"

//The following part should be completed by students.
//The students can modify anything except the class name and exisiting functions and varibles.
StudentAI::StudentAI(int col,int row,int p)
	:AI(col, row, p)
{
    board = Board(col,row,p);
    board.initializeGame();
    player = 2;
}

Move StudentAI::GetMove(Move move)
{
    if (move.seq.empty())
    {
        player = 1;
    } else{
        board.makeMove(move,player == 1?2:1);
    }
    vector<vector<Move>> moves = board.getAllPossibleMoves(player);
    Move best_move = moves[0][0];
    int score = -100000;                    // should be infinity
    int current;
    for (int i = 0; i < moves.size(); i++ ) {
        for (int j = 0; j < moves[i].size(); j++) {
            Move my_move = moves[i][j];
            board.makeMove(my_move, player);
            current = -alpha_beta(5, -100000, 100000, player == 1?2:1);         // swap for infinity and -
            board.Undo();
            if (current >= score) {
                score = current;
                best_move = my_move;
            }
        }
    }
    board.makeMove(best_move,player);
    return best_move;
}

// still need many more heuristics - this should be called eval()
int StudentAI::Eval(int t)
{
    return H_piece_count(t);
}

int StudentAI::H_piece_count(int t)
{
    return get_piece_count(t) - get_piece_count(t == 1 ? 2 : 1);
}

int StudentAI::get_piece_count(int t)
{
    int peasants = 0;
    int kings = 0;
    int forward_adv = 0;
    vector<vector<Move>> moves = board.getAllPossibleMoves(t);
    for (int i = 0; i < moves.size(); i++)
    {
        Position pos = moves[i][0].seq[0];
        if (board.board[pos[0]][pos[1]].isKing) kings++;
        else peasants++;
        if(t == 1)
        {
            forward_adv = pos[1] + forward_adv;
        } else {
            forward_adv = row - pos[1] + forward_adv;
        }

    }
    peasants *= 3;
    kings *= 3;
    return (peasants + kings) + forward_adv;
}

/*
int StudentAI::H_advanced_forward(int t)
{
    vector<vector<Move>> moves = board.getAllPossibleMoves(t);
    for (int i = 0; i < moves.size(); i++)
    {
        
    }
    return checkers_forward(int t); 
}
*/


int StudentAI::alpha_beta(int depth, int alpha, int beta, int t)
{
    //this will currently value a win at the same rate as a tie
    int score;
    if (depth <= 0)
    {
        return Eval(t);
    }
    vector<vector<Move>> moves = board.getAllPossibleMoves(t);
    for (int i = 0; i < moves.size(); i++ )
    {
        for (int j = 0; j < moves[i].size(); j++)
        {
            Move my_move = moves[i][j];
            board.makeMove(my_move, t);
            score = -alpha_beta(depth - 1, -beta, -alpha, t == 1 ? 2 : 1);
            if (score >= alpha) {
                alpha = score;
            }
            board.Undo();
            if (alpha >= beta) {
                break;
            }
        }
    }
    return alpha;
}

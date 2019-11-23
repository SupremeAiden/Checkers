#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#include "Board.h"
#pragma once

//The following part should be completed by students.
//Students can modify anything except the class name and exisiting functions and varibles.
class StudentAI :public AI
{
public:
    Board board;
	StudentAI(int col, int row, int p);
	virtual Move GetMove(Move board);
	int Eval(int t);
    int H_piece_count(int t);
    int get_piece_count(int t);
	int alpha_beta(int depth, int alpha, int beta, int player);
	int turn;
};

#endif //STUDENTAI_H

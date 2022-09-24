#include <iostream>
#include "Agent.h"
#include <ctype.h>
#include <vector>

using namespace std;
int agent::GetBestMove()
{
    int value = MaxValue(Square,-infinity,infinity,1);
    return value;
}


int agent::MaxValue(const vector<char> & board, int alpha, int beta, int depth)
{
    if(depth == maximal_depth){
        int eval = 0;
        for ( int pos = 0; pos<64 ;pos++ ){
            eval += evaluator.EvaluatePosition(board[pos],pos);
        }
        return eval;
    }
    else{
        int value = -infinity;
        int utility;
        vector<vector<char> > moves;
        GenerateMoves(board,maximizer,moves);
        for (auto state = moves.cbegin();state != moves.cend();state++){
            if(not Check(*state,minimizer)){
                utility = MinValue(*state,alpha,beta,depth+1);
                if (value < utility){
                    value = utility;
                    if(depth == 1){//we are in root node
                        SaveMove(board,*state);
                    }
                }
                if (value >= beta){return value;}
                alpha = max(alpha,value);
            }
        }
        return value; //if check mate return default value -infinity
    }
}
  
    
int agent::MinValue(const vector<char> & board, int alpha, int beta, int depth)
{
    if(depth == maximal_depth){
        int eval = 0;
        for ( int pos = 0; pos<64 ;pos++ ){
            eval += evaluator.EvaluatePosition(board[pos],pos);
        }
        return eval;
    }
    else{
        int value = infinity;
        vector<vector<char> > moves;
        GenerateMoves(board,minimizer,moves);
        for (auto state = moves.cbegin();state != moves.cend();state++){
            if(not Check(*state,maximizer)){
                value = min(value,MaxValue(*state,alpha,beta,depth+1));
                if (value <= alpha){return value;}
                beta = min(beta,value);
            }
        }
        return value; //if check mate return default value infinity
    }
}   


void agent::SaveMove(const vector<char> & board_before,const vector<char> & board_after)
{
    for(int pos = 0;pos < 64;pos++){
        if(piece.Color(board_before[pos]) == maximizer && piece.Color(board_after[pos]) != maximizer){
            from = pos;
        }
        else if(piece.Color(board_before[pos]) != maximizer && piece.Color(board_after[pos]) == maximizer){
            to = pos;
        }
    }
}

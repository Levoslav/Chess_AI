/*
    This header file contains th ChessGame class.
    contains the whole game.
*/

#ifndef _CHESSGAME_H
#define _CHESSGAME_H

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>
#include "board.h"
#include "piece.h"
#include "cctype"

class ChessGame: public sf::Drawable{
private:
    Board board;
    std::array<Piece, 16> whitePieces;
    std::array<Piece, 16> blackPieces;
    Piece* selectedPiece;
    std::vector<sf::RectangleShape> possibleMovesSquares;
    std::string lastMove;

    sf::RectangleShape infoRestart;

    sf::Font font;
    sf::Text textRestart;
    sf::Text textTurn;
    sf::Text textSituation;
    sf::Text textLastMove;
    

    bool selected;
    bool playerTurn; // true = White turn, false = Black Turn
    bool playerTurnCheck;
    bool mate;
    int turn;

    void createMovesSquares();

    void calcPossibleMoves();
    void calcKingMoves(Piece* tmpPiece);
    void calcQueenMoves(Piece* tmpPiece);
    void calcRookMoves(Piece* tmpPiece);
    void calcBishopMoves(Piece* tmpPiece);
    void calcKnightMoves(Piece* tmpPiece);
    void calcPawnMoves(Piece* tmpPiece);
    void calcCastling(Piece* tmpPiece);

    void eraseMoves(Piece* tmpPiece);

    void checkMate();

    void updateInfo();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    

public:
    ChessGame(sf::Color bordCol1, sf::Color bordCol2);

    bool getSelected(){return selected;}

    bool getMate(){return mate;}

    bool selectPiece(int pos);

    void moveSelected(int pos);

    void restart();

    //custom functions
    bool whiteTurn(){return playerTurn;}
    void turnChange(){playerTurn = !playerTurn;}
    int mapping[64] = {56,57,58,59,60,61,62,63,48,49,50,51,52,53,54,55,40,41,42,43,44,45,46,47,32,33,34,35,36,37,38,39,24,25,26,27,28,29,30,31,16,17,18,19,20,21,22,23,8 ,9 ,10,11,12,13,14,15,0 , 1, 2, 3, 4, 5, 6, 7};
    
    std::vector<char> getBoard(){
        std::vector<char> b(64, '#');
        int whitePos;
        int blackPos; 
        for (int i = 0; i < 16; i++){
        whitePos = whitePieces[i].getPosition(); 
        blackPos = blackPieces[i].getPosition();
        if (whitePos != -1)
            b[mapping[whitePos]] = whitePieces[i].getType();
        if (blackPos != -1)
            b[mapping[blackPos]] = tolower(blackPieces[i].getType());
        }
        return b;
    };
    


    


};


#endif
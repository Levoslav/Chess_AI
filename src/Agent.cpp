#include <iostream>
#include "Agent.h"
#include <ctype.h>
#include <vector>


using namespace std;
void agent::UploadFEN(const string & FEN)//FEN(Forsyth Edward Notation)
{
    int c = 0;
    int offset = 56;
    
    for (auto it = FEN.cbegin(); it != FEN.cend(); it++){
        if (*it == '/'){
            offset -= 8;
            c = 0;
        }
        else if(isdigit(*it)){
            for (int i = 0;i < (*it - '0');i++){
                Square[offset + c] = '#';
                c += 1;
            }
        }
        else{
            Square[offset + c] = *it;
            c += 1;
        }
    }
}


void agent::AddMove(const vector<char> & board, vector<vector<char> > & moves,int StartSquare, int TargetSquare)
{
    vector<char> temp = board;
    temp[TargetSquare] = temp[StartSquare];
    temp[StartSquare] = '#';
    moves.emplace_back(move(temp));
}


void agent::GenerateMoves(const vector<char> & board, char color, vector<vector<char> > & moves)
{
    moves.clear();
    int pos = 0;
    for (auto it = board.cbegin(); it != board.cend();it++)
    {
        if (piece.Color(*it) == color)
        {
            if(piece.IsSlidingPiece(*it)){
                GenerateSlidingMoves(pos,*it,board,color,moves);
            }
            else if(piece.IsPawn(*it)){
                GeneratePawnMoves(pos, board, color,moves);
            }
            else if(piece.IsKnight(*it)){
                GenerateKnightMoves(pos, board, color,moves);
            }
            else if(piece.IsKing(*it)){
                GenerateKingMoves(pos, board, color,moves);
            } 
        }
        pos++;
    }
}


void agent::GenerateSlidingMoves(int StartSquare,char Piece, const vector<char> & board, char color, vector<vector<char> > & moves)
{
    int FrontBorder = 0;
    int BackBorder = 7;
    if (Piece == piece.b_rook || Piece == piece.w_rook ){
        BackBorder = 3;
    } 
    else if(Piece == piece.b_bishop || Piece == piece.w_bishop ){
        FrontBorder = 4;
    }    

    for (int DirectionIndex = FrontBorder; DirectionIndex <= BackBorder; DirectionIndex++){
        for (int n = 1 ; n <= SquaresToEdge[StartSquare][DirectionIndex];n++){

            int TargetSquare = StartSquare + DirectionOffset[DirectionIndex] * n;
            char PieceOnTargetSquare = board[TargetSquare];

            if (piece.Color(PieceOnTargetSquare) == color){
                break;//blocked by our own piece
            }

            AddMove(board,moves,StartSquare,TargetSquare);

            if (piece.Color(PieceOnTargetSquare) == piece.Opponent(color)){
                break;//capture enemy and dont go further
            }
        }
    }
}


void agent::GeneratePawnMoves(int StartSquare, const std::vector<char> & board, char color, vector<vector<char> > & moves)
{
    bool onBase = piece.OnBase(StartSquare,color);;

    //indices for Directions
    int ForwardIndex;
    int LeftForwardIndex;
    int RightForwardIndex;

    int TargetSquare;
    char PieceOnTargetSquare;

    if (color == 'w'){
        ForwardIndex = 0;
        LeftForwardIndex = 4;
        RightForwardIndex = 7;
    }
    else {
        ForwardIndex = 1;
        LeftForwardIndex = 6;
        RightForwardIndex = 5;
    }

    // Forward / 2 Forward from base
    if (SquaresToEdge[StartSquare][ForwardIndex] >= 1){
        TargetSquare = StartSquare + DirectionOffset[ForwardIndex];
        PieceOnTargetSquare = board[TargetSquare];

        if (piece.Color(PieceOnTargetSquare) == piece.none){
            AddMove(board,moves,StartSquare,TargetSquare);

            if (SquaresToEdge[StartSquare][ForwardIndex] >= 2 && onBase){
                TargetSquare = StartSquare + DirectionOffset[ForwardIndex] * 2;
                PieceOnTargetSquare = board[TargetSquare];

                if(piece.Color(PieceOnTargetSquare) == piece.none){
                    AddMove(board,moves,StartSquare,TargetSquare);
                }
            }
        }
    }

    // Attack left
    if (SquaresToEdge[StartSquare][LeftForwardIndex] >= 1){
        TargetSquare = StartSquare + DirectionOffset[LeftForwardIndex];
        PieceOnTargetSquare = board[TargetSquare];

        if (piece.Color(PieceOnTargetSquare) == piece.Opponent(color)){
            AddMove(board,moves,StartSquare,TargetSquare);
        }
    }
    
    //Attack right
    if (SquaresToEdge[StartSquare][RightForwardIndex] >= 1){
        TargetSquare = StartSquare + DirectionOffset[RightForwardIndex];
        PieceOnTargetSquare = board[TargetSquare];

        if (piece.Color(PieceOnTargetSquare) == piece.Opponent(color)){
            AddMove(board,moves,StartSquare,TargetSquare);
        }
    }
}


void agent::GenerateKnightMoves(int StartSquare, const std::vector<char> & board, char color, vector<vector<char> > & moves)
{
    auto CheckAvailability = [&](int offset,int start,char color){
        if (piece.Color(board[start + offset]) != color){return true;}else{return false;}
    };

    for ( int DirectionIndex = 0; DirectionIndex < DirectionOffsetKnight.size() ; DirectionIndex++){
        switch (DirectionIndex)
        {
        case 0:
            if (SquaresToEdge[StartSquare][NORTH] >= 2 && SquaresToEdge[StartSquare][WEST] >= 1){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    AddMove(board,moves,StartSquare,StartSquare + DirectionOffsetKnight[DirectionIndex]);
                }
            }
            break;
        case 1:
            if (SquaresToEdge[StartSquare][NORTH] >= 1 && SquaresToEdge[StartSquare][WEST] >= 2){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    AddMove(board,moves,StartSquare,StartSquare + DirectionOffsetKnight[DirectionIndex]);
                }
            }
            break;
        case 2:
            if (SquaresToEdge[StartSquare][SOUTH] >= 1 && SquaresToEdge[StartSquare][WEST] >= 2){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    AddMove(board,moves,StartSquare,StartSquare + DirectionOffsetKnight[DirectionIndex]);
                }
            }
            break;
        case 3:
            if (SquaresToEdge[StartSquare][SOUTH] >= 2 && SquaresToEdge[StartSquare][WEST] >= 1){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    AddMove(board,moves,StartSquare,StartSquare + DirectionOffsetKnight[DirectionIndex]);
                }
            }
            break;
        case 4:
            if (SquaresToEdge[StartSquare][SOUTH] >= 2 && SquaresToEdge[StartSquare][EAST] >= 1){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    AddMove(board,moves,StartSquare,StartSquare + DirectionOffsetKnight[DirectionIndex]);
                }
            }
            break;
        case 5:
            if (SquaresToEdge[StartSquare][SOUTH] >= 1 && SquaresToEdge[StartSquare][EAST] >= 2){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    AddMove(board,moves,StartSquare,StartSquare + DirectionOffsetKnight[DirectionIndex]);
                }
            }
            break;
        case 6:
            if (SquaresToEdge[StartSquare][NORTH] >= 1 && SquaresToEdge[StartSquare][EAST] >= 2){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    AddMove(board,moves,StartSquare,StartSquare + DirectionOffsetKnight[DirectionIndex]);
                }
            }
            break;
        case 7:
            if (SquaresToEdge[StartSquare][NORTH] >= 2 && SquaresToEdge[StartSquare][EAST] >= 1){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    AddMove(board,moves,StartSquare,StartSquare + DirectionOffsetKnight[DirectionIndex]);
                    
                }
            }
            break;
        default:
            break;
        }
        
    }
    
}


void agent::GenerateKingMoves(int StartSquare, const std::vector<char> & board, char color, vector<vector<char> > & moves)
{
    int TargetSquare;
    char PieceOnTargetSquare;
    for (int DirectionIndex = 0; DirectionIndex < 8; DirectionIndex++){
        if(SquaresToEdge[StartSquare][DirectionIndex] >= 1){
            TargetSquare = StartSquare + DirectionOffset[DirectionIndex];
            PieceOnTargetSquare = board[TargetSquare];
            if (piece.Color(PieceOnTargetSquare) != color){
                AddMove(board,moves,StartSquare,TargetSquare);
            }
        }
    } 
}


bool agent::Check(const vector<char> & board,char color)
{
    int pos = 0;
    bool check = false;
    for (auto it = board.cbegin(); it != board.cend();it++){
        if (piece.Color(*it) == color){
            if(piece.IsSlidingPiece(*it)){
                check = SlidingCheck(pos,*it,board,color);
            }
            else if (piece.IsPawn(*it)){
                check = PawnCheck(pos, board, color);
            }
            else if (piece.IsKnight(*it)){
                check = KnightCheck(pos, board, color);
            }
            else if (piece.IsKing(*it)){
                check = KingCheck(pos, board, color);
            }

            if (check) 
                return true;
        }
        pos++;
    }
    return false;
}


bool agent::SlidingCheck(int StartSquare,char Piece, const vector<char> & board, char color)
{
    int FrontBorder = 0;
    int BackBorder = 7;
    if (Piece == piece.b_rook || Piece == piece.w_rook ){
        BackBorder = 3;
    } 
    else if(Piece == piece.b_bishop || Piece == piece.w_bishop ){
        FrontBorder = 4;
    }    

    for (int DirectionIndex = FrontBorder; DirectionIndex <= BackBorder; DirectionIndex++){
        for (int n = 1 ; n <= SquaresToEdge[StartSquare][DirectionIndex];n++){

            int TargetSquare = StartSquare + DirectionOffset[DirectionIndex] * n;
            char PieceOnTargetSquare = board[TargetSquare];

            if (piece.Color(PieceOnTargetSquare) == color){
                break;//blocked by our own piece
            }

            if (piece.Color(PieceOnTargetSquare) == piece.Opponent(color)){
                if (piece.IsKing(PieceOnTargetSquare))
                    return true;
                break;//enemy and dont go further
            }
        }
    }
    return false;
}


bool agent::PawnCheck(int StartSquare, const vector<char> & board, char color)
{
    int LeftForwardIndex;
    int RightForwardIndex;
    if (color == 'w'){
        LeftForwardIndex = 4;
        RightForwardIndex = 7;
    }
    else {
        LeftForwardIndex = 6;
        RightForwardIndex = 5;
    }
    // Attack left
    if (SquaresToEdge[StartSquare][LeftForwardIndex] >= 1){
        int TargetSquare = StartSquare + DirectionOffset[LeftForwardIndex];
        int PieceOnTargetSquare = board[TargetSquare];
        if (piece.Color(PieceOnTargetSquare) == piece.Opponent(color)){
            if(piece.IsKing(PieceOnTargetSquare))
                return true;
        }
    }
    //Attack right
    if (SquaresToEdge[StartSquare][RightForwardIndex] >= 1){
        int TargetSquare = StartSquare + DirectionOffset[RightForwardIndex];
        int PieceOnTargetSquare = board[TargetSquare];
        if (piece.Color(PieceOnTargetSquare) == piece.Opponent(color)){
            if(piece.IsKing(PieceOnTargetSquare))
                return true;
        }
    }
    return false;
}


bool agent::KnightCheck(int StartSquare, const vector<char> & board, char color)
{
    auto CheckAvailability = [&](int offset,int start,char color){
        if (piece.Color(board[start + offset]) != color){return true;}else{return false;}
    };
    int TargetSquare;
    char PieceOnTargetSquare;
    for ( int DirectionIndex = 0; DirectionIndex < DirectionOffsetKnight.size() ; DirectionIndex++){
        switch (DirectionIndex)
        {
        case 0:
            if (SquaresToEdge[StartSquare][NORTH] >= 2 && SquaresToEdge[StartSquare][WEST] >= 1){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    TargetSquare = StartSquare + DirectionOffsetKnight[DirectionIndex];
                }
            }
            break;
        case 1:
            if (SquaresToEdge[StartSquare][NORTH] >= 1 && SquaresToEdge[StartSquare][WEST] >= 2){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    TargetSquare = StartSquare + DirectionOffsetKnight[DirectionIndex];
                }
            }
            break;
        case 2:
            if (SquaresToEdge[StartSquare][SOUTH] >= 1 && SquaresToEdge[StartSquare][WEST] >= 2){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    TargetSquare = StartSquare + DirectionOffsetKnight[DirectionIndex];
                }
            }
            break;
        case 3:
            if (SquaresToEdge[StartSquare][SOUTH] >= 2 && SquaresToEdge[StartSquare][WEST] >= 1){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    TargetSquare = StartSquare + DirectionOffsetKnight[DirectionIndex];
                }
            }
            break;
        case 4:
            if (SquaresToEdge[StartSquare][SOUTH] >= 2 && SquaresToEdge[StartSquare][EAST] >= 1){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    TargetSquare = StartSquare + DirectionOffsetKnight[DirectionIndex];
                }
            }
            break;
        case 5:
            if (SquaresToEdge[StartSquare][SOUTH] >= 1 && SquaresToEdge[StartSquare][EAST] >= 2){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    TargetSquare = StartSquare + DirectionOffsetKnight[DirectionIndex];
                }
            }
            break;
        case 6:
            if (SquaresToEdge[StartSquare][NORTH] >= 1 && SquaresToEdge[StartSquare][EAST] >= 2){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    TargetSquare = StartSquare + DirectionOffsetKnight[DirectionIndex];
                }
            }
            break;
        case 7:
            if (SquaresToEdge[StartSquare][NORTH] >= 2 && SquaresToEdge[StartSquare][EAST] >= 1){
                if(CheckAvailability(DirectionOffsetKnight[DirectionIndex],StartSquare,color)){
                    TargetSquare = StartSquare + DirectionOffsetKnight[DirectionIndex];
                }
            }
            break;
        default:
            break;
        }
        PieceOnTargetSquare = board[TargetSquare];
        if (piece.Color(PieceOnTargetSquare) == piece.Opponent(color)){
            if(piece.IsKing(PieceOnTargetSquare))
                return true;
        }   
    }
    return false;
}


bool agent::KingCheck(int StartSquare, const vector<char> & board, char color)
{
    int TargetSquare;
    char PieceOnTargetSquare;
    for (int DirectionIndex = 0; DirectionIndex < 8; DirectionIndex++){
        if(SquaresToEdge[StartSquare][DirectionIndex] >= 1){
            TargetSquare = StartSquare + DirectionOffset[DirectionIndex];
            PieceOnTargetSquare = board[TargetSquare];
            if (piece.Color(PieceOnTargetSquare) == piece.Opponent(color)){
                if(piece.IsKing(PieceOnTargetSquare))
                    return true;
            }   
        }
    } 
    return false;
}


void agent::PrecomputeSquaresToEdges()
{
    int North;
    int South;
    int West;
    int East;
    for (int row = 0; row < 8;row++)
    {
        for (int column = 0; column < 8; column++)
        {
            North = 7 - row;
            South = row;
            West = column;
            East = 7 - column;
            
            SquaresToEdge.emplace_back(std::initializer_list<int>{North, South, West, East, min(North,West), min(West,South), min(South,East), min(East,North)}); 
        }
    }
}


void agent::print(const vector< vector<char> > & moves)
{
    cout << "-------------------------------" <<endl;
    cout << moves.size() << endl;
    int mapping[64] = {56,57,58,59,60,61,62,63,48,49,50,51,52,53,54,55,40,41,42,43,44,45,46,47,32,33,34,35,36,37,38,39,24,25,26,27,28,29,30,31,16,17,18,19,20,21,22,23,8 ,9 ,10,11,12,13,14,15,0 , 1, 2, 3, 4, 5, 6, 7};
    for (int j = 0 ; j < moves.size();j++){
        cout << "/////////////////////////////" <<endl;
        int c = 1;
        for (int i = 0; i < 64;i++){
            cout << moves[j][mapping[i]] << " " ;
            if (c % 8 == 0){cout <<endl;} 
            c +=1;
        }
        cout << "/////////////////////////////" <<endl;
        
    }
}
//my representation of the board
// 56,57,58,59,60,61,62,63
// 48,49,50,51,52,53,54,55
// 40,41,42,43,44,45,46,47
// 32,33,34,35,36,37,38,39
// 24,25,26,27,28,29,30,31
// 16,17,18,19,20,21,22,23
// 8 ,9 ,10,11,12,13,14,15
// 0 , 1, 2, 3, 4, 5, 6, 7


//library representation of the board
// 0 , 1, 2, 3, 4, 5, 6, 7
// 8 ,9 ,10,11,12,13,14,15
// 16,17,18,19,20,21,22,23
// 24,25,26,27,28,29,30,31
// 32,33,34,35,36,37,38,39
// 40,41,42,43,44,45,46,47
// 40,41,42,43,44,45,46,47
// 48,49,50,51,52,53,54,55
// 56,57,58,59,60,61,62,63


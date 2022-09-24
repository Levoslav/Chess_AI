#include <array>
#include <string>
#include <vector>
#include <tuple>
#include "Evaluation.h"
#include "Figure.h"

class agent
{
    public:
        agent(const std::string & FEN,char ColorOfAgent, int DepthOfMinimax)
        {
            maximal_depth = DepthOfMinimax;
            maximizer = ColorOfAgent;
            minimizer = piece.Opponent(ColorOfAgent);
        
            UploadFEN(FEN);
            PrecomputeSquaresToEdges();
        }
        
        void UploadFEN(const std::string & FEN);

        void UploadBoard(const std::vector<char> & b){ Square = b;}

        int GetBestMove();
        
        void print(const std::vector<std::vector<char> > & moves);
        
         //Best move
        int from =-1;
        int to =-1;
         std::vector<char> Square = {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',};
    private:
        piece piece;
        evaluation evaluator;

       
        int maximal_depth = 5;//desired depth of minimax
        int infinity = 1000000;
        char maximizer = 'b';// by default
        char minimizer = 'w';// by default

        std::vector<std::vector<int> > SquaresToEdge;
        std::vector<int> DirectionOffset = {8,-8,-1,1,7,-9,-7,9}; //[North,South,West,East,NorthWest,SouthWest,SouthEast,NorthEast]
        std::vector<int> DirectionOffsetKnight = {15,6,-10,-17,-15,-6,10,17}; //see documentation
        const int NORTH = 0;
        const int SOUTH = 1;
        const int WEST = 2;
        const int EAST = 3; 

        void PrecomputeSquaresToEdges();

        //Moves generator
        void GenerateMoves(const std::vector<char> & board, char color, std::vector<std::vector<char> > & moves);
        void GenerateSlidingMoves(int StartSquare, char Piece, const std::vector<char> & board, char color, std::vector<std::vector<char> > & moves);
        void GeneratePawnMoves(int StartSquare, const std::vector<char> & board, char color, std::vector<std::vector<char> > & moves);
        void GenerateKnightMoves(int StartSquare, const std::vector<char> & board, char color, std::vector<std::vector<char> > & moves);
        void GenerateKingMoves(int StartSquare, const std::vector<char> & board, char color, std::vector<std::vector<char> > & moves);
        void AddMove(const std::vector<char> & board, std::vector<std::vector<char> > & moves,int StartSquare, int TargetSquare);

        //Check checker
        bool Check(const std::vector<char> & board, char color);
        bool SlidingCheck(int StartSquare, char Piece, const std::vector<char> & board, char color);
        bool PawnCheck(int StartSquare, const std::vector<char> & board, char color);
        bool KnightCheck(int StartSquare, const std::vector<char> & board, char color);
        bool KingCheck(int StartSquare, const std::vector<char> & board, char color);

        //Minimax engine
        int MaxValue(const std::vector<char> & board, int alpha, int beta, int depth );
        int MinValue(const std::vector<char> & board, int alpha, int beta, int depth ); 
        void SaveMove(const std::vector<char> & board_before,const std::vector<char> & board_after);
    
};

// 7 # # # # # # # #
// 6 # 3 # # 3 # # #
// 5 # # 2 # 2 # # #
// 4 ? # # 1 1 # # #
// 3 # 3 2 1 Q 1 2 3
// 2 # # # 1 1 1 # #
// 1 # # 2 # 2 # 2 #
// 0 ? 3 # # 3 # # 3
//   0 1 2 3 4 5 6 7
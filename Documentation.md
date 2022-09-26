# **Chess AI**
Author: Jakub Hajko

Year: 2021/22

Language used: C++ (c++ 11 for compiling)

## **Description**
Chess playing engine based on the Mini-Max alpha-beta pruning algorithm connected to a library implementing a chess game and its visualization.
When it is engines turn it loads a state of the playing board and responds with the best possible move. 

## **Used materials**
* [Library](https://github.com/LeftForRed) (does not work anymore but created by so called "Lefti")
* [Chess ai](https://www.freecodecamp.org/news/simple-chess-ai-step-by-step-1d55a9266977/)
* [MiniMax and alpha beta](https://www.youtube.com/watch?v=STjW3eH0Cik)
* [Chess implementation](https://www.youtube.com/watch?v=U4ogK0MIzqk&t=1210s)
* [Evaluation function](https://www.chessprogramming.org/Simplified_Evaluation_Function)

## **API reference**

### ***Files***:
* Agent.cpp 
* Agent.h
* MiniMax.cpp
* Evaluation.h
* Figure.h
* main.cpp

# **Agent.cpp / Agent.h**
---
## **description**: 
Agent with inner a state that can load actual state of the board and generate all possible moves.


# Playing board
```cpp
std::vector<char> Square; 
```
### ***Description:*** 
Playing board that preserves actual state of the game. Vector of 64 chars.
Black pieces are small letters, White pieces are Capital letters.
 
  ***Visual representation:***
```
56,57,58,59,60,61,62,63                 r, n, b, q, k, b, n, r
48,49,50,51,52,53,54,55                 p, p, p, p, p, p, p, p
40,41,42,43,44,45,46,47                 #, #, #, #, #, #, #, #
32,33,34,35,36,37,38,39                 #, #, #, #, #, #, #, #
24,25,26,27,28,29,30,31                 #, #, #, #, #, #, #, #
16,17,18,19,20,21,22,23                 #, #, #, #, #, #, #, #
8 ,9 ,10,11,12,13,14,15                 P, P, P, P, P, P, P, P
0 , 1, 2, 3, 4, 5, 6, 7                 R, N, B, Q, K, B, N, R 
```
# Upload board
```cpp
void UploadBoard(const vector<char> & b){ Square = b;}
void UploadFEN(const string & FEN);
```
### ***Description:*** 
Two ways how to upload new board to the ***Agent***.
First is just to copy second is FEN ([Forsyth–Edwards Notation](https://en.wikipedia.org/wiki/Forsyth–Edwards_Notation))

# Help objects
```cpp
piece piece;
evaluation evaluator;
```
### ***Description:*** 
* Class **piece** (defined in Figure.h) is used for simple low level functions to avoid repetition when handling chars(Figures) in board.
* Class **evaluation** (defined in Evaluation.h) is responsible for evaluating the board with ineger. The greater the number the better for the maximizing player. Will be discussed in a more detail later. 

# Constants
```cpp
int maximal_depth = 5;
int infinity = 1000000;
char maximizer = 'b';
char minimizer = 'w';
```
### ***Description:*** 
These constants can be set in the constructor.
* **maximal_depth** - is the depth of a search in the MiniMax algo.
* **infinity** - something big.
* **maximizer** - Color of the agent(Agent tries to maximaze the eval value of the board) by default black.
* **minimizer** - Oponent in this case human player.
  
# Orientation in 1D as it was 2D
```cpp
std::vector<int> DirectionOffset = {8,-8,-1,1,7,-9,-7,9}; //[North,South,West,East,NorthWest,SouthWest,SouthEast,NorthEast]
std::vector<int> DirectionOffsetKnight = {15,6,-10,-17,-15,-6,10,17}; 
const int NORTH = 0;
const int SOUTH = 1;
const int WEST = 2;
const int EAST = 3; 
```
### ***Description:*** 
Because we use one dimensional vector to represent two dimensional chess board we need offsets to move [North,South,West,East,NorthWest,SouthWest,SouthEast,NorthEast].

# Precomputing 
```cpp
std::vector<std::vector<int> > SquaresToEdge;
void PrecomputeSquaresToEdges();
```
### ***Description:*** 
For every square it precomputes the number of squares to the edge of the chess board in every direction.

# Moves generating
```cpp
void GenerateMoves(const vector<char> & board, char color, vector<vector<char> > & moves);
``` 
### ***Description:***
Generate all possible moves for the player: ***color***. Function will include pseudo legal moves.
Go through the game board and if you find a piece of a chosen ***color*** use helper functions to generate all possible even **pseudo legal** moves and save them to vector ***moves***.
### ***Input:***
board = actual game board 

color = color of the player 

moves = empty vector which will be filled with possible moves
### ***Output:***
void function but output is the filled vector ***moves***.

## Helper functions:
```cpp
void AddMove(const vector<char> & board, vector<vector<char> > & moves,int StartSquare, int TargetSquare);
```
### ***Description:***
Function that adds new move to the vector ***moves***. Move in ***moves*** is the board but with moved pieces.

```cpp
void GenerateSlidingMoves(int StartSquare, char Piece, const vector<char> & board, char color, vector<vector<char> > & moves);
```
### ***Description:***
Generate all possible moves of sliding piece( Rook, Bishop, Queen ) and add them to the ***moves*** . 
### ***Input:***
StartSquare = square where the piece stands

Piece = R/B/Q/r/b/q

board = actual game board

color = color of the player

moves = vector which will be filled with possible moves

```cpp
void GeneratePawnMoves(int StartSquare, const vector<char> & board, char color, vector<vector<char> > & moves);
```
### ***Description:***
Generate all possible pawn moves. Pawns move one or to squares forward depending whether they stand on base position or not and diagonaly left or right when attacking. Forward direction is different for black and white pawns(SOUTH for black NORTH for white).
### ***Input:***
StartSquare = square where the piece stands

board = actual game board

color = color of the player

moves = vector which will be filled with possible moves

```cpp
void GenerateKnightMoves(int StartSquare, const vector<char> & board, char color, vector<vector<char> > & moves);
```
### ***Description:***
Generate all possible knight moves. Because knight does not move North/South/West/East/NorthWest/SouthWest/SouthEast/NorthEast we need different ***DirectionOffsets***. We need offsets that can represent knight moves:
```
. . X . X . .
. X . . . X .
. . . N . . .
. X . . . X .
. . X . X . .
```
We will use ***DirectionOffsetKnight***.

### ***Input:***
StartSquare = square where the piece stands

board = actual game board

color = color of the player

moves = vector which will be filled with possible moves

```cpp
void GenerateKingMoves(int StartSquare, const vector<char> & board, char color, vector<vector<char> > & moves);
```
### ***Description:***
Generate all possible king moves even pseudo legal moves(Later will be filtered out).
### ***Input:***
StartSquare = square where the piece stands

board = actual game board

color = color of the player

moves = vector which will be filled with possible moves

# Check checking
```cpp
bool Check(const vector<char> & board, char color);
bool PawnCheck(int StartSquare, const vector<char> & board, char color);
bool KnightCheck(int StartSquare, const vector<char> & board, char color);
bool KingCheck(int StartSquare, const vector<char> & board, char color);
bool SlidingCheck(int StartSquare, char Piece, const vector<char> & board, char color);
```
### ***Description:***
Take in ***board***. If player of ***color*** have oponent in check return true.
Structure of this functions is very similar to those moves generating functions. Moves are generated the same way but instead of adding them to the vector we propagate **true** if move "kills" oponent's king.

# MiniMax.cpp
---
## **description**: 
Implemented Mini-Max algorithm with alpha beta pruning.

# Mini-Max algorithm with aplha beta pruning
```cpp
int MaxValue(const vector<char> & board, int alpha, int beta, int depth );
int MinValue(const vector<char> & board, int alpha, int beta, int depth ); 
```
### ***Description:***
Mini-Max algorithm finds best(relative because it is difficult to tell what value should a state get) possible move for maximizer when both maximizer and minimizer do the best possible move for them in every turn to the depth of ***maximal_depth***. 
Functions recursively call each other (first called is MaxValue(Maximizing player is in the root) which calls MinValue which calls MaxValue again) to perform a search. If algorithm hits desired depth it evaluates the state and returns a value(integer). 
In each layer all possible moves are generated. For every new state we make a recursive call. To avoid pseudo legal moves and to find out when there is check and check mate or whether it is an invalid move the algorithm filters out moves which cannot be made because they would lead to immediate check form the oponent (example: you cannot move the king on the endangered square).
To filter these invalid moves we look at every generated move and decide whether it is check for the oponent with the ***Check*** function.
Observation: When all move are filtered out it is check mate.

# Evaluation.h
--- 

```cpp
class evaluation
```
### ***Description:***
Finding a good evaluation function is a difficult task. I used this [evaluation function](https://www.chessprogramming.org/Simplified_Evaluation_Function). Each piece has a value and gets bonuses depending on which square it stands (example: knight in the middle of the board is better than a king in the middle of the board ).
Implemented with tables(in my represenation vectors) for each piece.

# Figure.h
---
```cpp
class piece
```
### ***Description***
class encapsulating basic functions such as Color, whether piece is sliding pawn, king, knight...
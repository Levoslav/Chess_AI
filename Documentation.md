## **API reference**

### ***Files***:
* Agent.cpp 
* Agent.h
* MiniMax.cpp
* Evaluation.h
* Figure.h
* main.cpp

#### **Agent.cpp / Agent.h**
##### **description**: 
Agent with inner a state that can load actual state of the board and generate all possible moves.

---
**State variables**
> 
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

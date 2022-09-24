class evaluation
{
    public:
        int EvaluatePosition(char piece,int pos){
            int Return = 0;
            switch (piece)
            {
            case 'p':
                Return = (b_pawn_value + b_pawn_table[pos]);
                break;
            case 'r':
                Return = (b_rook_value + b_rook_table[pos]);
                break;
            case 'n':
                Return = (b_knight_value + b_knight_table[pos]);
                break;
            case 'b':
                Return = (b_bishop_value + b_bishop_table[pos]);
                break;
            case 'q':
                Return = (b_queen_value + b_queen_table[pos]);
                break;
            case 'k':
                Return = (b_king_value + b_king_table[pos]);
                break;
            case 'P':
                Return = (w_pawn_value + w_pawn_table[pos]);
                break;
            case 'R':
                Return = (w_rook_value + w_rook_table[pos]);
                break;
            case 'N':
                Return = (w_knight_value + w_knight_table[pos]);
                break;
            case 'B':
                Return = (w_bishop_value + w_bishop_table[pos]);
                break;
            case 'Q':
                Return = (w_queen_value + w_queen_table[pos]);
                break;
            case 'K':
                Return = (w_king_value + w_king_table[pos]);
                break;
            case '#':
                return 0;
            default:
                break;
            }
            return Return;
        }

        void Switch(){
            //by default maximizing player is black
            //we can swith max and min player with the function Switch()
            b_pawn_value =   -b_pawn_value;
            b_rook_value =   -b_rook_value;
            b_knight_value = -b_knight_value;
            b_bishop_value = -b_bishop_value;
            b_queen_value =  -b_queen_value;
            b_king_value =   -b_king_value;

            w_pawn_value =   -w_pawn_value;
            w_rook_value =   -w_rook_value;
            w_knight_value = -w_knight_value;
            w_bishop_value = -w_bishop_value;
            w_queen_value =  -w_queen_value;
            w_king_value =   -w_king_value;
        }
        
    private:
        int b_pawn_value =   100;
        int b_rook_value =   500;
        int b_knight_value = 320;
        int b_bishop_value = 330;
        int b_queen_value =  900;
        int b_king_value =   20000;

        int w_pawn_value =   -100;
        int w_rook_value =   -500;
        int w_knight_value = -320;
        int w_bishop_value = -330;
        int w_queen_value =  -900;
        int w_king_value =   -20000;

        //tables depending on position of the piece
        int b_pawn_table[64] =  {0, 0, 0, 0, 0, 0, 0, 0, 50, 50, 50, 50, 50, 50, 50, 50, 10, 10, 20, 30, 30, 20, 10, 10, 5, 5, 10, 25, 25, 10, 5, 5, 0, 0, 0, 20, 20, 0, 0, 0, 5, -5, -10, 0, 0, -10, -5, 5, 5, 10, 10, -20, -20, 10, 10, 5, 0, 0, 0, 0, 0, 0, 0, 0 };
                                
        int b_rook_table[64] =  {0, 0, 0, 0, 0, 0, 0, 0, 5, 10, 10, 10, 10, 10, 10, 5, -5, 0, 0, 0, 0, 0, 0, -5, -5, 0, 0, 0, 0, 0, 0, -5, -5, 0, 0, 0, 0, 0, 0, -5, -5, 0, 0, 0, 0, 0, 0, -5, -5, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 5, 5, 0, 0, 0};

        int b_knight_table[64] ={-50, -40, -30, -30, -30, -30, -40, -50, -40, -20, 0, 0, 0, 0, -20, -40, -30, 0, 10, 15, 15, 10, 0, -30, -30, 5, 15, 20, 20, 15, 5, -30, -30, 0, 15, 20, 20, 15, 0, -30, -30, 5, 10, 15, 15, 10, 5, -30, -40, -20, 0, 5, 5, 0, -20, -40, -50, -40, -30, -30, -30, -30, -40, -50};
                                
        int b_bishop_table[64] ={-20, -10, -10, -10, -10, -10, -10, -20, -10, 0, 0, 0, 0, 0, 0, -10, -10, 0, 5, 10, 10, 5, 0, -10, -10, 5, 5, 10, 10, 5, 5, -10, -10, 0, 10, 10, 10, 10, 0, -10, -10, 10, 10, 10, 10, 10, 10, -10, -10, 5, 0, 0, 0, 0, 5, -10, -20, -10, -10, -10, -10, -10, -10, -20};

        int b_queen_table[64] = {-20, -10, -10, -5, -5, -10, -10, -20, -10, 0, 0, 0, 0, 0, 0, -10, -10, 0, 5, 5, 5, 5, 0, -10, -5, 0, 5, 5, 5, 5, 0, -5, -5, 0, 5, 5, 5, 5, 0, 0, -10, 0, 5, 5, 5, 5, 5, -10, -10, 0, 0, 0, 0, 5, 0, -10, -20, -10, -10, -5, -5, -10, -10, -20};

        int b_king_table[64] =  {-30, -40, -40, -50, -50, -40, -40, -30, -30, -40, -40, -50, -50, -40, -40, -30, -30, -40, -40, -50, -50, -40, -40, -30, -30, -40, -40, -50, -50, -40, -40, -30, -20, -30, -30, -40, -40, -30, -30, -20, -10, -20, -20, -20, -20, -20, -20, -10, 20, 20, 0, 0, 0, 0, 20, 20, 20, 30, 10, 0, 0, 10, 30, 20};

        int w_pawn_table[64] =  { 0,  0,  0,  0,  0,  0,  0,  0, 5, 10, 10,-20,-20, 10, 10,  5, 5, -5,-10,  0,  0,-10, -5,  5, 0,  0,  0, 20, 20,  0,  0,  0, 5,  5, 10, 25, 25, 10,  5,  5, 10, 10, 20, 30, 30, 20, 10, 10, 50, 50, 50, 50, 50, 50, 50, 50, 0,  0,  0,  0,  0,  0,  0,  0};

        int w_rook_table[64] =  { 0, 0, 0, 5, 5, 0, 0, 0,
                                 -5, 0, 0, 0, 0, 0, 0, -5,
                                 -5, 0, 0, 0, 0, 0, 0, -5,
                                 -5, 0, 0, 0, 0, 0, 0, -5,
                                 -5, 0, 0, 0, 0, 0, 0, -5,
                                 -5, 0, 0, 0, 0, 0, 0, -5,
                                  5, 10, 10, 10, 10, 10, 10, 5,
                                  0, 0, 0, 0, 0, 0, 0, 0};
                                
        
       int w_knight_table[64] ={-50, -40, -30, -30, -30, -30, -40, -50, -40, -20, 0, 5, 5, 0, -20, -40, -30, 5, 10, 15, 15, 10, 5, -30, -30, 0, 15, 20, 20, 15, 0, -30, -30, 5, 15, 20, 20, 15, 5, -30, -30, 0, 10, 15, 15, 10, 0, -30, -40, -20, 0, 0, 0, 0, -20, -40, -50, -40, -30, -30, -30, -30, -40, -50};

        int w_bishop_table[64] ={-20, -10, -10, -10, -10, -10, -10, -20, -10, 5, 0, 0, 0, 0, 5, -10, -10, 10, 10, 10, 10, 10, 10, -10, -10, 0, 10, 10, 10, 10, 0, -10, -10, 5, 5, 10, 10, 5, 5, -10, -10, 0, 5, 10, 10, 5, 0, -10, -10, 0, 0, 0, 0, 0, 0, -10, -20, -10, -10, -10, -10, -10, -10, -20};

        int w_queen_table[64] = {-20, -10, -10, -5, -5, -10, -10, -20, -10, 0, 5, 0, 0, 0, 0, -10, -10, 5, 5, 5, 5, 5, 0, -10, 0, 0, 5, 5, 5, 5, 0, -5, -5, 0, 5, 5, 5, 5, 0, -5, -10, 0, 5, 5, 5, 5, 0, -10, -10, 0, 0, 0, 0, 0, 0, -10, -20, -10, -10, -5, -5, -10, -10, -20};

        int w_king_table[64] =  {20, 30, 10, 0, 0, 10, 30, 20, 20, 20, 0, 0, 0, 0, 20, 20, -10, -20, -20, -20, -20, -20, -20, -10, -20, -30, -30, -40, -40, -30, -30, -20, -30, -40, -40, -50, -50, -40, -40, -30, -30, -40, -40, -50, -50, -40, -40, -30, -30, -40, -40, -50, -50, -40, -40, -30, -30, -40, -40, -50, -50, -40, -40, -30};
};



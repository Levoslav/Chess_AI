class piece
{
    public:
        char b_pawn   = 'p';
        char b_rook   = 'r';
        char b_knight = 'n';
        char b_bishop = 'b';
        char b_queen  = 'q';
        char b_king   = 'k';

        char w_pawn   = 'P';
        char w_rook   = 'R';
        char w_knight = 'N';
        char w_bishop = 'B';
        char w_queen  = 'Q';
        char w_king   = 'K';

        char none = 'e';

        char Color(char piece)
        {
            if (piece == '#')
            {return 'e';}
            else if (islower(piece))
            {return 'b';}
            else
            {return 'w';}
        }

        bool IsSlidingPiece(char piece)
        {
            if(piece == b_rook || piece == w_rook || piece == b_bishop || piece == w_bishop || piece == b_queen  || piece == w_queen){return true;} else {return false;}
        }

        bool IsPawn(char piece)
        {
            if(piece == b_pawn || piece == w_pawn){return true;} else {return false;}
        }

        bool IsKnight(char piece)
        {
            if(piece == b_knight || piece == w_knight){return true;} else {return false;}
        }

        bool IsKing(char piece)
        {
            if(piece == b_king || piece == w_king){return true;} else {return false;}
        }

        char Opponent(char color){if (color == 'w'){return 'b';} else {return 'w';}}

        bool OnBase(int pos, char color)
        {
            if (color == 'w'){
                if (pos >= 8 && pos <= 15){return true;} else {return false;}
            }
            else{
                if(pos >= 48 && pos <= 55){return true;} else {return false;}
            }
        }
};
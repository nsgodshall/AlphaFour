#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

class Board;

class Player{
    public:
        Player(Board *b);
        virtual bool isInteractive() const { return false; }
    private:
        Board *m_board = nullptr;
};

class HumanPlayer : public Player {
    public:
        HumanPlayer(Board *b);
        virtual bool isInteractive() const { return true; } 
};

#endif // PLAYER_INCLUDED